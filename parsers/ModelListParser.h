/**
 * ModelListParser.h
 * Scopo: definire una sottoclasse di FileParser che effettui il parsing del file models.dat
 *
 * @author Giacomo Seno
 * @version 1.0 29/01/20
 */

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

        /**
         * Override della funzione virtuale parse_row di FileParser
         * Fa il parsing di ogni riga del file models.dat e comunica a ModelParser su quale file deve effettuare il parsing
         * @param line              numero della linea all'interno del file
         * @param parsedFields      sono i diversi campi che sono presenti nel file models.dat
         * @throws ParsingException se ci sono problemi nel parsing
         */
        void parse_row(int line, const std::vector<std::string> &parsedFields) override;

    public:
        /**
         * Costruttore di ModelListParser
         * @param fileName      nome del file che deve essere aperto e parsato
         * @param modelMap      mappa contenente i modelli
         * @param componentMap  mappa contente i componenti
         */
        ModelListParser(const std::string &fileName, std::map<int, std::shared_ptr<const Model>> &modelMap, const std::map<int, std::shared_ptr<const Component>> &componentMap);
    };
}

#endif //INC_PARSERS_MODELLISTPARSER_H
