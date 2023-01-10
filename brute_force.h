#ifndef _BRUTE_FORCE_H
#define _BRUTE_FORCE_H

#include "parser.h"

class BFGraph {
private:
    int num_vertex;
    std::unordered_map<std::string, std::vector<Block> > adj_list;
    std::unordered_map<Block*, std::unordered_map<Block*, double> > adj_matrix;

public:
    BFGraph(): num_vertex(0) {};
    BFGraph(int num): num_vertex(num) {};
    void add_edge_list(Block& from, Block& to);
    void add_edge_list(Block& from, Block& to, double weight);
    void show_adjacency_matrix();
    void show_adjacency_list();
};

class BruteForce {
public:
    void create_link(Data& data);
    double compute_overlap_area(int dim, Block from, Block to);
    double compute_resistance(int dim, Block from, Block to, double overlap_area);
};

#endif