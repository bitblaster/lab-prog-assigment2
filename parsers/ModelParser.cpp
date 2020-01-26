//
// Created by mozzicator on 22/01/20.
//

#include <assert.h>
#include "FileParser.h"
#include "ModelParser.h"
#include "../ComponentUsage.h"

using namespace std;

namespace parsers {

    ModelParser::ModelParser(std::string fileName, std::map<int, Model> &modelMap, const std::map<int, Component> &componentMap)
            : FileParser{fileName}, parsed_model{nullptr}, model_map(modelMap), component_map{componentMap}  {

    }

    ModelParser::~ModelParser() {
        delete parsed_model;
        parsed_model = nullptr;
    }


    void ModelParser::parse_row(const int line, const std::vector<std::string> &parsedFields) {
        if (parsedFields.size() != 3)
            throw ParsingException(parsedFileName, line);

        try {
            if(line == 1) {
                // libera un'eventuale instanza di parsed_model, in caso questo parser venga riutilizzato
                delete parsed_model;

                parsed_model = new Model(
                        stoi(parsedFields[0]),  // id
                        parsedFields[1],            //name
                        stod(parsedFields[2])   // price
                );
            } else {
                assert(parsed_model);

                int componentId = stoi(parsedFields[0]);
                string componentNameInModel {parsedFields[1]};
                int componentQuantityInModel {stoi(parsedFields[2])};

                const Component &comp {component_map.at(componentId)};
                ComponentUsage compUsage(
                        comp,
                        componentNameInModel,
                        componentQuantityInModel
                );
                parsed_model->add_component(compUsage);
            }
        } catch (exception e) {
            throw ParsingException(parsedFileName, line);
        }
    }

    void ModelParser::parse() {
        FileParser::parse();

        if (parsed_model && parsed_model->get_id() > 0 && !parsed_model->get_components().empty()) {
//            parsed_model->get_components()
            model_map[parsed_model->get_id()] = move(*parsed_model);
        }
        else
            throw ParsingException("Il file " + parsedFileName + " non contiene una definizione valida di un modello");
    }
}
