//
// Created by mozzicator on 22/01/20.
//

#include "FileParser.h"
#include "ModelListParser.h"
#include "ModelParser.h"

using namespace std;

namespace parsers {
    void ModelListParser::parse_row(const int line, const std::vector<std::string> &parsedFields) {
        if (parsedFields.size() != 1)
            throw ParsingException(parsedFileName, line);

        const string &fileName {parsedFields[0]};
        ModelParser p(fileName);
        p.parse();
        parsedModels.push_back(p.get_parsed_model());
    }
}
