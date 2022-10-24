#include "corner_link.h"
#include <type_traits>

bool compare(Block& b1, Block& b2) {
    Point &loc_b1 = b1.loc;
    Point &loc_b2 = b2.loc;
    // return (loc_b1.x < loc_b2.x) ||
    //        ((loc_b1.x == loc_b2.x) && (loc_b1.y < loc_b2.y)) ||
    //        ((loc_b1.y == loc_b2.y) && (loc_b1.z < loc_b2.z));
    return loc_b1 < loc_b2;
}

bool CornerLink::same_coordi(std::pair<const std::string, Point>& v,
                             std::pair<const std::string, Point>& w) {
  // return ((v.second.x == w.second.x) &&
  //         (v.second.y == w.second.y) &&
  //         (v.second.z == w.second.z));

    return (v.second == w.second);
}

std::string CornerLink::coordi_info(std::pair<const std::string, Point>& v) {
    std::string res = "";
    res = v.first + ":(" + std::to_string(v.second.x) + ", " +
        std::to_string(v.second.y) + ", " + std::to_string(v.second.z) + ")";
    return res;
}

bool CornerLink::corner_pair_exist(corner_pair& cp1, corner_pair& cp2) {
    if (((cp1.first.first == cp2.first.first) && (cp1.first.second == cp2.first.second)) &&
        ((cp1.second.first == cp2.second.first) && (cp1.second.second == cp2.second.second))) {
        return true;
    }
    
    return false;
}

void CornerLink::get_corner_link(Data& data) {
    std::cout << "\n>> Corner Link...\n";
    // std::cout << "\n/===== Before sort =====/\n";
    // print_blocks(data, 0);

    // Sort the st of all blocks in the given 3D mosaic floorplan
    std::sort(data.blocks.begin(), data.blocks.end(), compare);
    // std::cout << "\n/===== After sort =====/\n";
    // print_blocks(data, 0);

    // Find neighboring corners for each block
    for (auto& b1: data.blocks) {

        // corner v in linking_corners
        for (auto& v: b1.corners.linking_corners) {

            // Find 1/8 neighboring corners of the hamming distance = 1
            for (auto& b2: data.blocks) {
                if (&b1 == &b2) continue;
                // std::cout << "b1: " << b1.name << " b2: " << b2.name << std::endl;
                
                // corner w in opposite_corners
                for (auto& w: b2.corners.opposite_corners) {
                    // std::cout << "v: " << coordi_info(v) << " w: " << coordi_info(w) << std::endl;
                    // std::cout << "ham_dis: " << get_ham_dist(v, w) << std::endl;
                    // std::cout << "same coordi: " << same_coordi(v, w) << std::endl;
                    if (same_coordi(v, w) && (get_ham_dist(v, w) == 1)) {
                        if (data.corner_links.find(v.second) == data.corner_links.end()) {
                            std::cout << "corner_link exist\n";
                            // data.corner_links.emplace(make_pair(v.second, make_pair(v.first, w.first)));
                        }
                        // else {
                        //     for (auto& cl: data.corner_links) {
                        //         // ! TODO: still has bug
                        //         if (corner_pair_exist(cl.second, make_pair(v.first, w.first)))
                        //         //     data.corner_links.emplace(make_pair(v.second, make_pair(v.first, w.first)));
                        //     }
                        // }
                    }
                }
                std::cout << std::endl;
            }

            // Find 1/8 neighboring corners of the hamming distance = 3
            for (auto& b2: data.blocks) {
                if (&b1 == &b2) continue;
                for (auto& w: b2.corners.opposite_corners) {
                    if (same_coordi(v, w) && (get_ham_dist(v, w) == 3)) {
                        // if (data.corner_links.find(v.second) == data.corner_links.end())
                        //     data.corner_links.emplace(make_pair(v.second, make_pair(v.first, w.first)));
                    }
                }
            }
        }
    }
    
}

int CornerLink::get_ham_dist(std::pair<const std::string, Point> &v,
                             std::pair<const std::string, Point> &w) {
    int ham_dist = 0;
    for (int i = 0; i < v.first.size(); ++i)
        if (v.first[i] != w.first[i]) ham_dist++;

    return ham_dist;
}

void CornerLink::print_blocks(Data& data, int mode) {
    for (const auto& b: data.blocks) {
        double x = b.loc.x;
        double y = b.loc.y;
        double z = b.loc.z;
        double len_x = b.len_x;
        double len_y = b.len_y;
        double len_z = b.len_z;
        // Corners corners = b.corners;
        std::cout << "\nBlock: " << b.name << std::endl;
        if (mode) {
            printf("---: (%f, %f, %f)\n", x, y, z);
            printf("+--: (%f, %f, %f)\n", x + len_x, y, z);
            printf("-+-: (%f, %f, %f)\n", x, y + len_y, z);
            printf("--+: (%f, %f, %f)\n", x, y, z + len_z);
            printf("++-: (%f, %f, %f)\n", x + len_x, y + len_y, z);
            printf("-++: (%f, %f, %f)\n", x, y + len_y, z + len_z);
            printf("+-+: (%f, %f, %f)\n", x + len_x, y, z + len_z);
            printf("+++: (%f, %f, %f)\n", x + len_x, y + len_y, z + len_z);
        }
        else {
            printf("Min X: %f, Max X: %f\n", x, x + len_x);
            printf("Min Y: %f, Max Y: %f\n", y, y + len_y);
            printf("Min Z: %f, Max Z: %f\n", z, z + len_z);
        }
    }
}