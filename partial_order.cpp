#include "partial_order.h"

void PartialOrder::get_partial_order(Data& data) {
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

    for (int i = 0; i < data.stitching_planes.size(); ++i) {
        std::string str = i ? (i == 1 ? "y: " : "z: ") : "x: ";
        std::cout << str << std::endl;
        for (const auto& p: data.stitching_planes[i])
            std::cout << p << std::endl;
        std::cout << std::endl;
    }
}