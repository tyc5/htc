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
    double length;
    double width;
    double height;
};

// Place space
struct Space {
    std::string unit;
    Block space;
};

struct SolidBlock {
    Block solid;
    std::string material;
    // double emissivity[8];
};

class Data {
    public:
        std::vector<SolidBlock> blocks;
};

class Parser {
    public:
        void parser(std::string filename, Data& data);
};

#endif