//
// Created by mozzicator on 16/01/20.
//

#ifndef INC_COMPONENT_H
#define INC_COMPONENT_H


#include "Entity.h"
#include <string>

class Component : public Entity {
    int months_to_delivery;
    double price_1; // price per quantita<11
    double price_2; // price per quantita 10<quantità<50
    double price_3; // price per quantita 51+


public:
    Component(int id, std::string name, int months_to_delivery, double price_1, double price_2 , double price_3)
        : Entity(id, name) , months_to_delivery {months_to_delivery} , price_1{price_1} , price_2{price_2} , price_3{price_3} {};

    int get_months_to_delivery() const {
        return months_to_delivery;
    }

    double get_price(const int quantity) const;
};

std::ostream& operator << (std::ostream& stream, const Component& component);

#endif //INC_COMPONENT_H
