//
// Created by mozzicator on 26/01/20.
//

#include "BatchPeriod.h"

BatchPeriod& BatchPeriod::operator++() {
    ++month;
    if(month > 12) {
        month = 1;
        ++year;
    }

    return *this;
}