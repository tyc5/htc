#include "parser.h"

void Parser::parser(std::string filename) {
    std::cout << ">> Parsing...\n";
    std::ifstream in_file;
    in_file.open(filename, std::ios::in);
    if (!in_file) {
        std::cerr << "Failed to open file: " << filename << ".\n";
        return;
    }

    std::string line, str;
    
    in_file.close();
}