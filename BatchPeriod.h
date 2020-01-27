//
// Created by mozzicator on 26/01/20.
//

#ifndef INC_BATCHPERIOD_H
#define INC_BATCHPERIOD_H

#include <ostream>

// TODO gestire invarianti su mese e anno
class BatchPeriod {
    int month; // come la struct tm: 0-11
    int year; // come la struct tm: anni dal 1900

    void check_validity();

public:
    BatchPeriod(int month, int year);

    int get_month() const {
        return month;
    }

    int get_year() const {
        return year;
    }

    void add_months(unsigned int amount);

    BatchPeriod& operator++();       // Prefix increment operator.
    BatchPeriod operator++(int);     // Postfix increment operator.

    bool operator==(const BatchPeriod& rhs) const;
    bool operator!=(const BatchPeriod& b) const;

    bool operator<(const BatchPeriod &rhs) const;

    bool operator>(const BatchPeriod &rhs) const;

    bool operator<=(const BatchPeriod &rhs) const;

    bool operator>=(const BatchPeriod &rhs) const;
};

BatchPeriod operator+(BatchPeriod lhs, int months);
std::ostream& operator << (std::ostream& stream, const BatchPeriod& order);

#endif //INC_BATCHPERIOD_H
