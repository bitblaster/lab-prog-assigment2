//
// Created by Giacomo Seno on 17/01/2020.
//

#include <iostream>
#include "Stock.h"
#include "Component.h"

using namespace std;

void Stock::add(const std::shared_ptr<const Component> comp, unsigned int quantity) {
    auto it = items.find(comp->get_id());
    if (it != items.end())
        it->second->add(quantity);
    else
        items[comp->get_id()] = make_unique<StockItem>(comp, quantity);
}

unsigned int Stock::reserve(const std::shared_ptr<const Component> comp, unsigned int quantity) {
    auto it = items.find(comp->get_id());
    if (it != items.end())
        return it->second->reserve(quantity);

    return 0;
}

void Stock::remove(const std::shared_ptr<const Component> comp, unsigned int quantity) {
    auto it = items.find(comp->get_id());
    if (it == items.end())
        throw Stock::OutOfStock();

    it->second->remove(quantity);
}

unsigned int Stock::get_availability(const std::shared_ptr<const Component> comp) const {
    auto it = items.find(comp->get_id());
    if (it != items.end())
        return it->second->get_availability();

    return 0;
}

const std::map<int, std::unique_ptr<StockItem>>& Stock::get_items() const {
    return items;
}
