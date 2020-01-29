//
// Created by giacomo on 17/01/20.
//

#include <iomanip>
#include "Order.h"

using namespace std;

Order::Order(unsigned int timestamp, const shared_ptr<const Model> model, const unsigned int quantity)
    : timestamp{timestamp}, model{model}, quantity{quantity}, reserved_components(), requested_components() {}

bool Order::is_component_fullfilled(const std::shared_ptr<const ComponentUsage> comp) const {
    try {
        return reserved_components.at(comp->get_component()->get_id()) == comp->get_quantity() * quantity;
    } catch (out_of_range e) {
        return false;
    }
}

void Order::add_reserved_quantity(const std::shared_ptr<const ComponentUsage> comp, unsigned int quantity) {
    unsigned int oldQuantity = reserved_components[comp->get_component()->get_id()];
    reserved_components[comp->get_component()->get_id()] = oldQuantity + quantity;
}

unsigned int Order::get_reserved_quantity(const std::shared_ptr<const ComponentUsage> comp) const {
    try {
        return reserved_components.at(comp->get_component()->get_id());
    } catch (out_of_range e) {
        return 0;
    }
}

void Order::add_requested_quantity(const std::shared_ptr<const ComponentUsage> comp, unsigned int quantity) {
    unsigned int oldQuantity = requested_components[comp->get_component()->get_id()];
    requested_components[comp->get_component()->get_id()] = oldQuantity + quantity;
}

unsigned int Order::get_requested_quantity(const std::shared_ptr<const ComponentUsage> comp) const {
    try {
        return requested_components.at(comp->get_component()->get_id());
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
