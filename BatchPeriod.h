//
// Created by mozzicator on 26/01/20.
//

#ifndef INC_BATCHPERIOD_H
#define INC_BATCHPERIOD_H

// TODO gestire invarianti su mese e anno
class BatchPeriod {
    int month;
    int year;

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

    BatchPeriod& operator++();
        bool operator==(const BatchPeriod& rhs) const;
    bool operator!=(const BatchPeriod& b) const;

    bool operator<(const BatchPeriod &rhs) const;

    bool operator>(const BatchPeriod &rhs) const;

    bool operator<=(const BatchPeriod &rhs) const;

    bool operator>=(const BatchPeriod &rhs) const;
};

BatchPeriod operator+(BatchPeriod lhs, int months);

#endif //INC_BATCHPERIOD_H
