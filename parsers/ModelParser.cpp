//
// Created by mozzicator on 22/01/20.
//

#include <assert.h>
#include "FileParser.h"
#include "ModelParser.h"
#include "../ComponentUsage.h"

using namespace std;

namespace parsers {

    ModelParser::ModelParser(string fileName, map<int, shared_ptr<const Model>> &modelMap, const map<int, shared_ptr<const Component>> &componentMap)
            : FileParser{fileName}, parsed_model{nullptr}, model_map(modelMap), component_map{componentMap}  { }

    void ModelParser::parse_row(const int line, const std::vector<std::string> &parsedFields) {
        if (parsedFields.size() != 3)
            throw ParsingException(parsedFileName, line);

        try {
            if(line == 1) {
                // libera un'eventuale instanza di parsed_model, in caso questo parser venga riutilizzato
                //delete parsed_model;
                int modelId {stoi(parsedFields[0])};
                string name {parsedFields[1]};
                double price {stod(parsedFields[2])};

                parsed_model = make_shared<Model>(modelId, name, price);
            } else {
                // In questo punto il model dev'essere già statao letto dal file
                if(parsed_model.get() == nullptr)
                    throw ParsingException("Errore di parsing nel file " + parsedFileName + ": rilevato componente prima del modello a linea " + to_string(line));

                int componentId = stoi(parsedFields[0]);
                string componentNameInModel {parsedFields[1]};
                int componentQuantityInModel {stoi(parsedFields[2])};

                const shared_ptr<const Component> comp {component_map.at(componentId)};
                parsed_model->add_component(make_unique<ComponentUsage>(comp, componentNameInModel, componentQuantityInModel));
            }
        } catch (exception e) {
            throw ParsingException(parsedFileName, line);
        }
    }

    void ModelParser::parse() {
        FileParser::parse();

        if (parsed_model && parsed_model->get_id() > 0 && !parsed_model->get_components().empty()) {
            model_map[parsed_model->get_id()] = parsed_model;
        }
        else
            throw ParsingException("Il file " + parsedFileName + " non contiene una definizione valida di un modello");
    }
}
