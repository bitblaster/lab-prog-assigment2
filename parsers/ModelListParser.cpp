//
// Created by mozzicator on 22/01/20.
//

#include "FileParser.h"
#include "ModelListParser.h"
#include "ModelParser.h"

using namespace std;

namespace parsers {
    ModelListParser::ModelListParser(const string &fileName, map<int, shared_ptr<const Model>> &modelMap, const map<int, shared_ptr<const Component>> &componentMap)
            : FileParser{fileName}, model_map{modelMap}, component_map{componentMap} { }

    void ModelListParser::parse_row(const int line, const std::vector<std::string> &parsedFields) {
        if (parsedFields.size() != 1)
            throw ParsingException(parsedFileName, line);

        const string &fileName {parsedFields[0]};
        ModelParser p(fileName, model_map, component_map);
        p.parse();
    }
}
