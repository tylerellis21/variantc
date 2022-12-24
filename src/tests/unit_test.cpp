#include "unit_test.h"

#include <iostream>
#include <iomanip>

namespace cpptest {

UnitTest* currentUnit = 0;
TestCase* currentCase = 0;

UnitTestMapPtr unitTests = 0;

void registerTest(const std::string& unitName, const std::string& testName, TestCaseFunction function) {
    if (unitTests == 0) {
        unitTests = new UnitTestMap();
    }
    UnitTest* unit;
    UnitTestMap::iterator it = unitTests->find(unitName);

    if (it != unitTests->end()) {
        unit = it->second;
    }
    else {
        unit = new UnitTest(unitName);
        unitTests->emplace(unitName, unit);
    }

    unit->tests.push_back(TestCase(testName, function));

    std::cout << "registered: " << unitName << " - " << testName << " @ " << (void*)function << std::endl;
}

void runUnitTest(UnitTest* unitTest) {
}

void runTestCase(UnitTest* unitTest, TestCase* testCase) {

}

void runAllTests() {
    /*
    Come up with a better design/layout for printing the units and their test functions
    Since each unit can product std output,

    we should handle that as well while maintaining the readability of the test output

    show total test results
    # time taken for each unit
    # time taken for each test function
    # total time taken
    # passed / # total
    # failed / # total
    */
    std::cout << std::endl;
    std::cout << "[running " << unitTests->size() << " tests]" << std::endl;


    // TODO(@Tyler): Clean this up, perhaps break up into two functions?
    for (UnitTestMap::iterator i = unitTests->begin(); i != unitTests->end(); i++) {
        std::string name = i->first;
        UnitTest* unit = i->second;

        std::cout << std::endl << "[running unit: " << name << "]" << std::endl;

        // Gross, fix this by returning a test result structure of some sorts?
        currentUnit = unit;

        for (TestCaseVector::iterator t = unit->tests.begin(); t != unit->tests.end(); t++) {
            TestCase testCase = *t;

            // Gross, fix this by returning a test result structure of some sorts?
            currentCase = &testCase;

            std::cout << "    [running test case] " << testCase.name  << " @" << &testCase.function << " + " << std::endl;

            bool results = testCase.function();

            if (results) {
                std::cout << "        passed" << std::endl;
            }
            else {
                std::cout << "        failed" << std::endl;
            }

            std::cout << std::endl;
        }

        std::cout << "[finished running all tests]" << std::endl << std::endl;
    }
}

void _testAssert(const std::string& expression, const std::string& file, int line) {
    std::cout << "test assert failed" << std::endl << expression << " " << file << ":" << line << std::endl;
}

} // namespace cpptest