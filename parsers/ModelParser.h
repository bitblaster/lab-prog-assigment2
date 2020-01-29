/**
 * ModelParser.h
 * Scopo: Definire una sottoclasse di FileParser che effettui il parsing dei file dei singoli modelli
 *
 * @author Giacomo Seno
 * @version 1.0 29/01/20
 */

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
        /**
         * Override della funzione virtuale parse_row di FileParser
         * Effettua il parsing delle singole righe del file
         * @param line              numero della linea all'interno del file
         * @param parsedFields      sono i diversi campi che ogni riga all'interno del file ha
         * @throws ParsingException se ci sono errori nel parsing
         */
        void parse_row(int line, const std::vector<std::string> &parsedFields) override;

    public:
        /**
         * Costruttore di ModelParser
         * @param fileName          nome del file su cui deve essere fatto il parsing
         * @param modelMap          mappa contenente i modelli
         * @param componentMap      mappa contenente i componenti
         */
        ModelParser(std::string fileName, std::map<int, std::shared_ptr<const Model>> &modelMap, const std::map<int, std::shared_ptr<const Component>> &componentMap);

        /**
         * Override della funzione parse di FileParser
         * Effettua il parsing del file dividendolo in singole righe che verranno "analizzate" da parse_row
         * @throws ParsingException se ci sono errori nel parsing del file
         */
        void parse() override;
    };
}

#endif //INC_PARSERS_MODELPARSER_H
