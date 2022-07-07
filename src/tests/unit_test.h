#ifndef VC_UNIT_TEST_H_INCLUDE
#define VC_UNIT_TEST_H_INCLUDE

#include <map>
#include <vector>
#include <string>
#include <functional>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define AT __FILE__ ":" TOSTRING(__LINE__)

namespace vc {

typedef std::function<bool()> TestCaseFunction;

struct TestCase {
    std::string name;
    TestCaseFunction function;

    TestCase(std::string name, TestCaseFunction function) :
        name(name),
        function(function)
    { }
};

typedef std::vector<TestCase> TestCaseVector;

struct UnitTest {
    std::string name;
    TestCaseVector tests;

    UnitTest(std::string name) :
        name(name)
    { }
};

struct TestCaseResult {
    bool result;
    TestCase* testCase;
};

struct UnitTestResult {
    bool result;
    UnitTest* unitTest;
};

typedef std::map<std::string, UnitTest*> UnitTestMap;

extern UnitTestMap unitTests;

void registerTest(std::string unitName, std::string testName, TestCaseFunction function);

void runAllTests();

struct TestAutoRegister {
    TestAutoRegister(std::string unitName, std::string testName, TestCaseFunction function) {
        registerTest(unitName, testName, function);
    }
};

#define TEST(unitName, testName) \
    bool unitName##testName(); \
    TestAutoRegister _register_##unitName##testName(#unitName, #testName, unitName##testName); \
    bool unitName##testName()

} // namespace vc

#endif // VC_UNIT_TEST_H_INCLUDE