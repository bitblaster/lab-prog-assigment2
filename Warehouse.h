//
// Created by Giacomo Seno on 17/01/2020.
//

#ifndef INC_WAREHOUSE_H
#define INC_WAREHOUSE_H

#include <vector>
#include "Component.h"
#include "Warehouse_elem.h"

class Warehouse { //componenti ordinati e arrivati ma non ancora utilizzati
    //mappa dei componenti
    std::vector<Warehouse_elem> v;
public:
    Warehouse() = default;
    void add (const Component& comp, int quantity);
    Component remove (const Component& comp, int quantity);
    class OutofElem {};
    class ElemNotFount {};
    int getSize() const {
        return v.size();
    }
    Component get (int i) {
        return v[i].getComponent();
    }
    Component operator[] (int i){
        return v[i].getComponent();
    }
};

#endif //INC_WAREHOUSE_H