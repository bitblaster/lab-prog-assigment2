//
// Created by mozzicator on 26/01/20.
//

#include "Supply.h"

Supply::Supply(const Component &component, const BatchPeriod &deliveryPeriod, int initialQuantity) : component{component}, delivery_period{deliveryPeriod} {
    quantity = initialQuantity > 0 ? initialQuantity : 0;
}

bool Supply::operator==(const Supply &rhs) const {
    return delivery_period == rhs.delivery_period && component.get_id() == rhs.component.get_id();
}

bool Supply::operator!=(const Supply &rhs) const {
    return !(rhs == *this);
}

bool Supply::operator<(const Supply &rhs) const {
    return delivery_period < rhs.delivery_period || delivery_period == rhs.delivery_period && component.get_id() < rhs.component.get_id();
}

bool Supply::operator>(const Supply &rhs) const {
    return rhs < *this;
}

bool Supply::operator<=(const Supply &rhs) const {
    return !(rhs < *this);
}

bool Supply::operator>=(const Supply &rhs) const {
    return !(*this < rhs);
}
