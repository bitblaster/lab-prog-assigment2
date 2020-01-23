//
// Created by mozzicator on 16/01/20.
//

#ifndef INC_MODEL_H
#define INC_MODEL_H

#include <string>
#include <vector>
#include "Component.h"
#include "Entity.h"
#include "ComponentReference.h"

//TODO: definire copy/move constructors e operators!!!

class Model : public Entity {
    double price;
    std::vector<ComponentReference> components;

public:
    Model(const int id, const std::string name, const double price) : Entity(id, name), price {price} {}

    double get_price() const {
        return price;
    }

    const std::vector<ComponentReference>& get_components() const {
        return components;
    }

    void add_component(const ComponentReference &comp) {
        components.push_back(comp);
    }
};

std::ostream& operator << (std::ostream& stream, const Model& model);

#endif //INC_MODEL_H
