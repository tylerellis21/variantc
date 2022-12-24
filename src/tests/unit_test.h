#ifndef CPPTEST_UNIT_TEST_H_INCLUDE
#define CPPTEST_UNIT_TEST_H_INCLUDE

#include <map>
#include <vector>
#include <string>
#include <functional>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define AT __FILE__ ":" TOSTRING(__LINE__)

namespace cpptest {

using namespace std;

struct TestCase;
struct UnitTest;

typedef bool (*TestCaseFunction)();
typedef std::vector<TestCase> TestCaseVector;
typedef std::map<std::string, UnitTest*> UnitTestMap;
typedef UnitTestMap* UnitTestMapPtr;

void registerTest(const std::string&, const std::string&, TestCaseFunction);

struct TestCase {
    std::string name;
    TestCaseFunction function;

    TestCase(std::string name, TestCaseFunction function) :
        name(name),
        function(function)
    { }
};

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

struct TestAutoRegister {
    TestAutoRegister(std::string unitName, std::string testName, TestCaseFunction function) {
        registerTest(unitName, testName, function);
    }
};

extern UnitTestMap* unitTests;

void registerTest(const std::string& unitName, const std::string& testName, TestCaseFunction function);

void runAllTests();

void _testAssert(const std::string& expression, const std::string& file, int line);

#define TEST(unitName, testName) \
    bool unitName##testName(); \
    TestAutoRegister _register_##unitName##testName(#unitName, #testName, unitName##testName); \
    bool unitName##testName()

#define TEST_ASSERT(expression) if (!(expression)) { _testAssert(#expression, __FILE__, __LINE__); return false; }


} // namespace cpptest

#endif // CPPTEST_UNIT_TEST_H_INCLUDE