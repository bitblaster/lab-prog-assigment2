/**
 *  Supply.h
 *  Scopo: Definire la classe Supply che rappresenta la fornitura di un solo tipo di componenti
 *
 *  @author Giacomo Seno, 1187124
 *  @version 1.0 29/01/20
 */

#ifndef INC_SUPPLY_H
#define INC_SUPPLY_H

#include <memory>
#include "Component.h"

/**
 * Gli invarianti della classe sono:
 * - delivery_period > 0
 * - quantity > 0
 */
class Supply {
    std::shared_ptr<const Component> component;
    const unsigned int delivery_period;
    unsigned int quantity;

public:
    /**
     * Costruttore di Supply
     * @param component         componente da acquistare
     * @param deliveryPeriod    tempo di consegna previsto
     * @param initialQuantity   quantità iniziale presente
     */
    Supply(std::shared_ptr<const Component> component, unsigned int deliveryPeriod, unsigned int initialQuantity=0);

    /**
     * Ritorna il componente che deve essere acquistato
     * @return il tipo di componente
     */
    const std::shared_ptr<const Component> get_component() const {
        return component;
    }

    /**
     * Ritorna il tempo di consegna previsto per quel dato componente
     * @return il tempo di consegna
     */
    const unsigned int &get_delivery_period() const {
        return delivery_period;
    }

    /**
     * Ritorna la quantità di componenti component che devono essere acquistati
     * @return quantità presente
     */
    unsigned int get_quantity() const {
        return quantity;
    }

    /**
     * Aggiunge una certa quantità al numero di componenti component che devono essere acquistati
     * @param q     incremento della quantità di un componente da comprare
     */
    void add_quantity(unsigned int q) {
        quantity += q;
    }

    /**
     * Overload dell'operatore ==
     */
    bool operator==(const Supply &rhs) const;

    /**
     * Overload dell'operatore !=
     */
    bool operator!=(const Supply &rhs) const;

    /**
     * Overload dell'operatore <
     */
    bool operator<(const Supply &rhs) const;

    /**
     * Overload dell'operatore >
     */
    bool operator>(const Supply &rhs) const;

    /**
     * Overload dell'operatore <=
     */
    bool operator<=(const Supply &rhs) const;

    /**
     * Overload dell'operatore >=
     */
    bool operator>=(const Supply &rhs) const;
};


#endif //INC_SUPPLY_H
