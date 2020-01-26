//
// Created by mozzicator on 22/01/20.
//

#ifndef INC_PARSERS_MODELLISTPARSER_H
#define INC_PARSERS_MODELLISTPARSER_H

#include <map>
#include "FileParser.h"
#include "../Model.h"

namespace parsers {
    class ModelListParser : public FileParser {
        std::map<int, Model> &model_map;
        const std::map<int, Component> &component_map;
    protected:
        void parse_row(const int line, const std::vector<std::string> &parsedFields) override;

    public:
        ModelListParser(const std::string &fileName, std::map<int, Model> &modelMap, const std::map<int, Component> &componentMap)
                : FileParser{fileName}, model_map{modelMap}, component_map{componentMap} {
            model_map.clear();
        }
    };
}

#endif //INC_PARSERS_MODELLISTPARSER_H
