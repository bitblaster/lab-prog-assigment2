//
// Created by giacomo on 17/01/20.
//

#include <iomanip>
#include "Order.h"

using namespace std;

Order::Order(unsigned int timestamp, const shared_ptr<const Model> model, const unsigned int quantity)
    : timestamp{timestamp}, model{model}, quantity{quantity} {}

bool Order::is_component_fullfilled(const std::shared_ptr<const ComponentUsage> comp) const {
    try {
        return reserved_components.at(comp->get_component()->get_id()) == comp->get_quantity() * quantity;
    } catch (out_of_range e) {
        return false;
    }
}

void Order::add_reserved_quantity(const std::shared_ptr<const ComponentUsage> comp, unsigned int quantity) {
    map<int, int>::iterator it = reserved_components.find(comp->get_component()->get_id());
    if (it != reserved_components.end())
        it->second += quantity;
    else
        reserved_components[comp->get_component()->get_id()] = quantity;
}

unsigned int Order::get_reserved_quantity(const std::shared_ptr<const ComponentUsage> comp) const {
    try {
        return reserved_components.at(comp->get_component()->get_id());
    } catch (out_of_range e) {
        return 0;
    }
}

ostream& operator <<(ostream& stream, const Order& order) {
    stream << "mese: " << order.get_timestamp() << ", modello: " << order.get_model()->get_id() << ", quantità:" << order.get_quantity() << ", componenti: ";
    for (auto c : order.get_model()->get_components()) {
        stream << '(' << *c->get_component() << ", quantità: " << c->get_quantity() << ") ";
    }
    return stream;
}
