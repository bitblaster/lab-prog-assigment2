//
// Created by mozzicator on 22/01/20.
//

#ifndef INC_PARSERS_COMPONENTPARSER_H
#define INC_PARSERS_COMPONENTPARSER_H

#include <map>
#include "FileParser.h"
#include "../Component.h"

namespace parsers {
    class ComponentParser : public FileParser {
        std::map<int, Component> &component_map;

    protected:
        void parse_row(const int line, const std::vector<std::string> &parsedFields) override;

    public:
        ComponentParser(const std::string &fileName, std::map<int, Component> &componentMap) : FileParser{fileName}, component_map{componentMap} {
            component_map.clear();
        }
    };
}

#endif //INC_PARSERS_COMPONENTPARSER_H
