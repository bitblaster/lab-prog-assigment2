//
// Created by Giacomo Seno on 17/01/2020.
//

#include "Warehouse.h"
#include "Component.h"

void Warehouse::add(const Component& comp, int quantity){
    for (int i = 0; i < v.size(); i++){
        if (v[i].getComponentId() == comp.get_id()){
            if(v[i].getQuantity() !=0){
                v[i].increment(quantity);
                return;
            }
            Warehouse_elem elem(comp,quantity);
            v.push_back(elem);
        }
    }
}

Component Warehouse::remove(const Component& comp, int quantity){
    for (int i = 0; i < v.size(); i++){
        if (v[i].getComponentId() == comp.get_id()){
            if(v[i].getQuantity()-quantity < 0) throw OutofElem{};

            v[i].decrement(quantity);
            return v[i].getComponent();
        }
    }
    throw ElemNotFount{};
}



