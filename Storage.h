//
// Created by Giacomo Seno on 17/01/2020.
//

#ifndef INC_STORAGE_H
#define INC_STORAGE_H

#endif //INC_STORAGE_H

#include <vector>
#include "Component.h"

class Storage { //componenti ordinati e arrivati ma non ancora utilizzati
    //mappa dei componenti
    std::vector<Component> v;
public:
    Storage() {}
    void add (Component comp);
    Component remove (Component comp);
    int getSize() const {
        return v.size();
    }
    Component get (int i) {
        return v[i];
    }
    Component operator[] (int i){
        return v[i];
    }
};
