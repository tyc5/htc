#include "corner_link.h"

bool compare(SolidBlock b1, SolidBlock b2) {
    if (b1.solid.loc.x != b2.solid.loc.x)
        return ((b1.solid.loc.x < b2.solid.loc.x) && (b1.solid.loc.x + b1.solid.len_x < b2.solid.loc.x));
    if (b1.solid.loc.y != b2.solid.loc.y)
        return ((b1.solid.loc.y < b2.solid.loc.y) && (b1.solid.loc.y + b1.solid.len_y < b2.solid.loc.y));
    if (b1.solid.loc.z != b2.solid.loc.z)
        return ((b1.solid.loc.z < b2.solid.loc.z) && (b1.solid.loc.z + b1.solid.len_z < b2.solid.loc.z));
}

void CornerLink::get_corner_link(Data& data) {
    std::cout << "\n>> Corner Link...\n";
    print_blocks(data);
    // std::sort(data.solid_blocks.begin(), data.solid_blocks.end(), compare);
    // std::cout << "After sort\n";
    // print_blocks(data);
    
}

void CornerLink::print_blocks(Data& data) {
    for (const auto& b: data.solid_blocks) {
        double x = b.solid.loc.x;
        double y = b.solid.loc.y;
        double z = b.solid.loc.z;
        double len_x = b.solid.len_x;
        double len_y = b.solid.len_y;
        double len_z = b.solid.len_z;
        // Corners corners = b.solid.corners;
        std::cout << "\nBlock: " << b.solid.name << std::endl;
        printf("---: (%f, %f, %f)\n", x, y, z);
        printf("+--: (%f, %f, %f)\n", x + len_x, y, z);
        printf("-+-: (%f, %f, %f)\n", x, y + len_y, z);
        printf("--+: (%f, %f, %f)\n", x, y, z + len_z);
        printf("++-: (%f, %f, %f)\n", x + len_x, y + len_y, z);
        printf("-++: (%f, %f, %f)\n", x, y + len_y, z + len_z);
        printf("+-+: (%f, %f, %f)\n", x + len_x, y, z + len_z);
        printf("+++: (%f, %f, %f)\n", x + len_x, y + len_y, z + len_z);
    }
}