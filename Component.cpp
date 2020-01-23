//
// Created by mozzicator on 16/01/20.
//

#include <ostream>
#include "Component.h"

using namespace std;

double Component::get_price(const int quantity) {
    if(quantity <= 0){
            return -1;
    }
    else{
        if(quantity <= 10) {
            return price_1;
        }
        if(10 < quantity <= 50) {
            return price_2;
        }
        if(quantity > 50) {
            return price_3;
        }
    }
}

ostream& operator <<(ostream& stream, const Component& comp) {
    stream << comp.get_id() << ',' << comp.get_name();
    return stream;
}
