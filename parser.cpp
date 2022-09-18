#include "parser.h"

void Parser::parser(std::string filename, Data& data) {
    std::cout << ">> Parsing...\n";
    std::ifstream in_file;
    in_file.open(filename, std::ios::in);
    if (in_file.fail()) {
        std::cerr << "Failed to open file: " << filename << ".\n";
        return;
    }

    std::string str;
    // Place Space
    Space place_space;
    in_file >> str >> place_space.unit;
    std::cout << "place unit: " << place_space.unit << std::endl;
    in_file >> str >> place_space.space.name;
    std::cout << "place name: " << place_space.space.name << std::endl;
    in_file >> str
            >> place_space.space.loc.x
            >> place_space.space.loc.y
            >> place_space.space.loc.z;
    printf("place location: (%f, %f, %f)\n"
          , place_space.space.loc.x
          , place_space.space.loc.y
          , place_space.space.loc.z);
    in_file >> str
            >> place_space.space.length
            >> place_space.space.width
            >> place_space.space.height;
    printf("place geometry: (%f, %f, %f)\n"
          , place_space.space.length
          , place_space.space.width
          , place_space.space.height);
    std::cout << std::endl;
    // Solid Block
    SolidBlock solid_block;
    while (!in_file.eof()) {
        // name
        in_file >> str >> solid_block.solid.name;
        // location
        in_file >> str
                >> solid_block.solid.loc.x
                >> solid_block.solid.loc.y
                >> solid_block.solid.loc.z;
        // geometry
        in_file >> str
                >> solid_block.solid.length
                >> solid_block.solid.width
                >> solid_block.solid.height;
        // material
        in_file >> str >> solid_block.material;
        if (solid_block.material == "Power") break;
        // emissivity
        for (int i = 0; i <= 6; ++i) in_file >> str;
        // for (int i = 0; i < 6; ++i) {
        //     double e;
        //     in_file >> e;
        //     solid_block.emissivity[i] = e;
        // }
        in_file >> str;
        printf("Name: %s\nLocation: (%f, %f, %f)\nGeometry: (%f, %f, %f)\nMaterial: %s\n"
            , solid_block.solid.name.c_str()
            , solid_block.solid.loc.x
            , solid_block.solid.loc.y
            , solid_block.solid.loc.z
            , solid_block.solid.length
            , solid_block.solid.width
            , solid_block.solid.height
            , solid_block.material.c_str());
        // for (const auto& e: solid_block.emissivity)
        //     printf(" %f", e);
        std::cout << std::endl;        
        data.blocks.emplace_back(solid_block);
    }
    std::string line;
    std::stringstream ss;
    
    while (getline(in_file, line)) {
        Block block;
        //std::cout << line << std::endl;
        
    }
    in_file.close();
}