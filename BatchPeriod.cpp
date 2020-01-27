//
// Created by mozzicator on 26/01/20.
//

#include <string>
#include <stdexcept>
#include "BatchPeriod.h"

using namespace std;

BatchPeriod::BatchPeriod(int month, int year) : month{month}, year{year} {
    check_validity();
}

void BatchPeriod::add_months(unsigned int amount) {
    month += amount;
    if(month > 11) {
        year += month / 12;
        month %= 12;
    }
}

void BatchPeriod::check_validity() {
    if(month < 0 || month > 11 || year < 0)
        throw invalid_argument("invalid month " + to_string(month));
}

BatchPeriod &BatchPeriod::operator++() {
    add_months(1);
    return *this;
}

BatchPeriod BatchPeriod::operator++(int) {
    BatchPeriod temp = *this;
    ++*this;
    return temp;
}

bool BatchPeriod::operator==(const BatchPeriod &rhs) const{
    return month == rhs.get_month() && year == rhs.get_year();
}

bool BatchPeriod::operator!=(const BatchPeriod &rhs) const{
    return !(*this == rhs);
}

bool BatchPeriod::operator<(const BatchPeriod &rhs) const {
    return year < rhs.year || year == rhs.year && month < rhs.month;
}

bool BatchPeriod::operator>(const BatchPeriod &rhs) const {
    return rhs < *this;
}

bool BatchPeriod::operator<=(const BatchPeriod &rhs) const {
    return !(rhs < *this);
}

bool BatchPeriod::operator>=(const BatchPeriod &rhs) const {
    return !(*this < rhs);
}

BatchPeriod operator+(BatchPeriod lhs, int months) {
    BatchPeriod ret(lhs.get_month(), lhs.get_year());
    ret.add_months(months);
    return lhs; // return the result by value (uses move constructor)
}

std::ostream &operator<<(std::ostream &stream, const BatchPeriod &period) {
    stream << period.get_month() << '/' << period.get_year();
    return stream;
}


