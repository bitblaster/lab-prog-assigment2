//
// Created by mozzicator on 26/01/20.
//

#ifndef INC_BATCHPERIOD_H
#define INC_BATCHPERIOD_H

// TODO gestire invarianti su mese e anno
class BatchPeriod {
    int month;
    int year;

public:
    BatchPeriod(int month, int year) : month{month}, year{year} {}

    int get_month() const {
        return month;
    }

    int get_year() const {
        return year;
    }

    bool is_valid() {
        return month > 0 && year > 0;
    }

    // implementare operatore + (per il delivery) e < (per il confronto)
    BatchPeriod& operator++();
};


#endif //INC_BATCHPERIOD_H
