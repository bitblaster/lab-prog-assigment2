//
// Created by mozzicator on 22/01/20.
//

#include <iomanip>
#include <chrono>
#include <iostream>
#include "FileParser.h"
#include "OrderParser.h"
#include "../Order.h"

using namespace std;

namespace parsers {
    void OrderParser::parse_row(const int line, const vector<string> &parsedFields) {
        if (parsedFields.size() != 3)
            throw ParsingException(parsedFileName, line);

        tm orderTime = {};
        stringstream ss(parsedFields[0]);
        ss >> get_time(&orderTime, "%Y-%m-%d_%H:%M:%S");
        if (ss.fail())
            throw ParsingException(parsedFileName, line);

        try {
            int modelId {stoi(parsedFields[1])};
            int quantity = {stoi(parsedFields[2])};
            parsedOrders.push_back(Order(orderTime, modelId, quantity));
        } catch (exception e) {
            throw ParsingException(parsedFileName, line);
        }
    }
}
