//
// Created by giacomo on 17/01/20.
//

#ifndef INC_02_APPROVVIGIONAMENTO_ORDER_H
#define INC_02_APPROVVIGIONAMENTO_ORDER_H

#include "Model.h"
#include "Component.h"
#include "Date.h"

class Order{
    Date timestamp;
    int model_id;
    int quantity;

public:
    Order(Date timestamp, int model_id, int quantity) : timestamp{timestamp}, model_id{model_id}, quantity{quantity} {};

    Date getTimestamp() const;

    int getOrderedId() const{
        return model_id;
    }

    int getQuantity() const{
        return quantity;
    }
};


#endif //INC_02_APPROVVIGIONAMENTO_ORDER_H
