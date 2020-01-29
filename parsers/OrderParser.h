/**
 * OrderParser.h
 * Scopo: Definire una sottoclasse di FileParser che effettui il parsing del file degli ordini
 *
 * @author Roberto Mozzicato, 1236209
 * @version 1.0 29/01/20
 */

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
        std::list<std::shared_ptr<Order>> &parsed_orders;
        const std::map<int, std::shared_ptr<const Model>> &model_map;

    protected:
        /**
         * Override della funzione virtuale parse_row di  File Parser
         * @param line              numero della linea all'interno del file
         * @param parsedFields      sono i diversi campi all'interno di ogni riga del file
         * @throw ParsingException  se ci sono errori durante il parsing
         */
        void parse_row(int line, const std::vector<std::string> &parsedFields) override;

    public:
        OrderParser(const std::string &fileName, double &cashAmount, std::list<std::shared_ptr<Order>> &parsedOrders, const std::map<int, std::shared_ptr<const Model>> &modelMap);
    };
}

#endif //INC_PARSERS_ORDERPARSER_H
