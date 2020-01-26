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

    Supply(const Component &component, BatchPeriod &deliveryPeriod, int initialQuantity);
};


#endif //INC_SUPPLY_H
