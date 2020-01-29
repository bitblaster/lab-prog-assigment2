/*
 * Fund.h
 * Scopo: Definire la classe Fund.h che rappresenta e gestisce la cassa necessaria all'acquisto di componenti necessarie
 * alla produzione
 */

#ifndef INC_FUND_H
#define INC_FUND_H

#endif //INC_FUND_H

/*
 * Classe che rappresenta una cassa di un'azienda.
 * i soldi disponibili sono rappresentati da un valori double (cash).
 *
 * Gli invarianti della classe sono:
 *  - cash deve essere sempre >= 0
 */

class Fund {
    double cash;
public:
    Fund () : cash {0} {}
    Fund (double fund) : cash {fund} {}

    /*
     * @param a soldi da aggiungere in cassa
     * Aggiunge a alla cassa attuale
     */
    void increment(double a){
        cash = cash+a;
    }

    /*
     * @param a soldi da sottrarre alla cassa
     * throw OutOfCash nel caso i soldi da sottrarre siano maggiori della disponibilità della cassa
     */
    void decrement(double a){
        if(cash-a < 0) throw OutofCash{};
        cash = cash-a;
    }

    class OutofCash {};

    double get_cash() const {
        return cash;
    }
};