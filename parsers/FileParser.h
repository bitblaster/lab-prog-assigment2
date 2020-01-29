//
// Created by mozzicator on 22/01/20.
//

#ifndef INC_PARSERS_FILEPARSER_H
#define INC_PARSERS_FILEPARSER_H

#include <vector>
#include <string>

namespace parsers {
    class FileParser {
    protected:
        bool successfulParsing {false};
        const std::string parsedFileName;

        virtual void parse_row(const int line, const std::vector<std::string> &parsedFields) = 0;

    public:
        FileParser(const std::string &fileName) : parsedFileName{fileName} {}

        virtual void parse();

        bool get_successful_parsing() {
            return successfulParsing;
        }
    };


    class ParsingException : public std::exception {
        const std::string message;

    public:
        ParsingException(const std::string &msg) : message {msg} {}
        ParsingException(const std::string &fileName, const int line) :
                message {"Errore di parsing nel file '" + fileName + "', linea " + std::to_string(line)} {}

        const char * what () const throw () {
            return message.c_str();
        }

    };
}

#endif //INC_PARSERS_FILEPARSER_H
