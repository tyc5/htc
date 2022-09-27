#include "parser.h"

void Parser::parser(std::string filename, Data &data) {
    std::cout << ">> Parsing...\n";
    std::ifstream in_file;
    in_file.open(filename, std::ios::in);
    if (in_file.fail()) {
        std::cerr << "Failed to open file: " << filename << ".\n";
        return;
    }

    std::string str;
    // Place Space
    Space &place_space = data.place_space;
    in_file >> str >> place_space.unit;

    in_file >> str >> place_space.space.name;

    in_file >> str >> place_space.space.loc.x >> place_space.space.loc.y >> place_space.space.loc.z;

    in_file >> str >> place_space.space.len_x >> place_space.space.len_y >> place_space.space.len_z;

    Block &space = data.place_space.space;
    Point &space_loc = data.place_space.space.loc;
    Corners &space_corners = data.place_space.space.corners;
    // opposite corners
    // space.corners.nnp = Point(space_loc.x, space_loc.y, space_loc.z + space.len_z);
    // space.corners.npn = Point(space_loc.x, space_loc.y + space.len_y, space_loc.z);
    // space.corners.pnn = Point(space_loc.x + space.len_x, space_loc.y, space_loc.z);
    // space.corners.ppp = Point(space_loc.x + space.len_x, space_loc.y + space.len_y, space_loc.z + space.len_z);
    space.corners.opposite_corners.emplace("nnp", Point(space_loc.x, space_loc.y, space_loc.z + space.len_z));
    space.corners.opposite_corners.emplace("npn", Point(space_loc.x, space_loc.y + space.len_y, space_loc.z));
    space.corners.opposite_corners.emplace("pnn", Point(space_loc.x + space.len_x, space_loc.y, space_loc.z));
    space.corners.opposite_corners.emplace("ppp", Point(space_loc.x + space.len_x, space_loc.y + space.len_y, space_loc.z + space.len_z));
    // linking corners
    // space.corners.nnn = Point(space_loc.x, space_loc.y, space_loc.z);
    // space.corners.npp = Point(space_loc.x, space_loc.y + space.len_y, space_loc.z + space.len_z);
    // space.corners.pnp = Point(space_loc.x + space.len_x, space_loc.y, space_loc.z + space.len_z);
    // space.corners.ppn = Point(space_loc.x + space.len_x, space_loc.y + space.len_y, space_loc.z);
    space.corners.linking_corners.emplace("nnn", Point(space_loc.x, space_loc.y, space_loc.z));
    space.corners.linking_corners.emplace("npp", Point(space_loc.x, space_loc.y + space.len_y, space_loc.z + space.len_z));
    space.corners.linking_corners.emplace("pnp", Point(space_loc.x + space.len_x, space_loc.y, space_loc.z + space.len_z));
    space.corners.linking_corners.emplace("ppn", Point(space_loc.x + space.len_x, space_loc.y + space.len_y, space_loc.z));
    std::cout << std::endl;
    
    while (!in_file.eof()) {
        // Solid Block
        SolidBlock solid_block;
        // name
        in_file >> str >> solid_block.solid.name;
        // location
        in_file >> str >> solid_block.solid.loc.x >> solid_block.solid.loc.y >> solid_block.solid.loc.z;
        // geometry
        in_file >> str >> solid_block.solid.len_x >> solid_block.solid.len_y >> solid_block.solid.len_z;
        // material
        in_file >> str >> solid_block.material;
        if (solid_block.material == "Power") break;
        // emissivity
        in_file >> str;
        for (int i = 0; i < 6; ++i) {
            in_file >> solid_block.emissivity[i];
        }
        in_file >> str;

        // corners
        double &x = solid_block.solid.loc.x;
        double &y = solid_block.solid.loc.y;
        double &z = solid_block.solid.loc.z;
        double &len_x = solid_block.solid.len_x;
        double &len_y = solid_block.solid.len_y;
        double &len_z = solid_block.solid.len_z;
        Corners &corners = solid_block.solid.corners;
        // opposite corners
        // corners.nnp = Point(x, y, z + len_z);
        // corners.npn = Point(x, y + len_y, z);
        // corners.pnn = Point(x + len_x, y, z);
        // corners.ppp = Point(x + len_x, y + len_y, z + len_z);
        corners.opposite_corners.emplace("nnp", Point(x, y, z + len_z));
        corners.opposite_corners.emplace("npn", Point(x, y + len_y, z));
        corners.opposite_corners.emplace("pnn", Point(x + len_x, y, z));
        corners.opposite_corners.emplace("ppp", Point(x + len_x, y + len_y, z + len_z));
        
        // linking corners
        // corners.nnn = Point(x, y, z);
        // corners.npp = Point(x, y + len_y, z + len_z);
        // corners.pnp = Point(x + len_x, y, z + len_z);
        // corners.ppn = Point(x + len_x, y + len_y, z);
        corners.linking_corners.emplace("nnn", Point(x, y, z));
        corners.linking_corners.emplace("npp", Point(x, y + len_y, z + len_z));
        corners.linking_corners.emplace("pnp", Point(x + len_x, y, z + len_z));
        corners.linking_corners.emplace("ppn", Point(x + len_x, y + len_y, z));

        data.solid_blocks.emplace_back(solid_block);
    }
    /*
    for (const auto& b: data.solid_blocks) {
        printf("\nName: %s\nLocation: (%f, %f, %f)\nGeometry: (%f, %f, %f)\nMaterial: %s\nEmissivity:"
            , b.solid.name.c_str()
            , b.solid.loc.x
            , b.solid.loc.y
            , b.solid.loc.z
            , b.solid.len_x
            , b.solid.len_y
            , b.solid.len_z
            , b.material.c_str());
        for (int i = 0; i < 6; ++i) std::cout << " " << b.emissivity[i];
        std::cout << std::endl;
    }
    */
    // print_info(data);
    in_file.close();
}

