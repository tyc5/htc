#ifndef _PARTIAL_ORDER_H
#define _PARTIAL_ORDER_H

#include "parser.h"
#include "corner_link.h"

class Graph {
private:
    std::unordered_map<std::string, std::vector<Block>> adj_list;

public:
    void add_edge_list(Block& from, Block& to);
};

class PartialOrder {
public:
    void get_partial_order(Data& data);
};

#endif