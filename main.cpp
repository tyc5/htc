#include <ctime>

#include "brute_force.h"
#include "corner_link.h"
#include "parser.h"
#include "partial_order.h"
#include "stamp.h"

time_t start;

int main(int argc, char* argv[]) {
    start = clock();

    Parser parser;
    Data data;
    CornerLink corner_link;
    PartialOrder partial_order;
    BruteForce brute_force;
    Stamp stamp;

    if (argc != 3) {
        std::cerr << "Usage: ./HTC [input] [output]" << std::endl;
        exit(1);
    }
    std::cout << "\n/----- Case: " << argv[1] << " -----/\n";

    parser.parser(argv[1], data);
    parser.print_info(data);
    // corner_link.get_corner_link(data);
    // partial_order.get_partial_order(data);
    brute_force.create_link(data);
    stamp.stamp(data, brute_force);

    time_t end = clock();
    float t_used = (float)(end - start) / CLOCKS_PER_SEC;
    std::cout << "\n>> Running Time: " << t_used << " seconds.\n";

    return 0;
}