//
// Created by giacomo on 17/01/20.
//

#include <iomanip>
#include "Order.h"

using namespace std;

bool Order::in_month(const int month, const int year) const {
    tm localTime = get_localtime();
    return localTime.tm_mon == month && localTime.tm_year == year;
}

ostream& operator <<(ostream& stream, const Order& order) {
    time_t timestamp = order.get_timestamp();
    tm time {*localtime(&timestamp)};
    stream << put_time(&time, "%c") << "," << order.get_model_id() << ",quantity:" << order.get_quantity();
    return stream;
}
