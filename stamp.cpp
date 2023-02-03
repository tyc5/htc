#include "stamp.h"
#include "brute_force.h"

void Stamp::stamp(Data& data, BruteForce& brute_force) {
    std::cout << "\n/========== Stamp ==========/\n";

    for (int i = 0; i < 3; ++i) {
        if (i == 0) {
            brute_force.graph[0].show_adjacency_list();
        }
    }
}