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


bool BatchPeriod::operator<(const BatchPeriod& b) const{
    if(year < b.get_year()) return true;
    if(year == b.get_year())return month < b.get_month();
    return false;

}

bool BatchPeriod::operator==(const BatchPeriod &b) const{
    return month==b.get_month() && year==b.get_year();
}

bool BatchPeriod::operator!=(const BatchPeriod &b) const{
    return !(month==b.get_month() && year==b.get_year());
}


