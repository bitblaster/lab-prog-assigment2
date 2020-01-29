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
        std::map<int, std::shared_ptr<const Model>> &model_map;
        const std::map<int, std::shared_ptr<const Component>> &component_map;
    protected:
        void parse_row(int line, const std::vector<std::string> &parsedFields) override;

    public:
        ModelListParser(const std::string &fileName, std::map<int, std::shared_ptr<const Model>> &modelMap, const std::map<int, std::shared_ptr<const Component>> &componentMap);
    };
}

#endif //INC_PARSERS_MODELLISTPARSER_H
