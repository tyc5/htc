#ifndef _PARSER_H
#define _PARSER_H

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

// struct Point {
//     double x;
//     double y;
//     double z;
//     Point() : x(0), y(0), z(0) {}
//     Point(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}
// };

class Point {
public:
    double x;
    double y;
    double z;
    Point() : x(0), y(0), z(0) {}
    Point(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}
    bool operator==(const Point& rhs) {
        return ((x == rhs.x) && (y == rhs.y) && (z == rhs.z));
    }
    bool operator<(const Point& rhs) {
        return (
            (x < rhs.x) ||
            ((x == rhs.x) && (y < rhs.y)) ||
            ((y == rhs.y) && (z < rhs.z))
        );
    }
};

struct Corners {
    // -: n, +: p
    
    // opposite corners:  {− − +(nnp), − + −(npn), + − −(pnn), + + +(ppp)}
    // Point nnp, npn, pnn, ppp;
    std::unordered_map<std::string, Point> opposite_corners;
    // linking corners: {− − −(nnn), − + +(npp), + − +(pnp), + + −(ppn)}
    // Point nnn, npp, pnp, ppn;
    std::unordered_map<std::string, Point> linking_corners;
};

// struct Block {
//     std::string name;
//     Point loc;
//     double len_x;
//     double len_y;
//     double len_z;
//     Corners corners;
//     std::string material;
//     double emissivity[6];
//     Block() : name(""), loc(), len_x(), len_y(), len_z(), corners(), material("") {
//         for (int i = 0; i < 6; ++i) emissivity[i] = 0;
//     }
// };

class Block {
public:
    std::string name;
    Point loc;
    double len_x;
    double len_y;
    double len_z;
    Corners corners;
    std::string material;
    double emissivity[6];

    Block() : name(""), loc(), len_x(), len_y(), len_z(), corners(), material("") {
        for (int i = 0; i < 6; ++i) emissivity[i] = 0;
    }
};

// Place space
// struct Space {
//     std::string unit;
//     // Block space;
//     std::string name;
//     Point loc;
//     double len_x;
//     double len_y;
//     double len_z;
//     Corners corners;
//     Space() : unit(""), loc(), len_x(), len_y(), len_z(), corners() {}
//     // Space(std::string unit_, std::string name_, Point loc_, double len_x_, double len_y_, double len_z_, Corners corners_)
//     //     : unit(unit_), name(name_), loc(loc_), len_x(len_x_), len_y(len_y_), len_z(len_z_), corners(corners_) {}
// };

class Space {
public:
    std::string unit;
    std::string name;
    Point loc;
    double len_x;
    double len_y;
    double len_z;
    Corners corners;
    Space() : unit(""), name(), loc(), len_x(), len_y(), len_z(), corners() {}
    Space(std::string unit_, std::string name_, Point loc_, double len_x_, double len_y_, double len_z_, Corners corners_)
        : unit(unit_), name(name_), loc(loc_), len_x(len_x_), len_y(len_y_), len_z(len_z_), corners(corners_) {}
};

// struct SolidBlock {
//     Block solid;
//     std::string material;
//     double emissivity[6];
//     SolidBlock() : solid(), material("") {
//         for (int i = 0; i < 6; ++i) emissivity[i] = 0;
//     }
// };

class Data {
public:
    Space place_space;
    // std::vector<SolidBlock> solid_blocks;
    std::vector<Block> blocks;
    std::multimap<Point, std::unordered_map<std::string, std::string>> corner_links;
};

class Parser {
public:
    void parser(std::string filename, Data& data);
    void print_info(Data& data);
};

#endif