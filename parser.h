#ifndef _PARSER_H
#define _PARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

struct Block {
    std::string name;
    double ori;
    double length;
    double width;
    double height;
};

class Data {
    public:
        std::vector<Block> blocks;
};

class Parser {
    public:
        void parser(std::string filename);
};

#endif