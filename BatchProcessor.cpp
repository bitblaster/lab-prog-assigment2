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

    batch_month = order_list.front()->get_timestamp();

    cout << "Orders:" << endl;
    for (const auto &order : order_list) {
        cout << *order << endl;
    }
    cout << "Cassa disponibile: "<< cash_amount << endl;
    cout << "Lotto iniziale: " << batch_month << endl;
}

void BatchProcessor::start_production() {
    while (can_produce()) {
        cout << "Preparazione lotto " << batch_month << ", ordini precedenti in coda: " << order_queue.size() << endl;
        verify_supplies();
        enqueue_new_orders();
        cout << "Stato prima del lotto:" << endl;
        print_current_status();
        process_batch();

        cout << "Stato alla fine del lotto:" << endl;
        print_current_status();
        ++batch_month;
    }
}

bool BatchProcessor::can_produce() const {
    if(batch_month == 0)
        return false;

    if(order_list.empty()) {
        if(order_queue.empty())
            return false;

        // Verifichiamo di non essere in stallo, ovvero se dall'ultimo ordine in coda sono passati
        // più mesi di quelli necessari alla consegna di tutti i componenti del suo modello
        const shared_ptr<const Order> lastOrder { order_queue.back() };
        if (batch_month > lastOrder->get_timestamp() + lastOrder->get_model()->get_max_delivery_months()+1)
            return false;
    }

   return true;
}

// Verifica le componenti in arrivo, se il periodo corrente corrisponde con quello di arrivo aggiungiamo i componenti a magazzino
void BatchProcessor::verify_supplies() {
    // Dato che supplies è ordinato per periodo di delivery crescente,
    // se troviamo un elemento don periodo successivo al corrente possiamo uscire
    for (auto it = supplies.begin(); it != supplies.end() && it->second->get_delivery_period() <= batch_month;  it = supplies.erase(it)) {
        stock.add(it->second->get_component(), it->second->get_quantity());
    }
}

void BatchProcessor::enqueue_new_orders() {
    // Aggiunta alla coda ordini di questo mese
    for (auto it = order_list.begin(); it != order_list.end() && (*it)->get_timestamp() <= batch_month; it = order_list.erase(it)) {
        order_queue.push_back(*it);
    }
    //cout << order_list.size() << ',' << order_queue.size() <<endl;
}

void BatchProcessor::process_batch() {
    cout << "Inizio produzione lotto " << batch_month << ", ordini in coda: " << order_queue.size() << endl;

    auto it = order_queue.begin();
    while (it != order_queue.end()) {
        double cash_needed = process_missing_components(*it, false);
        if(cash_needed <= cash_amount) {
            if(cash_needed < 0) {
                // riserviamo gli eventuali ultimi pezzi mancanti dal magazzino
                process_missing_components(*it, true);
                // possiamo evadere l'ordine
                process_order(*it);
                it = order_queue.erase(it);

                // stampa dello stato corrente, come richiesto
                print_current_status();

                // evitiamo l'incremento dell'iteratore, dato che lo abbiamo già fatto tramite la erase()
                continue;
            } else {
                // riserviamo gli eventuali pezzi presenti in magazzino e
                // effettuiamo gli ordini dei rimanenti(se non già fatto in precedenza)
                process_missing_components(*it, true);
            }
        } else {
            cout << "Non c'è disponibilità sufficiente per l'ordine: " << *it;
        }

        ++it;
    }
}

