/*
 * Component.h
 * Scopo: Definere la classe che gestisca le componenti dei vari modelli
 */

#ifndef INC_COMPONENT_H
#define INC_COMPONENT_H


#include "Part.h"
#include <string>

constexpr unsigned int kQuantityTolerance {3};
constexpr int kQuantityThresholdCount {2};

/** Soglie di quantità per i diversi prezzi da applicare */
constexpr int kQuantityThresholds[kQuantityThresholdCount] {11, 51};

/*
 * Classe, sottoclasse di "Part", che rappresenta una componente che andranno a costituire i vari modelli.
 * Eredita Id e Nome dalla superclasse Part. I mesi necessari alla spedizione della componente sono rappresentati da
 * valori int, mentre i 3 differenti prezzi per quantità<11, 10<quantità<50, quantità>50 sono rappresentati da valori
 * double.
 * i mesi necessari alla spedizione della componente e i prezzi sono fissati in fase di costruzione e non possono essere
 * modificati
 *
 * Gli invarianti di classe sono:
 *  - month_to_delivery deve essere sempre > 0
 *
 */
class Component : public Part {
    int months_to_delivery;

    /** Prezzi corrispondenti alle diverse soglie di quantità */
    double prices[kQuantityThresholdCount+1];
public:
    Component(int id, std::string name, int months_to_delivery, double price_1, double price_2 , double price_3);

    int get_months_to_delivery() const {
        return months_to_delivery;
    }

/*
 * Data la quantità di componenti da acquistare, passata come parametro int, ritorna il corrispondente prezzo/componente,
 * nel caso venga passata una quantità <=0 viete tornato il valore -1
 */
    double get_price(const unsigned int quantity) const;

    static unsigned int get_suggested_quantity(const unsigned int minimumQuantity);
};

std::ostream& operator <<(std::ostream& stream, const Component& component);

#endif //INC_COMPONENT_H
