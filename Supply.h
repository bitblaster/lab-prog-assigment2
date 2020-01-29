//
// Created by mozzicator on 26/01/20.
//

#ifndef INC_SUPPLY_H
#define INC_SUPPLY_H


#include <memory>
#include "Component.h"
#include "BatchPeriod.h"

// TODO capire come fare un set di supply in cui ;la chiave sia la combinazione di componente e batchperiod!
class Supply {
    std::shared_ptr<const Component> component;
    const unsigned int delivery_period;
    unsigned int quantity;

public:
    Supply(std::shared_ptr<const Component> component, unsigned int deliveryPeriod, unsigned int initialQuantity=0);

    const std::shared_ptr<const Component> get_component() const {
        return component;
    }

    const unsigned int &get_delivery_period() const {
        return delivery_period;
    }

    unsigned int get_quantity() const {
        return quantity;
    }

    void add_quantity(unsigned int q) {
        quantity += q;
    }

    bool operator==(const Supply &rhs) const;

    bool operator!=(const Supply &rhs) const;

    bool operator<(const Supply &rhs) const;

    bool operator>(const Supply &rhs) const;

    bool operator<=(const Supply &rhs) const;

    bool operator>=(const Supply &rhs) const;
};


#endif //INC_SUPPLY_H
