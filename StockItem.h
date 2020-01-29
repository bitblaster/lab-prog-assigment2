/**
 * StockItem.h
 * Scopo: Definere la classe che definisca il tipo degli elementi del magazzino
 *
 * @author Giacomo Vettoretti, 1187540
 * @version 1.0 29/01/20
 */

#ifndef INC_STOCK_ITEM_H
#define INC_STOCK_ITEM_H

/**
 * Gli invarianti di classe sono:
 *  - quantity>0
 *  - availabiity non inferiore a 0
 */
#include <ostream>
#include <utility>
#include "Component.h"

class StockItem {
    const std::shared_ptr<const Component> component;
    unsigned int quantity;
    unsigned int availability;

public:
    /**
     * Costruttore della classe StockItem, inizializza un oggetto di tipo StockItem con una componente, una quantità e
     * la sua disponibilità
     *
     * @param component  componente
     * @param quantity   quantità
     */
    StockItem(std::shared_ptr<const Component> component, unsigned int quantity) : component{ std::move(component) }, quantity{quantity}, availability{quantity} {}

    /**
     * Ritorna la componente salvata in StockItem
     * @return component
     */
    const std::shared_ptr<const Component> get_component() const {
        return component;
    }

    /**
     * Ritorna la quantità di componenti presenti
     * @return quantity
     */
    unsigned int get_quantity() const {
        return quantity;
    }

    /**
     * ritorna il numero di componenti effettivamente disponibili
     * @return availability
     */
    unsigned int get_availability() const {
        return availability;
    }

    /**
     * Aggiunge q componenti
     * @param q
     */
    void add(unsigned int q);

    /**
     * Riserva q componenti
     * @param q     componenti da riservare
     * @return quantità di componenti riservate
     */
    int reserve(unsigned int q);

    /**
     * Rimuove q componenti
     * @param q     componenti da rimuovere
     * @throw OutOfStock se q> delle componenti presenti (quantity)
     */
    void remove(unsigned int q);
};

/**
 * Overload operatore <<
 * @param stream    stream su cui stampare
 * @param item      Elementdo da stampare
 * @return stream
 */
std::ostream& operator <<(std::ostream& stream, const StockItem& item);
#endif //INC_STOCK_ITEM_H
