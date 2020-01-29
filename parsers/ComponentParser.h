/**
 * ComponentParser.h
 * Scopo: Definire una sottoclasse di FileParser che effettui il parsing del file delle componenti
 *
 * @author Giacomo Vettoretti, 1187540
 * @version 1.0 29/01/20
 */

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
        /**
         * Override della funzione virtuale parse_row di FileParser
         * Effettua il parsing delle singole righe del file
         * @param line              numero della linea all'interno del file
         * @param parsedFields      sono i diversi campi all'interno di ogni riga del file
         * @throws ParsingException se ci sono errori nel parsing
         */
        void parse_row(int line, const std::vector<std::string> &parsedFields) override;

    public:
        /**
         * Costruttore di ModelParser
         * @param fileName          nome del file su cui deve essere fatto il parsing
         * @param componentMap      mappa che andrà a contenente le componenti
         */
        ComponentParser(const std::string &fileName, std::map<int, std::shared_ptr<const Component>> &componentMap);
    };
}

#endif //INC_PARSERS_COMPONENTPARSER_H
