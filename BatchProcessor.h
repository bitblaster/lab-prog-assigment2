//
// Created by mozzicator on 26/01/20.
//

#ifndef INC_BATCHPROCESSOR_H
#define INC_BATCHPROCESSOR_H

#include <map>
#include <list>
#include <queue>
#include "Component.h"
#include "Model.h"
#include "Order.h"
#include "BatchPeriod.h"
#include "Fund.h"

class BatchProcessor {
    std::map<int, Component> component_map;
    std::map<int, Model> model_map;

    // Usiamo un vettore di ordini anziché un set per supportare il caso in cui 2 ordini abbiano lo stesso timestamp
    // Questo ci constringe però a fare il sort degli ordini dopo il caricamento (v. OrderParser::parse())
    std::vector<Order> order_list;
    Fund fund;  //per la cassa utilizzo la classe cassa
    double cash_amount;
    std::queue<Order> order_queue;  // coda degli ordini non ancora evasi
    BatchPeriod *batch_period;

    bool can_produce();
    void verify_supplies();
    void enqueue_new_orders();
    void process_batch();

public:
    BatchProcessor() : cash_amount {0}, batch_period{nullptr} {}

    void load_components(const std::string &componentsFile);
    void load_models(const std::string &modelsFile);
    void load_orders(const std::string &ordersFile);

    void set_cash_amount(double cashAmount){
        fund = Fund(cashAmount);
    }

    double get_cash_amount() {
        return fund.get_cash();
    }

    void start_production();
};


#endif //INC_BATCHPROCESSOR_H
