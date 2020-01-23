//
// Created by mozzicator on 22/01/20.
//

#include "FileParser.h"
#include "ComponentParser.h"

using namespace std;

namespace parsers {
    void ComponentParser::parse_row(const int line, const std::vector<std::string> &parsedFields) {
        if (parsedFields.size() != 6)
            throw ParsingException(parsedFileName, line);

        int id = stoi(parsedFields[0]);
        Component parsed(
                id,
                parsedFields[1],        // name
                stoi(parsedFields[2]),  // months_to_delivery
                stod(parsedFields[3]),  // price_1
                stod(parsedFields[4]),  // price_2
                stod(parsedFields[5])   // price_3
        );

        parsedComponents[id] = parsed;
    }
}
