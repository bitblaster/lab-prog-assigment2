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
            tm orderTime = {};
            stringstream ss(parsedFields[0]);
            ss >> get_time(&orderTime, "%Y-%m-%d_%H:%M:%S");
            if (ss.fail())
                throw ParsingException(parsedFileName, line);

            try {
                int modelId{stoi(parsedFields[1])};
                int quantity = {stoi(parsedFields[2])};
                parsedOrders.push_back(Order(mktime(&orderTime), modelId, quantity));
            } catch (exception e) {
                throw ParsingException(parsedFileName, line);
            }
        }
    }

    void OrderParser::parse() {
        FileParser::parse();

        // Alla fine del parsing ordiniamo gli ordini per timestamp (v. operator < di Order)
        sort(parsedOrders.begin(), parsedOrders.end());
    }
}
