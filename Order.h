//
// Created by giacomo on 17/01/20.
//

#ifndef INC_ORDER_H
#define INC_ORDER_H

#include <chrono>
#include "Model.h"
#include "Component.h"

class Order {
    std::time_t timestamp;
    int model_id;
    int quantity;
    bool processed;

public:
    Order(const std::time_t timestamp, const int model_id, const int quantity) : timestamp{timestamp}, model_id{model_id}, quantity{quantity} {};

    const std::time_t get_timestamp() const {
        return timestamp;
    }

    const std::tm get_localtime() const {
        return *localtime(&timestamp);
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

    bool in_month(const int month, const int year) const;

    bool operator<(const Order &rhs) const {
        return timestamp < rhs.timestamp;
    }
};

std::ostream& operator << (std::ostream& stream, const Order& order);

#endif //INC_ORDER_H
