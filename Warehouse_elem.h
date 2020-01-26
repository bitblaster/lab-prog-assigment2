//
// Created by giacomo on 26/01/20.
//

#ifndef INC_02_APPROVVIGIONAMENTO_WAREHOUSE_ELEM_H
#define INC_02_APPROVVIGIONAMENTO_WAREHOUSE_ELEM_H

#include "Component.h"

class Warehouse_elem{
    Component component;
    int quantity;

public:
    Warehouse_elem(const Component& comp, int quantity) : component{comp}, quantity{quantity} {};

    int getComponentId() const{
        return component.get_id();
    }
    Component getComponent() const{
        return component;
    }

    int getQuantity()const{
        return quantity;
    };

    void increment(int a){
        quantity = quantity + a;
    }

    class OutofElem {};

    void decrement(int a){
        if(quantity-a < 0) throw OutofElem{};
        quantity = quantity-a;
    }


};
#endif //INC_02_APPROVVIGIONAMENTO_WAREHOUSE_ELEM_H
