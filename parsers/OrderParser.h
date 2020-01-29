//
// Created by mozzicator on 22/01/20.
//

#ifndef INC_PARSERS_ORDERPARSER_H
#define INC_PARSERS_ORDERPARSER_H

#include <list>
#include <map>
#include <memory>
#include "FileParser.h"
#include "../Component.h"
#include "../Order.h"

namespace parsers {
    class OrderParser : public FileParser {
        double &cash_amount;
        std::list<std::shared_ptr<const Order>> &parsed_orders;
        const std::map<int, std::shared_ptr<const Model>> &model_map;

    protected:
        void parse_row(int line, const std::vector<std::string> &parsedFields) override;

    public:
        OrderParser(const std::string &fileName, double &cashAmount, std::list<std::shared_ptr<const Order>> &parsedOrders, const std::map<int, std::shared_ptr<const Model>> &modelMap);
    };
}

#endif //INC_PARSERS_ORDERPARSER_H
