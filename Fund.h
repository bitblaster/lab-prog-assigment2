//
// Created by Giacomo Seno on 17/01/2020.
//

#ifndef INC_FUND_H
#define INC_FUND_H

#endif //INC_FUND_H

class Fund {
    double cash;
public:
    Fund () : cash {0} {}
    Fund (double fund) : cash {fund} {}

    void increment(double a){
        cash = cash+a;
    }
    void decrement(double a){
        if(cash-a < 0) throw OutofCash{};
        cash = cash-a;
    }

    class OutofCash {};

    double get_cash() const {
        return cash;
    }
};