//
// Created by Giacomo Seno on 17/01/2020.
//

#include "Fund.h"

double Fund::increment(double a) {
    if (cash + a > 0){
        cash = cash + a;
        return cash;
    } else
        throw OutofCash{};
}