#include "unit_test.h"
#include <iostream>

namespace vc {

UnitTestMap unitTests;

void registerTest(std::string unitName, std::string testName, TestCaseFunction function) {
    UnitTest* unit;
    UnitTestMap::iterator it = unitTests.find(unitName);

    if (it != unitTests.end()) {
        unit = it->second;
    }
    else {
        unit = new UnitTest(unitName);
        unitTests.emplace(unitName, unit); 
    }

    unit->tests.push_back(TestCase(testName, function));

    std::cout << "registered: " << unitName << " - " << testName << "@" << &function << std::endl;
}

void runAllTests() {

    // TODO(@Tyler): Clean this up, perhaps break up into two functions?

    for (UnitTestMap::iterator i = unitTests.begin(); i != unitTests.end(); i++) {
        std::string name = i->first;
        UnitTest* unit = i->second;

        std::cout << "running unit: " << name << std::endl;
        

        for (TestCaseVector::iterator t = unit->tests.begin(); t != unit->tests.end(); t++) {
            TestCase testCase = *t;
            
            std::cout << "running test case: " << testCase.name  << "@" << &testCase.function << " + ";
            
            bool results = testCase.function();

            if (results) {
                std::cout << "passed" << std::endl; 
            }
            else {
                std::cout << "failed" << std::endl; 
            }
        }
        
    }
}

} // namespace vc