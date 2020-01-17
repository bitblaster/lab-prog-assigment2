//
// Created by mozzicator on 16/01/20.
//

#include "Component.h"

int Component::getPrice(int quantity) const {
    if(quantity <= 0){
            return -1;
    }
    else{
        if(quantity <= 10){
            return price_1;
        }
        if(10 < quantity <= 50){
            return price_2;
        }
        if(quantity > 50){
            return price_3;
        }
    }
}

