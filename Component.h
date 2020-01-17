//
// Created by mozzicator on 16/01/20.
//

#ifndef INC_02_APPROVVIGIONAMENTO_COMPONENT_H
#define INC_02_APPROVVIGIONAMENTO_COMPONENT_H


#include "Entity.h"
#include <string>

class Component : public Entity{
    int month;
    int price_1; //price per quantita<11
    int price_2; //price per quantita 10<quantità<50
    int price_3; //price per quantita 51+


public:
    Component();
    Component(int id, std::string name, int month, int price_1, int price_2 , int price_3 );

    int getMonth() const;
    int getPrice(int quantity) const;

};


#endif //INC_02_APPROVVIGIONAMENTO_COMPONENT_H
