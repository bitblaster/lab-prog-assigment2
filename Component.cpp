//
// Created by mozzicator on 16/01/20.
//

#include <ostream>
#include "Component.h"

using namespace std;

double Component::get_price(const int quantity) const {
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

ostream& operator <<(ostream& stream, const Component& component) {
    stream << component.get_id() << ',' << component.get_name();
    return stream;
}
