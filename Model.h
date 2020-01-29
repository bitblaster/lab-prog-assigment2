/**
 * Model.h
 * Scopo: Definire una classe Model che rappresenti le caratteristiche dei vari modelli
 *
 * @author Giacomo Seno
 * @version 1.0 29/01/20
 */

#ifndef INC_MODEL_H
#define INC_MODEL_H

#include <string>
#include <set>
#include "Component.h"
#include "Part.h"
#include "ComponentUsage.h"

/**
 * Gli invarianti della classe sono:
 * - price > 0
 * - max_delivery_months > 0
 */

class Model : public Part {
    double price;
    std::set<std::shared_ptr<const ComponentUsage>> components;
    unsigned int max_delivery_months;

public:

    /**
     * Costruttore di Model, inizializza un oggetto di tipo Model con un id, un nome e un prezzo
     * @param id        id del modello
     * @param name      nome del modello
     * @param price     prezzo del modello
     */
    Model(const int id, const std::string name, const double price);

    /**
     * Ritorna il prezzo del modello
     * @return price
     */
    double get_price() const {
        return price;
    }

    /**
     * Ritorna un set dei componenti necessari per quel determinato modello
     * @return components
     */
    const std::set<std::shared_ptr<const ComponentUsage>>& get_components() const {
        return components;
    }

    /**
     * Aggiunge un componente al set dei componenti necessari per costruire il modello
     * @param comp
     */
    void add_component(const std::shared_ptr<ComponentUsage> comp) {
        components.insert(comp);

        // Aggiorna, se necessario, il massimo numero di mesi
        if (comp->get_component()->get_months_to_delivery() > max_delivery_months)
            max_delivery_months = comp->get_component()->get_months_to_delivery();
    }

    /**
     * Ritorna il numero massimo di mesi dopo cui il modello sarà disponibile
     * @return max_delivery_months
     */
    unsigned int get_max_delivery_months() const {
        return max_delivery_months;
    }

    /**
     * Operatore assegnamento di spostamento
     */
    Model& operator=(Model&&) = default;
};

/**
 * Overload dell'operatore <<
 * Stampa su uno stream l'id, il nome, il prezzo e il numero dei componenti necessari per quel determinato modello
 * @param stream        stream su cui stampare
 * @param model         modello di cui stampare i dati
 * @return lo stream passato come parametro
 */
std::ostream& operator<<(std::ostream& stream, const Model& model);

#endif //INC_MODEL_H
