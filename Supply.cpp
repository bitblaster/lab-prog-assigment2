/**
 * Implementazione della classe Supply
 *
 * @author Giacomo Seno
 * @version 1.0 29/01/20
 */

#include "Supply.h"

Supply::Supply(const std::shared_ptr<const Component> component, unsigned int deliveryPeriod, unsigned int initialQuantity) : component{component}, delivery_period{deliveryPeriod} {
    quantity = initialQuantity;
}

bool Supply::operator==(const Supply &rhs) const {
    return delivery_period == rhs.delivery_period && (component==rhs.component || component && rhs.component && component->get_id() == rhs.component->get_id());
}

bool Supply::operator!=(const Supply &rhs) const {
    return !(rhs == *this);
}

bool Supply::operator<(const Supply &rhs) const {
    return delivery_period < rhs.delivery_period || delivery_period == rhs.delivery_period && component && rhs.component && component->get_id() < rhs.component->get_id();
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
