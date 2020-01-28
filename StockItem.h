//
// Created by giacomo on 26/01/20.
//

#ifndef INC_STOCK_ITEM_H
#define INC_STOCK_ITEM_H

#include <ostream>
#include "Component.h"

class StockItem {
    int componentId;
    int quantity;
    int availability;

public:
    StockItem() = default;
    StockItem(const Component &comp, const int quantity) : componentId{comp.get_id()}, quantity{quantity}, availability{quantity} {}

    int get_component_id() const {
        return componentId;
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
