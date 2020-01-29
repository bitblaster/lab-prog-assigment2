//
// Created by giacomo on 17/01/20.
//

#include <iomanip>
#include "Order.h"

using namespace std;

ostream& operator <<(ostream& stream, const Order& order) {
    stream << "mese: " << order.get_timestamp() << ", modello: " << order.get_model()->get_id() << ", quantità:" << order.get_quantity();
    return stream;
}
