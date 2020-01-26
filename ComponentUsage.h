//
// Created by mozzicator on 16/01/20.
//

#ifndef INC_COMPONENT_USAGE_H
#define INC_COMPONENT_USAGE_H


#include "Part.h"
#include <string>

class ComponentUsage {
    const Component &component;
    const std::string name_in_model;
    int quantity;


public:
    ComponentUsage(const Component &component, const std::string nameInModel, int quantity);

    int get_quantity() const {
        return quantity;
    }

    bool operator<(const ComponentUsage &rhs) const {
        return component.get_months_to_delivery() < rhs.component.get_months_to_delivery();
    }
};


#endif //INC_COMPONENT_USAGE_H
