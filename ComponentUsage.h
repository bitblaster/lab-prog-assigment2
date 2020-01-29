/**
 * ComponentUsage.h
 * Scopo: Definire la classe ComponentUsage per rappresentare un componente all'interno di Model
 * @author Giacomo Seno, 1187124
 * @version 1.0 29/01/20
 */

#ifndef INC_COMPONENT_USAGE_H
#define INC_COMPONENT_USAGE_H

#include "Part.h"
#include <string>
#include <memory>
#include "Component.h"

/**
 * Classe che rappresenta un componente all'interno di un modello di elettrodomestico (Model).
 * Il componente è rappresentata dalla classe Component, il nome indicato all'interno del modello rappresentato da una
 * stringa e la quantità necessaria per il modello rappresentato da valori int.
 * Il componente, il nome nel modello e la quantità sono fissati in fase di costruzione e non possono essere modificati
 * in seguito.
 *
 * Gli invarianti della classe sono:
 * - quantity > 0
 */
class ComponentUsage {
    std::shared_ptr<const Component> component;
    std::string name_in_model;
    unsigned int quantity;

public:
    /**
     * Costruttore di ComponentUsage
     * @param component         componente a cui ComponentUsage si riferisce
     * @param nameInModel       stringa che definisce il componente all'interno del modello
     * @param quantity          quantità del componente necessaria per quello specifico modello
     */
    ComponentUsage(std::shared_ptr<const Component> component, const std::string nameInModel, unsigned int quantity);

    /**
     * Ritorna il componente
     * @return component
     */
    const std::shared_ptr<const Component> get_component() const {
        return component;
    }

    /**
     * Ritorna il nome del componente indicato all'interno del modello
     * @return name_in_model
     */
    const std::string& get_name_in_model() const {
        return name_in_model;
    }

    /**
     * Ritorna la quantità del componente necessaria per il Modello
     * @return quantity
     */
    int get_quantity() const {
        return quantity;
    }

    /**
     * Overload dell'operatore <
     * @param rhs       oggetto da confrontare
     * @return bool     true o false a seconda che il tempo di consegna di uno sia minore
     *                  o maggiore del tempo di consegna dell'altro
     */
    bool operator<(const ComponentUsage &rhs) const {
        return component->get_months_to_delivery() < rhs.component->get_months_to_delivery();
    }
};


#endif //INC_COMPONENT_USAGE_H
