#include "corner_link.h"

void CornerLink::init(Data& data) {
    std::cout << "\n>> Corner Link Init...\n";

    for (const auto& b: data.solid_blocks) {
        double x = b.solid.loc.x;
        double y = b.solid.loc.y;
        double z = b.solid.loc.z;
        double len_x = b.solid.len_x;
        double len_y = b.solid.len_y;
        double len_z = b.solid.len_z;
        printf("---: (%f, %f, %f)\n", x, y, z);
        printf("+--: (%f, %f, %f)\n", x + len_x, y, z);
    }
}