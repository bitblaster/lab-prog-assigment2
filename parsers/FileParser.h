//
// Created by mozzicator on 22/01/20.
//

#ifndef INC_PARSERS_FILEPARSER_H
#define INC_PARSERS_FILEPARSER_H

#include <utility>
#include <vector>
#include <string>

namespace parsers {
    class FileParser {
    protected:
        const std::string parsedFileName;

        virtual void parse_row(int line, const std::vector<std::string> &parsedFields) = 0;

    public:
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
