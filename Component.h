/**
 * Component.h
 * Scopo: Definere la classe che gestisca le componenti dei vari modelli
 *
 * @author Giacomo Vettoretti, 1187540
 * @version 1.0 29/01/20
 */

#ifndef INC_COMPONENT_H
#define INC_COMPONENT_H

/**
 * Classe, sottoclasse di "Part", che rappresenta una componente che andrà a costituire i vari modelli.
 * Eredita Id e Nome dalla superclasse Part. I mesi necessari alla spedizione della componente sono rappresentati da
 * valori int, mentre i 3 differenti prezzi per quantità<11, 10<quantità<50, quantità>50 sono rappresentati da valori
 * double.
 * i mesi necessari alla spedizione della componente e i prezzi sono fissati in fase di costruzione e non possono essere
 * modificati
 *
 * Gli invarianti di classe sono:
 *  - month_to_delivery deve essere sempre > 0
 *  -i price1/2/3 maggiori di 0
 */


#include "Part.h"
#include <string>

/**
 *
 */
constexpr unsigned int kQuantityTolerance {3};
constexpr int kQuantityThresholdCount {2};

/** Soglie di quantità per i diversi prezzi da applicare */
constexpr int kQuantityThresholds[kQuantityThresholdCount] {11, 51};

class Component : public Part {
    int months_to_delivery;

    /** Prezzi corrispondenti alle diverse soglie di quantità */
    double prices[kQuantityThresholdCount+1];
public:
    /**
     * Costruttore di model, inizializza un oggetto di tipo Component con id, nome, tempo di spedizione e i 3 diversi prezzi
     * @param id                    id della componente
     * @param name                  nome della componente
     * @param months_to_delivery    tempo di spedizione
     * @param price_1               prezzo con quantità <11
     * @param price_2               prezzo con quantità 10< quantità <51
     * @param price_3               prezzo con quantita > 50
     */
    Component(int id, std::string name, int months_to_delivery, double price_1, double price_2 , double price_3);

    /**
     * Ritorna il tempo di spedizione
     * @return month_to_delivery
     */
    int get_months_to_delivery() const {
        return months_to_delivery;
    }

    /**
     * Ritorna il prezzo per componente in base al numero di componenti da ordinare
     * @param quantity      quantità da ordinare
     * @return  prezzo per componente in base alla quantità inserita
     */
    double get_price(const unsigned int quantity) const;

    /**
     * Ritorna il numero ottimale di componenti da ordinare in base ad un numero minimo di componenti da comprare
     * @param minimumQuantity       quantità minima da acquistare
     * @return  la quantità di componenti da acquistare consigliata da acquistare
     */
    static unsigned int get_suggested_quantity(const unsigned int minimumQuantity);
};

/**
 * Overload dell'operatore <<
 * Stampa su uno stream id, nome della componente
 * @param stream        stream su cui stampare
 * @param component     componente da stampare
 * @return lo stream passato come parametro
 */
std::ostream& operator << (std::ostream& stream, const Component& component);

#endif //INC_COMPONENT_H