void Parser::print_info(Data &data) {
    std::cout << "\n>>> Print Info...\n";
    std::cout << ">>>> Place Space Info: \n";
    Space &place_space = data.place_space;
    std::cout << "place unit: " << place_space.unit << std::endl;
    std::cout << "place name: " << place_space.space.name << std::endl;
    printf("place location: (%f, %f, %f)\n", place_space.space.loc.x, place_space.space.loc.y, place_space.space.loc.z);
    printf("place geometry: (%f, %f, %f)\n", place_space.space.len_x, place_space.space.len_y, place_space.space.len_z);

    std::cout << "\n>>>> Blocks Info: \n";
    for (const auto &b : data.solid_blocks) {
        double x = b.solid.loc.x;
        double y = b.solid.loc.y;
        double z = b.solid.loc.z;
        double len_x = b.solid.len_x;
        double len_y = b.solid.len_y;
        double len_z = b.solid.len_z;
        Corners corners = b.solid.corners;
        std::cout << "\nBlock: " << b.solid.name << std::endl;
        // printf("---: (%f, %f, %f)\n", x, y, z);
        // printf("+--: (%f, %f, %f)\n", x + len_x, y, z);
        // printf("-+-: (%f, %f, %f)\n", x, y + len_y, z);
        // printf("--+: (%f, %f, %f)\n", x, y, z + len_z);
        // printf("++-: (%f, %f, %f)\n", x + len_x, y + len_y, z);
        // printf("-++: (%f, %f, %f)\n", x, y + len_y, z + len_z);
        // printf("+-+: (%f, %f, %f)\n", x + len_x, y, z + len_z);
        // printf("+++: (%f, %f, %f)\n", x + len_x, y + len_y, z + len_z);

        // opposite corners
        // std::cout << "\nopposite corners: \n";
        // printf("nnp: (%f, %f, %f)\n", corners.nnp.x, corners.nnp.y, corners.nnp.z);
        // printf("npn: (%f, %f, %f)\n", corners.npn.x, corners.npn.y, corners.npn.z);
        // printf("pnn: (%f, %f, %f)\n", corners.pnn.x, corners.pnn.y, corners.pnn.z);
        // printf("ppp: (%f, %f, %f)\n", corners.ppp.x, corners.ppp.y, corners.ppp.z);

        // linking corners
        // std::cout << "\nlinking corners: \n";
        // printf("nnn: (%f, %f, %f)\n", corners.nnn.x, corners.nnn.y, corners.nnn.z);
        // printf("npp: (%f, %f, %f)\n", corners.npp.x, corners.npp.y, corners.npp.z);
        // printf("pnp: (%f, %f, %f)\n", corners.pnp.x, corners.pnp.y, corners.pnp.z);
        // printf("ppn: (%f, %f, %f)\n", corners.ppn.x, corners.ppn.y, corners.ppn.z);

        // use unordered_map
        // std::cout << "\nfrom unordered_map\n";
        // opposite corners
        std::cout << "\nopposite corners: \n";
        printf("nnp: (%f, %f, %f)\n", corners.opposite_corners["nnp"].x, corners.opposite_corners["nnp"].y, corners.opposite_corners["nnp"].z);
        printf("npn: (%f, %f, %f)\n", corners.opposite_corners["npn"].x, corners.opposite_corners["npn"].y, corners.opposite_corners["npn"].z);
        printf("pnn: (%f, %f, %f)\n", corners.opposite_corners["pnn"].x, corners.opposite_corners["pnn"].y, corners.opposite_corners["pnn"].z);
        printf("ppp: (%f, %f, %f)\n", corners.opposite_corners["ppp"].x, corners.opposite_corners["ppp"].y, corners.opposite_corners["ppp"].z);

        // linking corners
        std::cout << "\nlinking corners: \n";
        printf("nnn: (%f, %f, %f)\n", corners.linking_corners["nnn"].x, corners.linking_corners["nnn"].y, corners.linking_corners["nnn"].z);
        printf("npp: (%f, %f, %f)\n", corners.linking_corners["npp"].x, corners.linking_corners["npp"].y, corners.linking_corners["npp"].z);
        printf("pnp: (%f, %f, %f)\n", corners.linking_corners["pnp"].x, corners.linking_corners["pnp"].y, corners.linking_corners["pnp"].z);
        printf("ppn: (%f, %f, %f)\n", corners.linking_corners["ppn"].x, corners.linking_corners["ppn"].y, corners.linking_corners["ppn"].z);
    }
}