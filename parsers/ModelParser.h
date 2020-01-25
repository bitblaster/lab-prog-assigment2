//
// Created by mozzicator on 22/01/20.
//

#ifndef INC_PARSERS_MODELPARSER_H
#define INC_PARSERS_MODELPARSER_H

#include "FileParser.h"
#include "../Component.h"
#include "../Model.h"

namespace parsers {
    class ModelParser : public FileParser {
        Model *parsedModel;

    protected:
        void parse_row(const int line, const std::vector<std::string> &parsedFields) override;

    public:
        ModelParser(std::string fileName) : FileParser{fileName}, parsedModel{nullptr} {}

        ~ModelParser() {
            delete parsedModel;
            parsedModel = nullptr;
        }

        const Model& get_parsed_model() {
            return *parsedModel;
        }
    };
}

#endif //INC_PARSERS_MODELPARSER_H
