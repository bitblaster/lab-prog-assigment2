//
// Created by mozzicator on 16/01/20.
//

#include <ostream>
#include "Component.h"

using namespace std;

unsigned int Component::get_suggested_quantity(const unsigned int minimumQuantity) {
    for (int threshold : kQuantityThresholds) {
        if(minimumQuantity < threshold) {
            if (minimumQuantity > threshold - kQuantityTolerance)
                return threshold;
            break;
        }
    }

    return minimumQuantity;
}

double Component::get_price(const unsigned int quantity) const {
    for (int i=0; i<kQuantityThresholdCount; i++) {
        if(quantity < kQuantityThresholds[i])
            return prices[i];
    }
    return prices[kQuantityThresholdCount];
}

ostream& operator <<(ostream& stream, const Component& component) {
    stream << component.get_id() << ',' << component.get_name();
    return stream;
}
