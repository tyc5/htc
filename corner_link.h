#ifndef _CORNER_LINK_H
#define _CORNER_LINK_H

#include <algorithm>
#include <utility>

#include "parser.h"

// typedef std::pair<typename T1, typename T2>

class CornerLink {
public:
    void get_corner_link(Data& data);
    void print_blocks(Data& data, int mode);
    bool same_coordi(std::pair<const std::string, Point>& v,
                     std::pair<const std::string, Point>& w);
    std::string coordi_info(std::pair<const std::string, Point>& v);
    int get_ham_dist(std::pair<const std::string, Point>& v,
                     std::pair<const std::string, Point>& w);
    bool corner_pair_exist(auto& cp1, auto& cp2);
};

#endif