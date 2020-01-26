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
    std::list<Order> order_list;
    Fund fund;  //per la cassa utilizzo la classe cassa
    std::queue<Order> order_queue;  // coda degli ordini non ancora evasi
    BatchPeriod batch_period;

public:
    BatchProcessor() : batch_period{-1, -1} {}

    void load_components(const std::string &componentsFile);
    void load_models(const std::string &modelsFile);
    void set_cash_amount(double cashAmount){
        fund = Fund(cashAmount);
    }

    double get_cash_amount() {
        return fund.get_cash();
    }

    void set_batch_period(BatchPeriod batchPeriod) {
        batch_period = batchPeriod;
    }

    void append_order(const Order &order);

    void process_next_batch();
};


#endif //INC_BATCHPROCESSOR_H
