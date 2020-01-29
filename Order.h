//
// Created by giacomo on 17/01/20.
//

#ifndef INC_ORDER_H
#define INC_ORDER_H

#include <functional>
#include <map>
#include "Model.h"
#include "Component.h"

class Order {
    unsigned int timestamp;
    const std::shared_ptr<const Model> model;
    unsigned int quantity;
    std::map<int, int> reserved_components;
    std::map<int, int> requested_components;

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

    bool is_component_fullfilled(const std::shared_ptr<const ComponentUsage> comp) const;
    void add_reserved_quantity(const std::shared_ptr<const ComponentUsage> comp, unsigned int quantity);
    unsigned int get_reserved_quantity(const std::shared_ptr<const ComponentUsage> comp) const;

    void add_requested_quantity(const std::shared_ptr<const ComponentUsage> comp, unsigned int quantity);
    unsigned int get_requested_quantity(const std::shared_ptr<const ComponentUsage> comp) const;

    bool operator<(const Order &rhs) const {
        return timestamp < rhs.timestamp;
    }
};

std::ostream& operator << (std::ostream& stream, const Order& order);

#endif //INC_ORDER_H
