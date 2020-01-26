//
// Created by mozzicator on 26/01/20.
//

#ifndef INC_02_APPROVVIGIONAMENTO_SUPPLY_H
#define INC_02_APPROVVIGIONAMENTO_SUPPLY_H


#include "ComponentUsage.h"
#include "BatchPeriod.h"

// TODO capire come fare un set di supply in cui ;la chiave sia la combinazione di componente e batchperiod!
class Supply {
    const ComponentUsage &component;
    const BatchPeriod delivery_period; //periodo di arrivo componenti
    int quantity; //quantità di componenti in arrivo

    Supply(const ComponentUsage &component, BatchPeriod &deliveryPeriod, int initialQuantity);

   // BatchPeriod
};


#endif //INC_02_APPROVVIGIONAMENTO_SUPPLY_H
