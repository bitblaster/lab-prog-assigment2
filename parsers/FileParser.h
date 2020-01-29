/**
 * FileParser.h
 * Scopo: Definire un parser astratto che legga un file di testo riga per riga e chiami una funzione virtuale pura passando i token letti
 *
 * @author Roberto Mozzicato, 1236209
 * @version 1.0 29/01/20
 */


#ifndef INC_PARSERS_FILEPARSER_H
#define INC_PARSERS_FILEPARSER_H

#include <utility>
#include <vector>
#include <string>

namespace parsers {
    class FileParser {
    protected:
        const std::string parsedFileName;

        /**
         * Override della funzione virtuale parse_row di FileParser
         * Effettua il parsing delle singole righe del file.
         * Dev'essere implementato nelle classi derivate
         *
         * @param line              numero della linea all'interno del file
         * @param parsedFields      sono i diversi campi all'interno di ogni riga del file
         * @throws ParsingException se ci sono errori nel parsing
         */
        virtual void parse_row(int line, const std::vector<std::string> &parsedFields) = 0;

    public:
        /**
        * Costruttore di FileParser
        * @param fileName          nome del file su cui deve essere fatto il parsing
        * @param componentMap      mappa che andrà a contenente le componenti
        */
        FileParser(std::string fileName) : parsedFileName{ std::move(fileName) } {}

        virtual void parse();
    };


    class ParsingException : public std::exception {
        const std::string message;

    public:
        ParsingException(const std::string &msg) : message {msg} {}
        ParsingException(const std::string &fileName, const int line);

        const char* what() const throw() override {
            return message.c_str();
        }
    };
}

#endif //INC_PARSERS_FILEPARSER_H
