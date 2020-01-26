//
// Created by mozzicator on 22/01/20.
//

#ifndef INC_PARSERS_MODELPARSER_H
#define INC_PARSERS_MODELPARSER_H

#include <map>
#include "FileParser.h"
#include "../Component.h"
#include "../Model.h"

namespace parsers {
    class ModelParser : public FileParser {
        Model *parsed_model;
        std::map<int, Model> &model_map;
        const std::map<int, Component> &component_map;

    protected:
        void parse_row(const int line, const std::vector<std::string> &parsedFields) override;

    public:
        ModelParser(std::string fileName, std::map<int, Model> &modelMap, const std::map<int, Component> &componentMap);

        ~ModelParser();

        void parse() override;
    };
}

#endif //INC_PARSERS_MODELPARSER_H