double BatchProcessor::process_missing_components(const std::shared_ptr<Order> order, bool processSupplies) {
    double cost {0};
    const Model &model = *order->get_model();
    bool allComponentFulfilled=true;

    for(shared_ptr<const ComponentUsage> compUsage : model.get_components()) {
        // se il componente è già stato riservato possiamo saltarlo
        if (order->is_component_fullfilled(compUsage))
            continue;

        const shared_ptr<const Component> comp = compUsage->get_component();
        unsigned int quantityNeeded = compUsage->get_quantity() * order->get_quantity() - order->get_reserved_quantity(compUsage);

        // Verifica la disponibilità di magazzino e riserva dei componenti se stiamo processSupplies == true
        if(quantityNeeded > 0) {
            unsigned quantityAvailable = 0;
            if (processSupplies) {
                quantityAvailable = stock.reserve(comp, quantityNeeded);
                order->add_reserved_quantity(compUsage, quantityAvailable);
            } else {
                quantityAvailable = stock.get_availability(comp);
            }

            if (quantityNeeded > quantityAvailable) {
                // Almeno un componente è ancora mancante quindi non poteremo evadere l'ordine
                allComponentFulfilled = false;

                // Se non abbiamo ancora richiesto questo componente facciamo la richiesta di fornitura
                if (quantityNeeded > order->get_requested_quantity(compUsage)) {
                    // Calcoliamo il costo dell'acquisto della quantità necessaria, tenendo conto anche di eventuali
                    // forniture già richieste questo mese e cercando di ottimizzare la quantità per avere un prezzo più basso

                    double supplyCost = 0;
                    int targetDeliveryMonth = batch_month + comp->get_months_to_delivery();
                    map<supply_key, unique_ptr<Supply>>::iterator it = supplies.find(
                            supply_key(targetDeliveryMonth, comp));
                    if (it != supplies.end()) {
                        // Esiste una fornitura precedente, di cui aumenteremo la quantità
                        Supply &previousSupply{*(it->second)};
                        //const unique_ptr<Supply> &previousSupply {supplies.at(supply_key(comp.get_id(), 1))};
                        unsigned int quantityOfOngoingSupply = previousSupply.get_quantity();
                        double costOfOngoingSupply = comp->get_price(quantityOfOngoingSupply);
                        // Otteniamo la quantità suggerita in base alle vicinanza della quantità alle soglie definite
                        unsigned int suggestedQuantity = Component::get_suggested_quantity(
                                quantityOfOngoingSupply + quantityNeeded);
                        supplyCost = comp->get_price(suggestedQuantity) - costOfOngoingSupply;

                        // Effettua un'integrazione della richiesta di fornitura del lotto corrente, solo se non fatto in un lotto precedente
                        if (processSupplies) {
                            previousSupply.add_quantity(suggestedQuantity - quantityOfOngoingSupply);
                            cash_amount -= supplyCost; // Scala il denaro dalla cassa
                            order->add_requested_quantity(compUsage, quantityNeeded);
                        }
                    } else {
                        // Nessuna fornitura precedente trovata, ne creiamo una nuova
                        // Otteniamo la quantità suggerita in base alle vicinanza della quantità alle soglie definite
                        unsigned int suggestedQuantity = Component::get_suggested_quantity(quantityNeeded);
                        supplyCost = comp->get_price(suggestedQuantity);

                        // Effettua una nuova richiesta di fornitura solo se non fatto in un lotto precedente
                        if (processSupplies) {
                            supplies[supply_key(targetDeliveryMonth, comp)] = make_unique<Supply>(comp,
                                                                                                  targetDeliveryMonth,
                                                                                                  suggestedQuantity);
                            cash_amount -= supplyCost; // Scala il denaro dalla cassa
                            order->add_requested_quantity(compUsage, quantityNeeded);
                        }
                    }
                    cost += supplyCost;
                }
            }
        }
    }

    if (allComponentFulfilled)
        return -1;

    return cost;
}

void BatchProcessor::process_order(const shared_ptr<Order> order) {
    const Model &model = *order->get_model();
    for(shared_ptr<const ComponentUsage> compUsage : model.get_components()) {
        unsigned int quantityNeeded = compUsage->get_quantity() * order->get_quantity();

        // rimozione componenti dal magazzino
        stock.remove(compUsage->get_component(), quantityNeeded);
    }

    // aggiunta alla cassa del ricavo dell'ordine
    cash_amount += order->get_model()->get_price() * order->get_quantity();
    // aggiunta dell'ordine a quelli processati
    processed_orders.push_back(order);
}

void BatchProcessor::print_current_status() const {
    cout << "------- STATO CORRENTE PRODUZIONE -------" << endl << endl;

    cout << "Acquisti effettuati: " << endl;
    if (supplies.empty())
        cout << "   Nessuno" << endl;
    else {
        for (auto &s : supplies) {
            cout << "   Componente: " << *s.second->get_component() << ", mese consegna prevista: "
                 << s.second->get_delivery_period() << ", quantità: " << s.second->get_quantity() << endl;
        }
    }
    cout << endl;

    cout << "Magazzino: "<< endl;
    if (stock.get_items().empty())
        cout << "   Nessuno" << endl;
    else {
        for (auto &item : stock.get_items()) {
            cout << "   " << *item.second << endl;
        }
    }
    cout << endl;

    cout << "Ordini evasi: " << endl;
    if (processed_orders.empty())
        cout << "   Nessuno" << endl;
    else {
        for (auto &order : processed_orders) {
            cout << "   " << *order << endl;
        }
    }
    cout << endl;

    cout << "Ordini in coda: " << endl;
    if (order_queue.empty())
        cout << "   Nessuno" << endl;
    else {
        for (auto &order : order_queue) {
            cout << "   " << *order << endl;
        }
    }
}

