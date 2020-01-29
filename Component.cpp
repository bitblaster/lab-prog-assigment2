//
// Created by mozzicator on 16/01/20.
//

#include <ostream>
#include "Component.h"

using namespace std;

Component::Component(int id, string name, int months_to_delivery, double price_1, double price_2, double price_3)
        : Part(id, name) , months_to_delivery {months_to_delivery}, prices {price_1, price_2, price_3} { }

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
            return prices[i] * quantity;
    }
    return prices[kQuantityThresholdCount] * quantity;
}

ostream& operator <<(ostream& stream, const Component& component) {
    stream << component.get_id() << ", " << component.get_name();
    return stream;
}
