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
        std::map<int, Component> parsedComponents;
    protected:
        void parse_row(const int line, const std::vector<std::string> &parsedFields) override;

    public:
        // Ereditiamo i costruttori
        using FileParser::FileParser;

        // TODO: verificare performance di copia e lifetime quando usato il vector fuori dello scope del parser
        const std::map<int, Component> get_parsed_components() const {
            return parsedComponents;
        }
    };
}

#endif //INC_PARSERS_COMPONENTPARSER_H
