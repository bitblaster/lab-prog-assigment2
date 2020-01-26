//
// Created by mozzicator on 16/01/20.
//

#ifndef INC_COMPONENT_H
#define INC_COMPONENT_H


#include "Part.h"
#include <string>

class Component : public Part {
    int months_to_delivery;
    double price_1; // price per quantita<11
    double price_2; // price per quantita 10<quantità<50
    double price_3; // price per quantita 51+

public:
    Component() = default;
    Component(int id, std::string name, int months_to_delivery, double price_1, double price_2 , double price_3)
        : Part(id, name) , months_to_delivery {months_to_delivery} , price_1{price_1} , price_2{price_2} , price_3{price_3} {}
    //Component(const Component &) = default;
    //Component(Component &&) = default;

    int get_months_to_delivery() const {
        return months_to_delivery;
    }

    double get_price(const int quantity) const;

    //Component& operator=(const Component &) = default;
};

std::ostream& operator << (std::ostream& stream, const Component& component);

#endif //INC_COMPONENT_H
