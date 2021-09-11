
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "Analyzer.h"
#include "Classifier.h"
using namespace std;

void run_tests();

int main(int argc, char* argv[]) {

    if (argc == 1) {
        run_tests();
    }
    else {
        Analyzer a;
        a.readIn(argv[1]);

        Classifier b;
        b.readIn(argv[2]);
        b.get_accuracy(argv[3]);
        b.print_to_file(argv[4]);
    }

    return 0;
}

void run_tests() {
    Catch::Session().run();
}