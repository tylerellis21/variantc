#include <ctime>
#include <iostream>
#include <chrono>
#include <thread>

#include <vc/compiler/lexer.h>

using namespace vc;

#include "unit_test.h"

int main(int argc, char** args) {
    
    runAllTests();

    return 0;
}

/*
using namespace std::chrono_literals;
while (true) {
    auto start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(900000ns);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> elapsed = end - start;
    std::cout << "Waited " << elapsed.count() << " ns\n";
}
*/