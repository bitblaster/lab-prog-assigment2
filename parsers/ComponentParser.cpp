//
// Created by mozzicator on 22/01/20.
//

#include "FileParser.h"
#include "ComponentParser.h"

using namespace std;

namespace parsers {
    void ComponentParser::parse_row(const int line, const vector<string> &parsedFields) {
        if (parsedFields.size() != 6)
            throw ParsingException(parsedFileName, line);

        try {
            int id {stoi(parsedFields[0])};
            string name {parsedFields[1]};
            int months {stoi(parsedFields[2])};
            double price_1 {stod(parsedFields[3])};
            double price_2 {stod(parsedFields[4])};
            double price_3 {stod(parsedFields[5])};

            parsedComponents[id] = Component(id, name, months, price_1, price_2, price_3);
        } catch (exception e) {
            throw ParsingException(parsedFileName, line);
        }
    }
}
