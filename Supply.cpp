//
// Created by mozzicator on 26/01/20.
//

#include "Supply.h"

Supply::Supply(const ComponentUsage &component, BatchPeriod &deliveryPeriod, int initialQuantity) : component{component}, delivery_period{deliveryPeriod} {
    quantity = initialQuantity > 0 ? initialQuantity : 0;
}
