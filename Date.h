//
// Created by giacomo on 17/01/20.
//

#ifndef INC_02_APPROVVIGIONAMENTO_DATE_H
#define INC_02_APPROVVIGIONAMENTO_DATE_H

class Date{
    class Invalid{};
    int d;
    int m;
    int y;

public:
    Date() : d{0}, m{0}, y{0} {};
    Date(int dd, int mm, int yy) : d{dd}, m{mm}, y{yy} {
        if(!is_date(dd,mm,yy)) throw Invalid{};
    };

    int day() const{
      return d;
    };
    int month() const{
        return m;
    }
    int year() const {
        return y;
    }

    void add_day(int n);
    void add_month(int n);
    void add_year(int n);
};

bool is_date(int dd, int mm, int yy);
bool leapyear(int y);

#endif //INC_02_APPROVVIGIONAMENTO_DATE_H
