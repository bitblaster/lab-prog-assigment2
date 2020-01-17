//
// Created by Giacomo Seno on 17/01/2020.
//

#include "Storage.h"
#include "Component.h"

void Storage::add(Component comp){
    v.push_back(comp);
}

Component Storage::remove(Component comp){
    for (int i = 0; i < v.size(); i++){
        if (v[i] == comp){
            v.erase(i);
            return comp;
        }
    }
    return null;
}



