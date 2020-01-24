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
        std::vector<Order> parsedOrders;
    protected:
        void parse_row(const int line, const std::vector<std::string> &parsedFields) override;

    public:
        // Ereditiamo i costruttori
        using FileParser::FileParser;

        // TODO: verificare performance di copia e lifetime quando usato il vector fuori dello scope del parser
        const std::vector<Order> get_parsed_orders() const {
            return parsedOrders;
        }
    };
}

#endif //INC_PARSERS_ORDERPARSER_H
