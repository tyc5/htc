#include "corner_link.h"

bool compare(SolidBlock& b1, SolidBlock& b2) {
    Point &loc_b1 = b1.solid.loc;
    Point &loc_b2 = b2.solid.loc;
    return (loc_b1.x < loc_b2.x) ||
           ((loc_b1.x == loc_b2.x) && (loc_b1.y < loc_b2.y)) ||
           ((loc_b1.y == loc_b2.y) && (loc_b1.z < loc_b2.z));
}

bool CornerLink::same_coordi(auto& v, auto& w) {
    return ((v.second.x == w.second.x) &&
            (v.second.y == w.second.y) &&
            (v.second.z == w.second.z));
}

std::string CornerLink::coordi(auto& v) {
    std::string res = "";
    res = v.first + ":(" +
          std::to_string(v.second.x) + ", " +
          std::to_string(v.second.y) + ", " +
          std::to_string(v.second.z) + ")";
    return res;
}

void CornerLink::get_corner_link(Data& data) {
    std::cout << "\n>> Corner Link...\n";
    // std::cout << "\n/===== Before sort =====/\n";
    // print_blocks(data, 0);
    std::sort(data.solid_blocks.begin(), data.solid_blocks.end(), compare);
    // std::cout << "\n/===== After sort =====/\n";
    // print_blocks(data, 0);

    // Find neighboring corners for each block
    for (auto& b1: data.solid_blocks) {
        for (auto& v: b1.solid.corners.linking_corners) {
            for (auto& b2: data.solid_blocks) {
                if (&b1 == &b2) continue;
                std::cout << "b1: " << b1.solid.name << " b2: " << b2.solid.name << std::endl;
                for (auto& w: b2.solid.corners.opposite_corners) {
                    std::cout << "v: " << coordi(v) << " w: " << coordi(w) << std::endl;
                    std::cout << "ham_dis: " << get_ham_dist(v, w) << std::endl;
                    std::cout << "same coordi: " << same_coordi(v, w) << std::endl;
                }
                std::cout << std::endl;
            }
        }
    }
    
}

int CornerLink::get_ham_dist(auto& v, auto& w) {
    int ham_dist = 0;
    for (int i = 0; i < v.first.size(); ++i)
        if (v.first[i] != w.first[i]) ham_dist++;

    return ham_dist;
}

void CornerLink::print_blocks(Data& data, int mode) {
    for (const auto& b: data.solid_blocks) {
        double x = b.solid.loc.x;
        double y = b.solid.loc.y;
        double z = b.solid.loc.z;
        double len_x = b.solid.len_x;
        double len_y = b.solid.len_y;
        double len_z = b.solid.len_z;
        // Corners corners = b.solid.corners;
        std::cout << "\nBlock: " << b.solid.name << std::endl;
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