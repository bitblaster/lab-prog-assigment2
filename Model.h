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
    std::set<std::shared_ptr<const ComponentUsage>> components;
    unsigned int max_delivery_months;

public:
    Model(const int id, const std::string name, const double price);

    double get_price() const {
        return price;
    }

    const std::set<std::shared_ptr<const ComponentUsage>>& get_components() const {
        return components;
    }

    void add_component(const std::shared_ptr<ComponentUsage> comp) {
        components.insert(comp);

        // Aggiorna, se necessario, il massimo numero di mesi
        if (comp->get_component()->get_months_to_delivery() > max_delivery_months)
            max_delivery_months = comp->get_component()->get_months_to_delivery();
    }

    unsigned int get_max_delivery_months() const {
        return max_delivery_months;
    }

    Model& operator=(Model&&) = default;
};

std::ostream& operator<<(std::ostream& stream, const Model& model);

#endif //INC_MODEL_H
