//
// Created by mozzicator on 22/01/20.
//

#include <assert.h>
#include "FileParser.h"
#include "ModelParser.h"
#include "../ComponentReference.h"

using namespace std;

namespace parsers {
    void ModelParser::parse_row(const int line, const std::vector<std::string> &parsedFields) {
        if (parsedFields.size() != 3)
            throw ParsingException(parsedFileName, line);

        if(line == 1) {
            parsedModel = new Model(
                    stoi(parsedFields[0]),  // id
                    parsedFields[1],            //name
                    stod(parsedFields[2])   // price
            );
        } else {
            assert(parsedModel != nullptr);

            ComponentReference comp(
                    stoi(parsedFields[0]),  // id
                    parsedFields[1],        // name
                    stoi(parsedFields[2])  // quantity
            );
            parsedModel->add_component(comp);
        }
    }
}
