//
// Created by giacomo on 17/01/20.
//

#include <iomanip>
#include "Order.h"

using namespace std;

Order::Order(unsigned int timestamp, const shared_ptr<const Model> model, const unsigned int quantity)
    : timestamp{timestamp}, model{model}, quantity{quantity}, waiting_components{false} {}

ostream& operator <<(ostream& stream, const Order& order) {
    stream << "mese: " << order.get_timestamp() << ", modello: " << order.get_model()->get_id() << ", quantità:" << order.get_quantity();
    return stream;
}
