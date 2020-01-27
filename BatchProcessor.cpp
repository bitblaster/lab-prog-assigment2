//
// Created by mozzicator on 26/01/20.
//

#include <iostream>
#include "parsers/ComponentParser.h"
#include "parsers/ModelListParser.h"
#include "BatchProcessor.h"
#include "parsers/OrderParser.h"

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
//    if(cash_amount <= 0) {
//        for(Order &o : order_queue)
//    }

    return true;
}

void BatchProcessor::enqueue_new_orders() {
    // Aggiunta alla coda ordini di questo mese
    for (vector<Order>::iterator it = order_list.begin(); it != order_list.end() && (*it).in_period(*batch_period);  ++it) {
        order_queue.push(*it);
    }
}

void BatchProcessor::verify_supplies() {
}

void BatchProcessor::process_batch() {

    ++batch_period;
}

void BatchProcessor::start_production() {
    while (can_produce()) {
        verify_supplies();
        enqueue_new_orders();
        process_batch();
    }

}

