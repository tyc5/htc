#include "brute_force.h"
#include "parser.h"
#include <cstddef>

void BFGraph::add_edge_list(Block& from, Block& to) {
    // std::cout << "type of from: "
    //           << abi::__cxa_demangle(typeid(from).name(), 0, 0, 0) << std::endl;
    // std::cout << "type of to: "
    //           << abi::__cxa_demangle(typeid(to).name(), 0, 0, 0) << std::endl;

    // std::cout << "type of adj_list[from]: "
    //           << abi::__cxa_demangle(typeid(adj_list[from.name]).name(), 0, 0, 0) << std::endl;

    // adjacency list
    adj_list[from.name].emplace_back(to);
}

void BFGraph::add_edge_list(Block& from, Block& to, double weight) {
    // adjacency matrix
    std::cout << ">>>> establish adjacency matrix" << std::endl;
    std::cout << "from:\t" << from.name << "\taddr = " << &from << std::endl;
    std::cout << "to  :\t" << to.name << "\t\taddr = " << &to << std::endl << std::endl;
    adj_matrix[&from][&to] = weight;
}

void BFGraph::show_adjacency_list() {
    std::cout << ">>>> show adjacency list: " << std::endl;
    std::cout << "adj_list size: " << adj_list.size() << std::endl;
    for (const auto& list: adj_list) {
        // std::cout << "Block " << list.first << " is connected with: \n\t";
        std::cout << list.first << ":\n    ";
        for (const auto& block: list.second) {
            std::cout << block.name << " ";
        }
        std::cout << std::endl;
    }
}

void BFGraph::show_adjacency_matrix() {
    std::cout << ">>>> show adjacency matrix: " << std::endl;
    std::cout << "size of adj_matrix: " << adj_matrix.size() << " x " << adj_matrix.begin()->second.size() << std::endl;
    for (const auto& adj: this->adj_matrix) {
        for (const auto& row: adj.second) {
            // std::cout << row.second << " ";
            std::cout << "\t" << row.first->name << " ";
        }
        std::cout << std::endl << adj.first->name;
        std::cout << std::endl;
    }
}

double BruteForce::compute_overlap_area(int dim, Block from, Block to) {
    double from_min_x = from.loc.x; double from_max_x = from.loc.x + from.len_x;
    double from_min_y = from.loc.y; double from_max_y = from.loc.y + from.len_y;
    double from_min_z = from.loc.z; double from_max_z = from.loc.z + from.len_z;
    double to_min_x = to.loc.x;     double to_max_x = to.loc.x + to.len_x;
    double to_min_y = to.loc.y;     double to_max_y = to.loc.y + to.len_y;
    double to_min_z = to.loc.z;     double to_max_z = to.loc.z + to.len_z;

    double overlap_x = std::min(from_max_x, to_max_x) - std::max(from_min_x, to_min_x);
    double overlap_y = std::min(from_max_y, to_max_y) - std::max(from_min_y, to_min_y);
    double overlap_z = std::min(from_max_z, to_max_z) - std::max(from_min_z, to_min_z);

    // ==============================
    // dim = 0: x-dim, area = y * z
    // dim = 1: y-dim, area = x * z
    // dim = 2: z-dim, area = x * y
    // ==============================
    double overlap_area = (dim == 0) ? std::max(overlap_y, 0.0) * std::max(overlap_z, 0.0)
                        : (dim == 1) ? std::max(overlap_x, 0.0) * std::max(overlap_z, 0.0)
                        : std::max(overlap_x, 0.0) * std::max(overlap_y, 0.0);
    
    return overlap_area;
}

double BruteForce::compute_resistance(int dim, Block from, Block to, double overlap_area) {
    double resistance = 0.0;
    double l_from = 0.0;
    double l_to = 0.0;
    double k_from = 0.0;
    double k_to = 0.0;
    double r_from = 0.0;
    double r_to = 0.0;
    
    if (dim == 0) {
        l_from = from.len_x / 2;
        l_to = to.len_x / 2;
    }
    
    return resistance;
}

void BruteForce::create_link(Data& data) {
    std::cout << "\n/========== Brute Force ==========/\n";

    std::vector<BFGraph> graph;
    graph.resize(3);
    std::cout << "vector_graph size: " << graph.size() << std::endl;
    // adjacency matrix init
    std::cout << "/=================================================================/\n";
    std::cout << "/====================        Init Graph       ====================/\n";
    std::cout << "/=================================================================/\n";
    for (auto& block1: data.blocks) {
        for (auto& block2: data.blocks) {
            graph[0].add_edge_list(block1, block2, 0.0);
            graph[1].add_edge_list(block1, block2, 0.0);
            graph[2].add_edge_list(block1, block2, 0.0);
        }
    }

    BFGraph x_graph(data.blocks.size());
    BFGraph y_graph(data.blocks.size());
    BFGraph z_graph(data.blocks.size());
    std::cout << "x_graph: " << &x_graph << "\ny_graph: " << &y_graph << "\nz_graph: " << &z_graph << std::endl;

    std::cout << "\n/----- print blocks -----/\n";
    for (auto& block_from: data.blocks) {
        std::cout << block_from.name << ": " << block_from.loc << std::endl;
        for (auto& block_to: data.blocks) {
            if (&block_from == &block_to) continue;

            double overlap_area = 0.0;
            // x-dim
            if ((block_from.loc.x == (block_to.loc.x + block_to.len_x)) || ((block_from.loc.x + block_from.len_x) == block_to.loc.x)) {
                overlap_area = compute_overlap_area(0, block_from, block_to);
                if (overlap_area == 0.0) continue;
                graph[0].add_edge_list(block_from, block_to, overlap_area);
                graph[0].add_edge_list(block_from, block_to);
            }
            // y-dim
            else if ((block_from.loc.y == (block_to.loc.y + block_to.len_y)) || ((block_from.loc.y + block_from.len_y) == block_to.loc.y)) {
                overlap_area = compute_overlap_area(1, block_from, block_to);
                if (overlap_area == 0.0) continue;
                graph[1].add_edge_list(block_from, block_to, overlap_area);
                graph[1].add_edge_list(block_from, block_to);
            }
            // z-dim
            else if ((block_from.loc.z == (block_to.loc.z + block_to.len_z)) || ((block_from.loc.z + block_from.len_z) == block_to.loc.z)) {
                overlap_area = compute_overlap_area(2, block_from, block_to);
                if (overlap_area == 0.0) continue;
                graph[2].add_edge_list(block_from, block_to, overlap_area);
                graph[2].add_edge_list(block_from, block_to);
            }
        }
    }

    // show adj_matrix
    // graph[0].show_adjacency_matrix();
    // show adj_list
    std::cout << "\n/***** x-dim ****/\n";
    graph[0].show_adjacency_list();
    std::cout << "\n/***** y-dim ****/\n";
    graph[1].show_adjacency_list();
    std::cout << "\n/***** z-dim ****/\n";
    graph[2].show_adjacency_list();
}