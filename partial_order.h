#ifndef _PARTIAL_ORDER_H
#define _PARTIAL_ORDER_H

#include "parser.h"
#include "corner_link.h"

class Graph {
private:
    int num_vertex;
    std::unordered_map<std::string, std::vector<Block>> adj_list;
    std::unordered_map<Block*, std::unordered_map<Block*, double>> adj_matrix;

public:
    Graph(): num_vertex(0) {};
    Graph(int num): num_vertex(num) {};
    void add_edge_list(Block& from, Block& to, double weight);
};

class PartialOrder {
public:
    void get_partial_order(Data& data);
    double compute_overlap_area(int dim, Block from, Block to);
};

#endif