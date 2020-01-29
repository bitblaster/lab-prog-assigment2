//
// Created by mozzicator on 26/01/20.
//

#include <iostream>
#include "parsers/ComponentParser.h"
#include "parsers/ModelListParser.h"
#include "BatchProcessor.h"
#include "parsers/OrderParser.h"
#include "Component.h"
#include "ComponentUsage.h"


using namespace std;
using namespace parsers;

void BatchProcessor::load_components(const string &componentsFile) {
    ComponentParser cp(componentsFile, component_map);
    cp.parse();
}

void BatchProcessor::load_models(const string &modelsFile) {
    if (component_map.empty())
        throw out_of_range("No components loaded");

    ModelListParser mlp(modelsFile, model_map, component_map);
    mlp.parse();
}

void BatchProcessor::load_orders(const string &ordersFile) {
    if (model_map.empty())
        throw out_of_range("No models loaded");

    OrderParser op(ordersFile, cash_amount, order_list, model_map);
    op.parse();

    int minTime = order_list.begin()->get()->get_timestamp();
    int maxTime = order_list.end()->get()->get_timestamp();

    cout << "Orders:" << endl;
    for (const auto &order : order_list) {
        cout << *order << endl;
    }
    cout<<"Cassa dispondibile: "<< cash_amount << endl;
}

void BatchProcessor::start_production() {
    while (can_produce()) {
        verify_supplies();
        enqueue_new_orders();
        process_batch();

        ++batch_month;
    }
}

bool BatchProcessor::can_produce() const {
    if(batch_month == 0)
        return false;

    if(order_list.empty() && order_queue.empty())
        return false;

    // Verifichiamo di non essere in stallo, ovvero dall'ultimo ordine in coda sono passati più mesi
    // di quelli necessari alla consegna di tutti i componenti del suo modello
    const shared_ptr<const Order> &lastOrder { *order_queue.end() };
    if (order_list.empty() && batch_month > lastOrder->get_timestamp() + lastOrder->get_model()->get_max_delivery_months())
        return false;

   return true;
}

// Verifica le componenti in arrivo, se il periodo corrente corrisponde con quello di arrivo aggiungiamo i componenti a magazzino
void BatchProcessor::verify_supplies() {
    for (auto it = supplies.begin(); it != supplies.end();  ++it) {
        if (it->second->get_delivery_period() == batch_month) {
            stock.add(it->second->get_component(), it->second->get_quantity());
            it = supplies.erase(it);
        }
        else if (it->second->get_delivery_period() > batch_month) {
            // Dato che supplies è ordinato per periodo di delivery crescente,
            // se troviamo un elemento don periodo successivo al corrente possiamo uscire
            break;
        }
    }
}

void BatchProcessor::enqueue_new_orders() {
    // Aggiunta alla coda ordini di questo mese
    for (auto it = order_list.begin(); it != order_list.end() && (*it)->get_timestamp() == batch_month; ++it) {
        order_queue.push_back(*it);
        it = order_list.erase(it);
    }
}

void BatchProcessor::process_batch() {
    for (auto it = order_queue.begin(); it != order_queue.end(); ++it) {
        double cash_needed = process_missing_components(*it, false);
        if(cash_needed <= cash_amount) {
            if(cash_needed <= 0) {
                // possiamo evadere l'ordine
                process_order(*it);
                it = order_queue.erase(it);

                // stampa dello stato corrente, come richiesto
                print_current_status();
            } else
                process_missing_components(*it, true);
        } else {
            cout << "Non c'è disponibilità sufficiente per l'ordine: " << *it;
        }
    }
}

//TODO commentare
double BatchProcessor::process_missing_components(const std::shared_ptr<const Order> order, bool processSupplies) {
    //TODO verificare se serve questo if
    if(processSupplies && order->is_waiting_components())
        return 0;

    double cost {0};
    const Model &model = *order->get_model();
    for(ComponentUsage compUsage : model.get_components()) {
        const shared_ptr<const Component> &comp = compUsage.get_component();
        unsigned int quantityNeeded = compUsage.get_quantity() * order->get_quantity();
        unsigned quantityAvailable = processSupplies ? stock.reserve(comp, quantityNeeded) : stock.get_availability(comp);
        if (quantityNeeded - quantityAvailable > 0) {
            // Calcoliamo il costo dell'acquisto della quantità necessaria, tenendo conto anche di eventuali
            // forniture già richieste questo mese e cercando di ottimizzare la quantità per avere un prezzo più basso

            int targetDeliveryMonth = batch_month + comp->get_months_to_delivery();
            map<supply_key, unique_ptr<Supply>>::iterator it = supplies.find(supply_key(targetDeliveryMonth, comp));
            if(it != supplies.end()) {
                // Esiste una fornitura precedente, di cui aumenteremo la quantità
                Supply &previousSupply { *(it->second) };
                //const unique_ptr<Supply> &previousSupply {supplies.at(supply_key(comp.get_id(), 1))};
                unsigned int quantityOfOngoingSupply = previousSupply.get_quantity();
                double costOfOngoingSupply = comp->get_price(quantityOfOngoingSupply);
                // Otteniamo la quantità suggerita in base alle vicinanza della quantità alle soglie definite
                unsigned int suggestedQuantity = Component::get_suggested_quantity(quantityOfOngoingSupply + quantityNeeded);
                cost += comp->get_price(suggestedQuantity) - costOfOngoingSupply;

                if(processSupplies)
                    previousSupply.add_quantity(suggestedQuantity - quantityOfOngoingSupply);
            } else {
                // Nessuna fornitura precedente trovata, ne creiamo una nuova
                // Otteniamo la quantità suggerita in base alle vicinanza della quantità alle soglie definite
                unsigned int suggestedQuantity = Component::get_suggested_quantity(quantityNeeded);
                cost += comp->get_price(suggestedQuantity);

                if(processSupplies)
                    supplies[supply_key(targetDeliveryMonth, comp)] = make_unique<Supply>(comp, targetDeliveryMonth, suggestedQuantity);
            }
        }
    }

    return cost;
}

void BatchProcessor::process_order(const shared_ptr<const Order> order) {
    const Model &model = *order->get_model();
    for(ComponentUsage compUsage : model.get_components()) {
        unsigned int quantityNeeded = compUsage.get_quantity() * order->get_quantity();

        // rimozione componenti dal magazzino
        stock.remove(compUsage.get_component(), quantityNeeded);
    }

    // aggiunta alla cassa del ricavo dell'ordine
    cash_amount += order->get_model()->get_price() * order->get_quantity();
    // aggiunta dell'ordine a quelli processati
    processed_orders.push_back(order);
}

void BatchProcessor::print_current_status() const {
    cout << "------- STATO CORRENTE PRODUZIONE -------" << endl << endl;

    cout << "Acquisti effettuati: " << endl;
    for (auto &s : supplies) {
        cout << "   Componente: " << s.second->get_component() << ", mese consegna prevista: " << s.second->get_delivery_period() << ", quantità: " << s.second->get_quantity() << endl;
    }
    cout << endl;

    cout << "Magazzino: "<< endl;
    for (auto &item : stock.get_items()) {
        cout << "   " << *item.second << endl;
    }

    cout << endl;
    cout << "Ordini evasi: " << endl;
    for(auto &order : processed_orders){
        cout << order << endl;
    }
}

