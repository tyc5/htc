#ifndef _CORNER_LINK_H
#define _CORNER_LINK_H

#include <algorithm>
#include <utility>

#include "parser.h"

typedef std::pair<Block, std::string> corner;
typedef std::pair<corner, corner> corner_pair;

class CornerLink {
public:
    void get_corner_link(Data& data);
    void print_blocks(Data& data, int mode);
    bool same_coordi(std::pair<const std::string, Point>& v,
                     std::pair<const std::string, Point>& w);
    std::string coordi_info(std::pair<const std::string, Point>& v);
    int get_ham_dist(std::pair<const std::string, Point>& v,
                     std::pair<const std::string, Point>& w);
    bool corner_pair_exist(corner_pair& cp1, corner_pair& cp2);
};

#endif