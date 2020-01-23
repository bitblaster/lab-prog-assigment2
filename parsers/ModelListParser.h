//
// Created by mozzicator on 22/01/20.
//

#ifndef INC_PARSERS_MODELLISTPARSER_H
#define INC_PARSERS_MODELLISTPARSER_H

//#include <map>
#include "FileParser.h"
#include "../Model.h"

namespace parsers {
    class ModelListParser : public FileParser {
        std::vector<Model> parsedModels;
        //std::map<int, Component> componentMap;
    protected:
        void parse_row(const int line, const std::vector<std::string> &parsedFields) override;

    public:
        // Ereditiamo i costruttori
        ModelListParser(const std::string &fileName/*, const std::map<int, Component> &componentMap*/) : FileParser{fileName}/*, componentMap{move(componentMap)*/ {}

        // TODO: verificare performance di copia e lifetime quando usato il vector fuori dello scope del parser
        const std::vector<Model>& get_parsed_models() const {
            return parsedModels;
        }
    };
}

#endif //INC_PARSERS_MODELLISTPARSER_H
