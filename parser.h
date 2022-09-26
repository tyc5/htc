#ifndef _PARSER_H
#define _PARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <map>

struct Point {
    double x;
    double y;
    double z;
    Point(): x(0), y(0), z(0) {}
    Point(double x_, double y_, double z_): x(x_), y(y_), z(z_) {}
};

struct Corners {
    // -: n, +: p
    // opposite corners: {− − −(nnn), − + +(npp), + − +(pnp), + + −(ppn)}
    Point nnn, npp, pnp, ppn;
    // linking corners:  {− − +(nnp), − + −(npn), + − −(pnn), + + +(ppp)}
    Point nnp, npn, pnn, ppp;
};

struct Block {
    std::string name;
    Point loc;
    double len_x;
    double len_y;
    double len_z;
    Corners corners;
};

// Place space
struct Space {
    std::string unit;
    Block space;
    Space(): unit(""), space() {}
    Space(std::string unit_, Block space_): unit(unit_), space(space_) {}
};

struct SolidBlock {
    Block solid;
    std::string material;
    double emissivity[6];
    SolidBlock(): solid(), material("") { for (int i = 0; i < 6; ++i) emissivity[i] = 0;}
};

class Data {
    public:
        Space place_space;
        std::vector<SolidBlock> solid_blocks;
        
};

class Parser {
    public:
        void parser(std::string filename, Data& data);
        void print_info(Data& data);
};

#endif