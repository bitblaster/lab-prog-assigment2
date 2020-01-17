//
// Created by Giacomo Seno on 17/01/2020.
//

#ifndef INC_02_APPROVVIGIONAMENTO_FUND_H
#define INC_02_APPROVVIGIONAMENTO_FUND_H

#endif //INC_02_APPROVVIGIONAMENTO_FUND_H

class Fund {
    double cash;
public:
    Fund () : cash {0} {}
    Fund (int fund) : cash {fund} {}
    double increment(double a);
    class OutofCash {};
    double getCash() const {
        return cash;
    }
};