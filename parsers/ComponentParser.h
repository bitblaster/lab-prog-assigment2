//
// Created by mozzicator on 22/01/20.
//

#ifndef INC_PARSERS_COMPONENTPARSER_H
#define INC_PARSERS_COMPONENTPARSER_H

#include <map>
#include <memory>
#include "FileParser.h"
#include "../Component.h"

namespace parsers {
    class ComponentParser : public FileParser {
        std::map<int, std::shared_ptr<const Component>> &component_map;

    protected:
        void parse_row(int line, const std::vector<std::string> &parsedFields) override;

    public:
        ComponentParser(const std::string &fileName, std::map<int, std::shared_ptr<const Component>> &componentMap);
    };
}

#endif //INC_PARSERS_COMPONENTPARSER_H
