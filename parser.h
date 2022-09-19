#ifndef _PARSER_H
#define _PARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

struct Point {
    double x;
    double y;
    double z;
};

struct Block {
    std::string name;
    Point loc;
    double len_x;
    double len_y;
    double len_z;
};

// Place space
struct Space {
    std::string unit;
    Block space;
};

struct SolidBlock {
    Block solid;
    std::string material;
    double emissivity[6];  
};

class Data {
    public:
        std::vector<SolidBlock> solid_blocks;
};

class Parser {
    public:
        void parser(std::string filename, Data& data);
};

#endif