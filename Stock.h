/**
 * Stock.h
 * Scopo: Definere la classe che gestisca il magazzino delle componenti arrivate(StockItem), ma non utilizzate
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

class Stock {
    /**
     * mappa degli elementi del magazzino
     */
    std::map<int, std::unique_ptr<StockItem>> items;

public:
    /**
     * Costruttore di stock, crea una mappa vuota degli elementi
     */
    Stock() : items() {}

    /**
     * Aggiunge al magazzino le componenti arrivate
     * @param comp      componente da aggiungere
     * @param quantity  quantità da aggiungere al magazzino
     */
    void add(std::shared_ptr<const Component> comp, unsigned int quantity);

    /**
     * Riserva un numero definito di componenti senza rimuoverle dal magazzino
     * @param comp      componente da riservare
     * @param quantity  numero di componenti da riservare
     * @return quantità di componenti riservate
     */
    unsigned int reserve(std::shared_ptr<const Component> comp, unsigned int quantity);

    /**
     * Rimuove dal magazzino un numero definito di componenti
     * @param comp      componente da rimuovere
     * @param quantity  numero di componenti da rimuovere
     * @throw OutOfStock in caso venga richiesto di rimuovere piùà componenti rispetto a quelle disponibili
     */
    void remove(std::shared_ptr<const Component> comp, unsigned int quantity);

    /**
     * Controlla la disponibilità di una componente
     * @param comp        componente da verificare
     * @return quantità disponibile
     */
    unsigned int get_availability(std::shared_ptr<const Component> comp) const;

    /**
     * Ritorna la mappa dei componenti presenti in magazzino
     * @return mappa dei componenti in magazzino
     */
    const std::map<int, std::unique_ptr<StockItem>>& get_items() const;

    /**
     * classe per gestire l'eventualità di richiesta superiore ai componenti presenti
     */
    class OutOfStock {};
};

#endif //INC_STOCK_H