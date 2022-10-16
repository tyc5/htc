#ifndef _CORNER_LINK_H
#define _CORNER_LINK_H

#include <algorithm>

#include "parser.h"

class CornerLink {
public:
    void get_corner_link(Data& data);
    void print_blocks(Data& data, int mode);
    bool same_coordi(auto& v, auto& w);
    std::string coordi_info(auto& v);
    int get_ham_dist(auto& v, auto& w);
    bool corner_pair_exist(auto& cp1, auto& cp2);
};

#endif