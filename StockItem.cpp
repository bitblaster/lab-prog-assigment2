//
// Created by giacomo on 26/01/20.
//

#include "Stock.h"
#include "StockItem.h"

void StockItem::add(const unsigned int q) {
    quantity += q;
    availability += q;
}

int StockItem::reserve(const unsigned int q) {
    if (availability > q) {
        availability -= q;
        return q;
    }

    int tmp = availability;
    availability = 0;
    return tmp;
}

void StockItem::remove(const unsigned int q) {
    if (quantity < q) {
        throw Stock::OutOfStock();
    }

    quantity -= q;
}

std::ostream& operator<<(std::ostream &stream, const StockItem &item) {
    stream << "Componente: " << *item.get_component() << ", quantità: " << item.get_quantity() << ", disponibilità: " << item.get_availability();

    return stream;
}
