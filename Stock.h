//
// Created by Giacomo Seno on 17/01/2020.
//

#ifndef INC_STOCK_H
#define INC_STOCK_H

#include <map>
#include "Component.h"
#include "StockItem.h"

class Stock { //componenti ordinati e arrivati ma non ancora utilizzati
    //mappa dei componenti
    // TODO per ogni componente dev'esserci la quantità in magazzino e la quantità disponibile
    // ovvero se un modello ha bisogno di un componente in maniera parziale lo deve poter "bloccare"
    // per evitare che si chieda la fornitura solo del delta di un  componente e poi un ordine successivo venga evaso
    // "rubando" il componente da sotto il naso e rimandando ancora l'ordine inevaso
    std::map<int, StockItem> items;

public:
    Stock() = default;
    void add (const Component& comp, int quantity);
    int reserve (const Component& comp, int quantity);
    void remove (const Component& comp, int quantity);
    int availability(const Component& comp) const;
    int availabile(const Component& comp) const;
    const std::map<int, StockItem>& get_items() const;

    class OutOfStock {};
};

#endif //INC_STOCK_H