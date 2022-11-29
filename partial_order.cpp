#include "partial_order.h"
#include <typeinfo>
#include <cxxabi.h>

void Graph::add_edge_list(Block& from, Block& to) {
    std::cout << "type of from: "
              << abi::__cxa_demangle(typeid(from).name(), 0, 0, 0) << std::endl;
    std::cout << "type of to: "
              << abi::__cxa_demangle(typeid(to).name(), 0, 0, 0) << std::endl;

    std::cout << "type of adj_list[from]: "
              << abi::__cxa_demangle(typeid(adj_list[from.name]).name(), 0, 0, 0) << std::endl;

    adj_list[from.name].emplace_back(to);
}

void PartialOrder::get_partial_order(Data& data) {
    std::cout << "type of data: "
              << abi::__cxa_demangle(typeid(data).name(), 0, 0, 0) << std::endl;
    // initialize stitching_planes
    data.stitching_planes.reserve(3);
    data.stitching_planes = {{}, {}, {}};
    std::cout << "sp size: " << data.stitching_planes.size() << std::endl;
    
    for (const auto& cl: data.corner_links) {
        if (!data.stitching_planes.at(0).count(cl.first.x))
            data.stitching_planes[0].emplace(cl.first.x);
        if (!data.stitching_planes.at(1).count(cl.first.y))
            data.stitching_planes[1].emplace(cl.first.y);
        if (!data.stitching_planes.at(2).count(cl.first.z))
            data.stitching_planes[2].emplace(cl.first.z);
    }

    Graph partial_order_x;
    partial_order_x.add_edge_list(data.blocks[0], data.blocks[1]);

    for (int i = 0; i < data.stitching_planes.size(); ++i) {
        std::string str = i ? (i == 1 ? "y: " : "z: ") : "x: ";
        std::cout << str << std::endl;
        for (const auto& p: data.stitching_planes[i]) {
            std::cout << p << std::endl;


        }
        std::cout << std::endl;
    }
}