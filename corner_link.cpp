#include "corner_link.h"

bool compare_x(SolidBlock b1, SolidBlock b2) {
    return ((b1.solid.corners.nnn.x < b2.solid.corners.nnn.x));
}

void CornerLink::get_corner_link(Data& data) {
    std::cout << "\n>> Corner Link...\n";
    print_blocks(data, 0);
    std::sort(data.solid_blocks.begin(), data.solid_blocks.end(), compare_x);
    std::cout << "\n/===== After sort =====/\n";
    print_blocks(data, 0);
    
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