//
// Created by giacomo on 17/01/20.
//

#ifndef INC_ORDER_H
#define INC_ORDER_H

#include <chrono>
#include "Model.h"
#include "Component.h"

class Order {
    const std::tm timestamp;
    const int model_id;
    const int quantity;
    bool processed;

public:
    Order(const std::tm timestamp, const int model_id, const int quantity) : timestamp{timestamp}, model_id{model_id}, quantity{quantity} {};

    std::tm get_timestamp() const {
        return timestamp;
    }

    int get_model_id() const{
        return model_id;
    }

    int get_quantity() const{
        return quantity;
    }

    bool is_processed() {
        return processed;
    }

    void set_processed(bool val) {
        processed = val;
    }
};

std::ostream& operator << (std::ostream& stream, const Order& order);

#endif //INC_ORDER_H
