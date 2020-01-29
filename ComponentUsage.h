/*
 * ComponentUsage.h
 * Scopo: Definire la classe ComponentUsage per rappresentare una componente all'interno di Model
 */
#ifndef INC_COMPONENT_USAGE_H
#define INC_COMPONENT_USAGE_H


#include "Part.h"
#include <string>
#include <memory>
#include "Component.h"

/*
 * Classe che rappresenta una compoente all'interno di un modello di elettrodomestico (Model).
 * La componente è rappresentata dalla classe Component, il nome indicato all'interno del modello rappresentato da una
 * stringa e la quantità necessaria per il modello rappresentato da valori int.
 * La componente, il nome nel modello e la quantità sono fissati in fase di costruzione e non possono essere modificati
 * in seguito.
 *
 * Gli invarianti della classe sono:
 *  - quantity > 0
 */
class ComponentUsage {
    std::shared_ptr<const Component> component;
    std::string name_in_model;
    unsigned int quantity;

public:
    ComponentUsage(std::shared_ptr<const Component> component, const std::string nameInModel, unsigned int quantity);

    const std::shared_ptr<const Component> get_component() const {
        return component;
    }

    const std::string get_name_in_model() const {
        return name_in_model;
    }

    /*
     * torna la quantità di componenti necessaria per la produzione del modello corrispondente
     */
    int get_quantity() const {
        return quantity;
    }

    bool operator<(const ComponentUsage &rhs) const {
        return component->get_months_to_delivery() < rhs.component->get_months_to_delivery();
    }
};


#endif //INC_COMPONENT_USAGE_H
