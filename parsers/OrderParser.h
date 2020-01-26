//
// Created by mozzicator on 22/01/20.
//

#ifndef INC_PARSERS_ORDERPARSER_H
#define INC_PARSERS_ORDERPARSER_H

#include <vector>
#include "FileParser.h"
#include "../Component.h"
#include "../Order.h"

namespace parsers {
    class OrderParser : public FileParser {
        double &cash_amount;
        std::vector<Order> &parsed_orders;

    protected:
        void parse_row(const int line, const std::vector<std::string> &parsedFields) override;

    public:
        OrderParser(std::string fileName, double &cashAmount, std::vector<Order> &parsedOrders) : FileParser{fileName}, cash_amount{cashAmount}, parsed_orders(parsedOrders) {
            parsed_orders.clear();
        }

        void parse() override;
    };
}

#endif //INC_PARSERS_ORDERPARSER_H
