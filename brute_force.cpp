#include "brute_force.h"

void BruteForce::create_link(Data& data) {
    std::cout << "\n/========== Brute Force ==========/\n";

    std::cout << "/----- print blocks -----/\n";
    for (auto& block: data.blocks) {
        std::cout << block.name << ": " << block.loc << std::endl;
    }
    
}