//
// Created by mozzicator on 16/01/20.
//

#ifndef INC_COMPONENT_REFERENCE_H
#define INC_COMPONENT_REFERENCE_H


#include "Entity.h"
#include <string>

class ComponentReference : public Entity {
    int quantity;


public:
    ComponentReference(int id, std::string name, int quantity)
        : Entity(id, name) , quantity {quantity} {};

    int get_quantity() const {
        return quantity;
    }
};


#endif //INC_COMPONENT_REFERENCE_H
