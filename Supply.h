//
// Created by mozzicator on 26/01/20.
//

#ifndef INC_SUPPLY_H
#define INC_SUPPLY_H


#include "Component.h"
#include "BatchPeriod.h"

// TODO capire come fare un set di supply in cui ;la chiave sia la combinazione di componente e batchperiod!
class Supply {
    const Component &component;
    const BatchPeriod delivery_period;
    int quantity;

public:
    Supply(const Component &component, const BatchPeriod &deliveryPeriod, int initialQuantity);

    const Component& get_component() const {
        return component;
    }

    const BatchPeriod &get_delivery_period() const {
        return delivery_period;
    }

    int get_quantity() const {
        return quantity;
    }

    bool operator==(const Supply &rhs) const;

    bool operator!=(const Supply &rhs) const;

    bool operator<(const Supply &rhs) const;

    bool operator>(const Supply &rhs) const;

    bool operator<=(const Supply &rhs) const;

    bool operator>=(const Supply &rhs) const;
};


#endif //INC_SUPPLY_H
