#include "parser.h"
#include "corner_link.h"
#include <ctime>

time_t start;

int main(int argc, char* argv[]) {
    start = clock();

    Parser parser;
    Data data;
    CornerLink corner_link;

    if (argc != 3) {
        std::cerr << "Usage: ./HTC [input] [output]" << std::endl;
        exit(1);
    }
    std::cout << "\n/----- Case: " << argv[1] << " -----/\n";

    parser.parser(argv[1], data);
    // parser.check(data);
    corner_link.init(data);

    time_t end = clock();
    float t_used = (float)(end - start) / CLOCKS_PER_SEC;
    std::cout << "\n>> Running Time: " << t_used << " seconds.\n";

    return 0;
}