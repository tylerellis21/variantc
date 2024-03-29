#include <ctime>
#include <iostream>
#include <chrono>
#include <thread>

#include <vc/compiler/lexer.h>

using namespace vc;

#include "unit_test.h"

#include <windows.h>

/*
Tests needed:
    Numerics
    Word
    Operators & Symbols
    Escape Sequences
    Strings
    Chars
*/


int main(int argc, char** args) {
    TokenKind test = TokenKind::Int32;

    char buffer[256];
    GetCurrentDirectoryA(256, buffer);
    printf("\ncurrent working directory: %s\n", buffer);

    cpptest::runAllTests();

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