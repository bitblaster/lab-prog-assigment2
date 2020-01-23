//
// Created by mozzicator on 22/01/20.
//

#include "FileParser.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

namespace parsers {
    void FileParser::parse() {
        // Apertura file in lettura
        ifstream in{parsedFileName};
        if (in.fail())
            throw ParsingException("Unable to open file '" + parsedFileName + "'");

        string line;
        for (int lineNum = 1; !in.eof(); ++lineNum) {
            // Lettura prossima riga
            getline(in, line);
            if (in.bad() || in.fail()) {
                break;
            }

            // Lettura singoli token dalla riga, separati da spazi
            std::vector<std::string> tokens;
            std::istringstream iss(line);
            for (std::string token; iss >> token;)
                tokens.push_back(token);

            // Parsing effettuato con la virtual function parse_row
            // specificatamente per ogni tipo di file
            parse_row(lineNum, tokens);
        }
    }
}