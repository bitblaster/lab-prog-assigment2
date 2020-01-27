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
    // TODO per ogni componente dev'esserci la quantità in magazzino e la quantità disponibile
    // ovvero se un modello ha bisogno di un componente in maniera parziale lo deve poter "bloccare"
    // per evitare che si chieda la fornitura solo del delta di un  componente e poi un ordine successivo venga evaso
    // "rubando" il componente da sotto il naso e rimandando ancora l'ordine inevaso
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
    Warehouse_elem getElement(int i) const
    {
        return v[i];
    }

    Warehouse_elem operator[] (int i) const{
        return v[i];
    }
};

std::ostream& operator << (std::ostream& stream, const Warehouse& warehouse);
#endif //INC_WAREHOUSE_H