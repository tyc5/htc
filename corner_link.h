#ifndef _CORNER_LINK_H
#define _CORNER_LINK_H

#include <algorithm>

#include "parser.h"

class CornerLink {
public:
    void get_corner_link(Data& data);
    void print_blocks(Data& data, int mode);
};

#endif