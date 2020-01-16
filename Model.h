//
// Created by mozzicator on 16/01/20.
//

#ifndef INC_02_APPROVVIGIONAMENTO_MODEL_H
#define INC_02_APPROVVIGIONAMENTO_MODEL_H

#include <string>
#include <vector>
#include "Component.h"
#include "Entity.h"

class Model : public Entity {
    double price;
    std::vector<Component> components;

public:
    Model(int id, std::string name, double price) : Entity(id, name), price {price} {}

    double getPrice() const {
        return price;
    }
};


#endif //INC_02_APPROVVIGIONAMENTO_MODEL_H
