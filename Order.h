//
// Created by giacomo on 17/01/20.
//

#ifndef INC_ORDER_H
#define INC_ORDER_H

#include <functional>
#include "Model.h"
#include "Component.h"
#include "BatchPeriod.h"

class Order {
    unsigned int timestamp;
    const std::shared_ptr<const Model> model;
    unsigned int quantity;
    bool waiting_components;

public:
    Order(unsigned int timestamp, const std::shared_ptr<const Model> model, const unsigned int quantity);

    unsigned int get_timestamp() const {
        return timestamp;
    }

    const std::shared_ptr<const Model> get_model() const{
        return model;
    }

    unsigned int get_quantity() const{
        return quantity;
    }

    bool is_waiting_components() const {
        return waiting_components;
    }

    void set_waiting_components(bool val) {
        waiting_components = val;
    }

    bool operator<(const Order &rhs) const {
        return timestamp < rhs.timestamp;
    }
};

std::ostream& operator << (std::ostream& stream, const Order& order);

#endif //INC_ORDER_H
