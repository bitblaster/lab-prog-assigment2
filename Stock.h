/**
 * Stock.h
 * Scopo: Definere la classe che gestisca il magazzino delle componenti arrivate, ma non utilizzate
 *
 * @author Giacomo Vettoretti, 1187540
 * @version 1.0 29/01/20
 */

#ifndef INC_STOCK_H
#define INC_STOCK_H

#include <map>
#include <memory>
#include "Component.h"
#include "StockItem.h"

class Stock { //componenti ordinati e arrivati ma non ancora utilizzati
    //mappa dei componenti
    std::map<int, std::unique_ptr<StockItem>> items;

public:
    Stock() : items() {}

    void add(std::shared_ptr<const Component> comp, unsigned int quantity);
    unsigned int reserve(std::shared_ptr<const Component> comp, unsigned int quantity);
    void remove(std::shared_ptr<const Component> comp, unsigned int quantity);
    unsigned int get_availability(std::shared_ptr<const Component> comp) const;
    const std::map<int, std::unique_ptr<StockItem>>& get_items() const;

    class OutOfStock {};
};

#endif //INC_STOCK_H