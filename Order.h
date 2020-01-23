//
// Created by giacomo on 17/01/20.
//

#ifndef INC_ORDER_H
#define INC_ORDER_H

#include "Model.h"
#include "Component.h"

class Order{
    bool timestamp;
    int model_id;
    int quantity;
    bool processed;

public:
    Order(bool timestamp, int model_id, int quantity) : timestamp{timestamp}, model_id{model_id}, quantity{quantity} {};

    bool get_timestamp() const;

    int get_model_id() const{
        return model_id;
    }

    int get_quantity() const{
        return quantity;
    }
};


#endif //INC_ORDER_H
