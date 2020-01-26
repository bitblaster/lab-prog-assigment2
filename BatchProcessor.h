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

class BatchProcessor {
    std::map<int, Component> component_map;
    std::map<int, Model> model_map;
    std::list<Order> order_list;
    double cash_amount;
    std::queue<Order> order_queue;  // coda degli ordini non ancora evasi
    BatchPeriod batch_period;

public:
    BatchProcessor() : cash_amount{0}, batch_period{-1, -1} {}

    void load_components(const std::string &componentsFile);
    void load_models(const std::string &modelsFile);

    double get_cash_amount() {
        return cash_amount;
    }

    void set_cash_amount(double cashAmount) {
        cash_amount = cashAmount;
    }

    void set_batch_period(BatchPeriod batchPeriod) {
        batch_period = batchPeriod;
    }

    void append_order(const Order &order);

    void process_next_batch();
};


#endif //INC_BATCHPROCESSOR_H
