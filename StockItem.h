//
// Created by giacomo on 26/01/20.
//

#ifndef INC_STOCK_ITEM_H
#define INC_STOCK_ITEM_H

#include <ostream>
#include "Component.h"

class StockItem {
    std::shared_ptr<const Component> component;
    unsigned int quantity;
    unsigned int availability;

public:
    StockItem(std::shared_ptr<const Component> component, unsigned int quantity) : component{component}, quantity{quantity}, availability{quantity} {}

    const std::shared_ptr<const Component> get_component() const {
        return component;
    }

    int get_quantity() const {
        return quantity;
    }

    int get_availability() const {
        return availability;
    }

    void add(const int q);
    int reserve(const int q);
    void remove(const int q);
};

std::ostream& operator <<(std::ostream& stream, const StockItem& item);
#endif //INC_STOCK_ITEM_H
