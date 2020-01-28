//
// Created by giacomo on 26/01/20.
//

#include "Stock.h"
#include "StockItem.h"

void StockItem::add(const int q) {
    quantity += q;
    availability += q;
}

int StockItem::reserve(const int q) {
    if (availability > q) {
        availability -= q;
        return q;
    }

    int tmp = availability;
    availability = 0;
    return tmp;
}

void StockItem::remove(const int q) {
    if (quantity < q) {
        throw Stock::OutOfStock();
    }

    quantity -= q;
}

std::ostream& operator<<(std::ostream &stream, const StockItem &item) {
    stream << "Componente: " << item.get_component_id() << ", quantità: " << item.get_quantity() << ", disponibilità: " << item.get_availability();

    return stream;
}
