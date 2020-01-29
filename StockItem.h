//
// Created by giacomo on 26/01/20.
//

#ifndef INC_STOCK_ITEM_H
#define INC_STOCK_ITEM_H

#include <ostream>
#include <utility>
#include "Component.h"

class StockItem {
    const std::shared_ptr<const Component> component;
    unsigned int quantity;
    unsigned int availability;

public:
    StockItem(std::shared_ptr<const Component> component, unsigned int quantity) : component{ std::move(component) }, quantity{quantity}, availability{quantity} {}

    const std::shared_ptr<const Component> get_component() const {
        return component;
    }

    unsigned int get_quantity() const {
        return quantity;
    }

    unsigned int get_availability() const {
        return availability;
    }

    void add(unsigned int q);
    int reserve(unsigned int q);
    void remove(unsigned int q);
};

std::ostream& operator <<(std::ostream& stream, const StockItem& item);
#endif //INC_STOCK_ITEM_H
