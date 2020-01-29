//
// Created by mozzicator on 22/01/20.
//

#include <iomanip>
#include <chrono>
#include <iostream>
#include <algorithm>
#include "FileParser.h"
#include "OrderParser.h"
#include "../Order.h"

using namespace std;

namespace parsers {
    OrderParser::OrderParser(const string &fileName, double &cashAmount, list<shared_ptr<const Order>> &parsedOrders, const map<int, shared_ptr<const Model>> &modelMap)
            : FileParser{fileName}, cash_amount{cashAmount}, parsed_orders(parsedOrders), model_map{modelMap} { }

    void OrderParser::parse_row(const int line, const vector<string> &parsedFields) {
        if (line == 1 && parsedFields.size() != 1 || line > 1 && parsedFields.size() != 3)
            throw ParsingException(parsedFileName, line);

        if (line == 1) {
            try {
                cash_amount = stod(parsedFields[0]);
            } catch (exception e) {
                throw ParsingException(parsedFileName, line);
            }
        } else {
            try {
                int orderTime {stoi(parsedFields[0])};
                int modelId {stoi(parsedFields[1])};
                unsigned int quantity {static_cast<unsigned int>(stoi(parsedFields[2]))};
                parsed_orders.push_back(make_shared<Order>(orderTime, model_map.at(modelId), quantity));
            } catch (out_of_range e) {
                throw ParsingException("Error loading order at line " + to_string(line) + ": no model loaded with id: " + parsedFields[1]);
            } catch (exception e) {
                throw ParsingException(parsedFileName, line);
            }
        }
    }
}
