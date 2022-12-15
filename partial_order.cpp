#include "partial_order.h"
#include <typeinfo>
#include <cxxabi.h>

void Graph::add_edge_list(Block& from, Block& to) {
    // std::cout << "type of from: "
    //           << abi::__cxa_demangle(typeid(from).name(), 0, 0, 0) << std::endl;
    // std::cout << "type of to: "
    //           << abi::__cxa_demangle(typeid(to).name(), 0, 0, 0) << std::endl;

    // std::cout << "type of adj_list[from]: "
    //           << abi::__cxa_demangle(typeid(adj_list[from.name]).name(), 0, 0, 0) << std::endl;

    // adjacency list
    adj_list[from.name].emplace_back(to);
}

void Graph::add_edge_list(Block& from, Block& to, double weight) {
    // adjacency matrix
    std::cout << ">>>> establish adjacency matrix" << std::endl;
    std::cout << "from:\t" << from.name << "\taddr = "<< &from << std::endl;
    std::cout << "to:\t\t" << to.name << "\taddr = " << &to << std::endl << std::endl;
    adj_matrix[&from][&to] = weight;
}

double PartialOrder::compute_overlap_area(int dim, Block from, Block to) {
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

void Graph::show_adjacency_matrix() {
    std::cout << ">>>> show adjacency matrix: " << std::endl;
    std::cout << "size of adj_matrix: " << adj_matrix.size() << " x " << adj_matrix.begin()->second.size() << std::endl;
    for (const auto& adj: this->adj_matrix) {
        for (const auto& row: adj.second) {
            // std::cout << row.second << " ";
            std::cout << "\t\t" << row.first->name << "\t";
        }
        std::cout << std::endl << adj.first->name;
        std::cout << std::endl;
    }
}

void Graph::show_adjacency_list() {
    std::cout << ">>>> show adjacency list: " << std::endl;
    for (const auto& list: adj_list) {
        std::cout << "Block " << list.first << " is connected with: \n\t";
        for (const auto& block: list.second) {
            std::cout << block.name << " ";
        }
        std::cout << std::endl;
    }
}

void PartialOrder::get_partial_order(Data& data) {
    std::cout << "type of data: "
              << abi::__cxa_demangle(typeid(data).name(), 0, 0, 0) << std::endl;

    // print block list
    std::cout << "Block Lists:\n";
    for (const auto& block : data.blocks) std::cout << block.name << std::endl;

    // initialize stitching_planes
    data.stitching_planes.reserve(3);
    data.stitching_planes = {{}, {}, {}};
    std::cout << "sp size: " << data.stitching_planes.size() << std::endl;
    
    // establish stitching_planes
    for (const auto& cl: data.corner_links) {
        if (!data.stitching_planes.at(0).count(cl.first.x))
            data.stitching_planes[0].emplace(cl.first.x);
        if (!data.stitching_planes.at(1).count(cl.first.y))
            data.stitching_planes[1].emplace(cl.first.y);
        if (!data.stitching_planes.at(2).count(cl.first.z))
            data.stitching_planes[2].emplace(cl.first.z);
    }
    std::cout << std::endl;

    // partial order
    Graph partial_order_x, partial_order_y, partial_order_z;

    // adjacency matrix init
    for (auto& block1: data.blocks) {
        for (auto& block2: data.blocks) {
            partial_order_x.add_edge_list(block1, block2, 0.0);
            partial_order_y.add_edge_list(block1, block2, 0.0);
            partial_order_z.add_edge_list(block1, block2, 0.0);
        }
    }
    // show init adj_matrix
    // std::cout << "show x-dim init adj_matrix:\n";
    // partial_order_x.show_adjacency_matrix();
    // std::cout << "show y-dim init adj_matrix:\n";
    // partial_order_x.show_adjacency_matrix();
    // std::cout << "show z-dim init adj_matrix:\n";
    // partial_order_x.show_adjacency_matrix();
    // return ;

    // x, y, z dimension partial_order
    std::cout << "/==================== Establish partial_order ====================/\n";

    for (int i = 0; i < data.stitching_planes.size(); ++i) {
        std::string str = "";

        // x-dim
        if (i == 0) {
            str = "x";
            std::cout << str << "-dim" << std::endl;
            for (const auto& x: data.stitching_planes[i]) {
                std::cout << x << std::endl;

                for (auto& cl: data.corner_links) {
                    if (cl.first.x > x) break;
                    if (cl.first.x == x) {
                        double overlap_area = compute_overlap_area(i, cl.second.first.first, cl.second.second.first);
                        std::cout << "Block 1: " << cl.second.first.first.name << std::endl;
                        std::cout << "Block 2: " << cl.second.second.first.name << std::endl;
                        std::cout << "overlap area: " << overlap_area << std::endl;

                        if (overlap_area != 0.0)
                            partial_order_x.add_edge_list(cl.second.first.first, cl.second.second.first);

                        partial_order_x.add_edge_list(cl.second.first.first, cl.second.second.first, overlap_area);
                    }
                }
            }
        }

        // y-dim
        else if (i == 1) {
            str = "y";
            std::cout << str << "-dim" << std::endl;
            for (const auto& y: data.stitching_planes[i]) {
                std::cout << y << std::endl;

                for (auto& cl: data.corner_links) {
                    if (cl.first.y > y) break;
                    if (cl.first.y == y) {
                        double overlap_area = compute_overlap_area(i, cl.second.first.first, cl.second.second.first);
                        std::cout << std::endl;
                        std::cout << "Block 1: " << cl.second.first.first.name << std::endl;
                        std::cout << "Block 2: " << cl.second.second.first.name << std::endl;
                        std::cout << "overlap area: " << overlap_area << std::endl;

                        if (overlap_area != 0.0)
                            partial_order_y.add_edge_list(cl.second.first.first, cl.second.second.first);

                        partial_order_y.add_edge_list(cl.second.first.first, cl.second.second.first, overlap_area);
                    }
                }
            }
        }

        // z-dim
        else if (i == 2) {
            str = "z";
            std::cout << str << "-dim" << std::endl;
            for (const auto& z: data.stitching_planes[i]) {
                std::cout << z << std::endl;

                for (auto& cl: data.corner_links) {
                    if (cl.first.z > z) break;
                    if (cl.first.z == z) {
                        double overlap_area = compute_overlap_area(i, cl.second.first.first, cl.second.second.first);
                        std::cout << std::endl;
                        std::cout << "Block 1: " << cl.second.first.first.name << std::endl;
                        std::cout << "Block 2: " << cl.second.second.first.name << std::endl;
                        std::cout << "overlap area: " << overlap_area << std::endl;

                        if (overlap_area != 0.0)
                            partial_order_z.add_edge_list(cl.second.first.first, cl.second.second.first);

                        partial_order_z.add_edge_list(cl.second.first.first, cl.second.second.first, overlap_area);
                    }
                }
            }
        }
        std::cout << std::endl;
    }

    // show adj_matrx
    // std::cout << "\nshow adj_matrix of x-dim: " << std::endl;
    // partial_order_x.show_adjacency_matrix();
    // std::cout << "\nshow adj_matrix of y-dim: " << std::endl;
    // partial_order_y.show_adjacency_matrix();
    // std::cout << "\nshow adj_matrix of z-dim: " << std::endl;
    // partial_order_z.show_adjacency_matrix();

    // show adj_list
    std::cout << "\n>>> show adj_list of x-dim: " << std::endl;
    partial_order_x.show_adjacency_list();
    std::cout << "\n>>> show adj_list of y-dim: " << std::endl;
    partial_order_y.show_adjacency_list();
    std::cout << "\n>>> show adj_list of z-dim: " << std::endl;
    partial_order_z.show_adjacency_list();
}