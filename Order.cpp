//
// Created by giacomo on 17/01/20.
//

#include <iomanip>
#include "Order.h"

using namespace std;

bool Order::in_period(const BatchPeriod period) const {
    tm localTime = *localtime(&timestamp);
    //tm localTime = get_localtime();
    return localTime.tm_mon == period.get_month() && localTime.tm_year == period.get_year();
}

ostream& operator <<(ostream& stream, const Order& order) {
    time_t timestamp = order.get_timestamp();
    tm time {*localtime(&timestamp)};
    stream << put_time(&time, "%c") << "," << order.get_model_id() << ",quantity:" << order.get_quantity();
    return stream;
}
