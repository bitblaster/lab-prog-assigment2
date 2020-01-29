/**
 * Order.h
 * Scopo: Definire una classe Order per la gestione degli ordini
 *
 * @author Roberto Mozzicato, 1236209
 * @version 1.0 29/01/20
 */

#ifndef INC_ORDER_H
#define INC_ORDER_H

/**
 * Classe che rappresenta un ordine. un ordine è caratterizzato da un timestamp, un id del modello ordinato e dalla
 * quantità di prodotti ordinati, e di conseguenza dalle componenti necessarie per realizzarlo.
 *
 * Gli invarianti di classe sono:
 *  -   quantity>0
 *  -   timestamp>0
 */
#include <functional>
#include <map>
#include "Model.h"
#include "Component.h"

class Order {
    unsigned int timestamp;
    const std::shared_ptr<const Model> model;
    unsigned int quantity;
    std::map<int, int> reserved_components;
    std::map<int, int> requested_components;

public:
    /**
     * Costruttore di Order, inizializza un oggetto di tipo order con un timestamp, il modello ordinato, la quantità
     * e creando due mappe vuote per le componenti necessarie alla produzione e le componenti già riservate
     * @param timestamp     timestamp
     * @param model         modello ordinato
     * @param quantity      quantità di modelli ordinati
     */
    Order(unsigned int timestamp, const std::shared_ptr<const Model> model, const unsigned int quantity);

    /**
     * Ritorna il timestamp dell'ordine
     * @return
     */
    unsigned int get_timestamp() const {
        return timestamp;
    }

    /**
     * Ritorna il modello ordinato
     * @return model
     */
    const std::shared_ptr<const Model> get_model() const{
        return model;
    }

    /**
     * Ritorna la quantità di modelli ordinati
     * @return quantity
     */
    unsigned int get_quantity() const{
        return quantity;
    }

    /**
     * metodo per verificare se le componenti di un tipo sono state riservate
     * @param comp  componente riservata
     * @return true se la quantità necessaria alla produzione è stata riservata
     */
    bool is_component_fullfilled(const std::shared_ptr<const ComponentUsage> comp) const;

    /**
     * Riserva il numero di un modello componenti da riservare nel magazzino indicate nei parametri
     * @param comp          componente
     * @param quantity      quantità da riservare
     */
    void add_reserved_quantity(const std::shared_ptr<const ComponentUsage> comp, unsigned int quantity);

    /**
     * Ritorna il numero di un determinato modello di componenti già riservate nel magazzino
     * @param comp      componente
     * @return
     */
    unsigned int get_reserved_quantity(const std::shared_ptr<const ComponentUsage> comp) const;

    /**
     * Aggiunge il numero di un modello di componenti totali richieste dall'ordine
     * @param comp          componente
     * @param quantity      quantità richiesta
     */
    void add_requested_quantity(const std::shared_ptr<const ComponentUsage> comp, unsigned int quantity);

    /**
     * Ritorna il numero di un modello di componenti totali richieste dall'ordine
     * @param comp      componente
     * @return
     */
    unsigned int get_requested_quantity(const std::shared_ptr<const ComponentUsage> comp) const;

    /**
     * Overload operatore <
     * @param rhs
     * @return
     */
    bool operator<(const Order &rhs) const {
        return timestamp < rhs.timestamp;
    }
};

/**
 * Overload dell'operatore <<
 * Stampa mese, modello, quantità e componenti necessarie di un ordine
 * @param stream    stream su cui stampare
 * @param order     ordine da stampare
 * @return lo stream passato come parametro
 */
std::ostream& operator << (std::ostream& stream, const Order& order);

#endif //INC_ORDER_H
