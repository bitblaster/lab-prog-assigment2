//
// Created by mozzicator on 22/01/20.
//

#ifndef INC_PARSERS_MODELPARSER_H
#define INC_PARSERS_MODELPARSER_H

#include <map>
#include <memory>
#include "FileParser.h"
#include "../Component.h"
#include "../Model.h"

namespace parsers {
    class ModelParser : public FileParser {
        std::shared_ptr<Model> parsed_model;
        std::map<int, std::shared_ptr<const Model>> &model_map;
        const std::map<int, std::shared_ptr<const Component>> &component_map;

    protected:
        void parse_row(int line, const std::vector<std::string> &parsedFields) override;

    public:
        ModelParser(std::string fileName, std::map<int, std::shared_ptr<const Model>> &modelMap, const std::map<int, std::shared_ptr<const Component>> &componentMap);

        void parse() override;
    };
}

#endif //INC_PARSERS_MODELPARSER_H
