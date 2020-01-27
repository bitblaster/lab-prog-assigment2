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

void BatchProcessor::load_components(const std::string &componentsFile) {
    ComponentParser cp(componentsFile, component_map);
    cp.parse();
}

void BatchProcessor::load_models(const std::string &modelsFile) {
    ModelListParser mlp(modelsFile, model_map, component_map);
    mlp.parse();
}

void BatchProcessor::load_orders(const std::string &ordersFile) {
    OrderParser op(ordersFile, cash_amount, order_list);
    op.parse();

    // TODO: migliorare usando una funzione membro di Order tipo get_localtime, solo che mi dava leak per l'uso di localtime, quindi ho lasciato stare
    // Prendiamo il primo e l'ultimo mese
    time_t time = order_list.begin()->get_timestamp();
    tm minTime = *localtime(&time);
    time = order_list.begin()->get_timestamp();
    tm maxTime = *localtime(&time);

    //BatchPeriod lastPeriod {maxTime.tm_mon, maxTime.tm_year};
    delete batch_period;
    batch_period = new BatchPeriod(minTime.tm_mon, minTime.tm_year);

    std::cout << "Orders:" << std::endl;
    for (const Order &order : order_list) {
        std::cout << order << std::endl;
    }
    std::cout<<"Cassa dispondibile: "<< cash_amount << endl;

}

bool BatchProcessor::can_produce() {
    if(!batch_period)
        return false;

    if(order_list.empty() && order_queue.empty())
        return false;

    // TODO verificare quali altre condizioni valgono per la produzione (es. non ci sono soldi per evadere nessuno degli ordini)
    // TODO bisogna tenere conto degli ordini elaborati l'ultimo mese non evadibili, che saranno evasi solo in mesi successivi, quando arrivano i componenti
   if(cash_amount <= 0) {
        return false;
   }

    return true;
}

void BatchProcessor::verify_supplies() {
    for (set<Supply>::iterator it = supplies.begin(); it != supplies.end();  ++it) {
        if (it->get_delivery_period() == *batch_period) {
            it = supplies.erase(it);
        }
    }
}

void BatchProcessor::enqueue_new_orders() {
    // Aggiunta alla coda ordini di questo mese
    for (vector<Order>::iterator it = order_list.begin(); it != order_list.end() && (*it).in_period(*batch_period);  ++it) {
        order_queue.push(*it);
    }
}

void BatchProcessor::start_production() {
    while (can_produce()){
        verify_supplies(batch_period);
        enqueue_new_orders();
        verify_orders();
        process_batch();
    }

}

//verifica le componenti in arrivo, se il mese corrente corrisponde con quello di arrivo le aggiungo a warehouse
void BatchProcessor::verify_supplies(const BatchPeriod *actualPeriod) {
    if(!supplies.empty()) {
        BatchPeriod period = *actualPeriod;
        for (const Supply &s : supplies) {
            if (s.get_delivery_period() == period) {
                warehouse.add(s.get_component(), s.get_quantity());
                supplies.erase(s);
            }
        }
        return;
    }
}

void BatchProcessor::process_batch() {

    ++batch_period;
}

void BatchProcessor::current_status(){
    cout<<"Current status of: "<<endl<<endl;

    cout<<"Acquisti effettuati: "<<endl;
    for (const Supply &s : supplies) {
        cout << s.get_component().get_id() << " - " << s.get_delivery_period().get_month() << '/' << s.get_delivery_period().get_year() << " q:" << s.get_quantity() << endl;
    }
    cout<<endl<<"Magazzino: "<<endl;
    cout<<warehouse;

    cout<<endl<<"Ordini evasi: "<<endl;
    for(const Order& order : processed_orders){
        cout<<order<<endl;
    }
}

//TODO: CONTROLLA GLI ORDINI IN CODA, SE CI SONO COMPONENTI, IN CASO PRODURRE con process_order().
void BatchProcessor::verify_orders() {
   /* for(const Order& order : order_list){
        int id = order.get_model_id();
        int order_quantity = order.get_quantity();
        bool components=true;
        Model model = model_map.at(id);

        for(const ComponentUsage& comp : model.get_components()){
            Component component = component_map.at(comp.get_componentUsageId());
            int component_quantity = comp.get_quantity();

//            if(component_quantity*order_quantity <= warehouse.)

        }
    }
*/
}

void BatchProcessor::process_order(){


}


void BatchProcessor::add_processed_order(Order order) {
    if(order.is_processed()) processed_orders.push_back(order);
}



