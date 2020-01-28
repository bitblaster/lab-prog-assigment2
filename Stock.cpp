//
// Created by Giacomo Seno on 17/01/2020.
//

#include <iostream>
#include "Stock.h"
#include "Component.h"

using namespace std;

void Stock::add(const Component& comp, int quantity) {
    map<int, StockItem>::iterator it = items.find(comp.get_id());
    if (it != items.end()) {
        it->second.add(quantity);
    }
    else {
        items[comp.get_id()] = StockItem(comp, quantity);
    }
}

int Stock::reserve(const Component& comp, int quantity) {
    map<int, StockItem>::iterator it = items.find(comp.get_id());
    if (it != items.end())
        return it->second.reserve(quantity);

    return 0;
}

void Stock::remove(const Component& comp, int quantity) {
    try {
        items[comp.get_id()].remove(quantity);
    } catch (out_of_range e) {
        throw Stock::OutOfStock();
    }
}

const std::map<int, StockItem> &Stock::get_items() const {
    return items;
}
