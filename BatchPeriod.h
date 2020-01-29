/*
 * BatchPeriod.h
 * Scopo: Definire la classe BatchPeriod che rappresenta mese e anno, per poi gestire ordini e avanzamento del processo
 * di produzione
 */

#ifndef INC_BATCHPERIOD_H
#define INC_BATCHPERIOD_H

#include <ostream>

// TODO gestire invarianti su mese e anno
/*
 * Classe che reappresenta un periodo mese-anno.
 *
 * Gli invarianti della classe sono:
 * -Year deve essere sempre maggiore di zero
 * -month non può essere maggiore di 11
 */

class BatchPeriod {
    int month; // come la struct tm: 0-11
    int year; // come la struct tm: anni dal 1900

    /*
     * Verifica che 0<= month <=11 e year >0
     */
    void check_validity();

public:
    BatchPeriod(int month, int year);

    int get_month() const {
        return month;
    }

    int get_year() const {
        return year;
    }
/*
 * Aggiunge a month il numero di mesi indicati, se month diventa > 11, incrementa year
 */
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
