//
// Created by mozzicator on 16/01/20.
//

#ifndef INC_MODEL_H
#define INC_MODEL_H

#include <string>
#include <set>
#include "Component.h"
#include "Part.h"
#include "ComponentUsage.h"

//TODO: definire copy/move constructors e operators!!!

class Model : public Part {
    double price;
    std::set<ComponentUsage> components;

public:
    Model() = default;
    Model(const int id, const std::string name, const double price) : Part(id, name), price {price} {}
    Model(const Model &model) = default;
    Model(Model &&model) = default;

    double get_price() const {
        return price;
    }

    const std::set<ComponentUsage>& get_components() const {
        return components;
    }

    void add_component(const ComponentUsage &comp) {
        components.insert(comp);
    }

    Model& operator=(Model&&) = default;
};

std::ostream& operator << (std::ostream& stream, const Model& model);

#endif //INC_MODEL_H
