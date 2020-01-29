/*
 * Component.h
 * Scopo: Definere la classe che gestisca le componenti dei vari modelli
 */

#ifndef INC_COMPONENT_H
#define INC_COMPONENT_H


#include "Part.h"
#include <string>

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
    double price_1; // price per quantita<11
    double price_2; // price per quantita 10<quantità<50
    double price_3; // price per quantita 51+

public:
    Component() = default;
    Component(int id, std::string name, int months_to_delivery, double price_1, double price_2 , double price_3)
        : Part(id, name) , months_to_delivery {months_to_delivery} , price_1{price_1} , price_2{price_2} , price_3{price_3} {}
    //Component(const Component &) = default;
    //Component(Component &&) = default;

    int get_months_to_delivery() const {
        return months_to_delivery;
    }
/*
 * Data la quantità di componenti da acquistare, passata come parametro int, ritorna il corrispondente prezzo/componente,
 * nel caso venga passata una quantità <=0 viete tornato il valore -1
 */
    double get_price(const int quantity) const;

    //Component& operator=(const Component &) = default;
};

std::ostream& operator << (std::ostream& stream, const Component& component);

#endif //INC_COMPONENT_H
