#include <iostream>

#include <CppUTest/CommandLineTestRunner.h>

using namespace std;

//подключаю тестируемый файл
#include "../Censor/Functions.hpp"

TEST_GROUP(FirstTestGroup) {
};

TEST(FirstTestGroup, test1) {
    bool res = simpleTestWor();
    CHECK_EQUAL(res, true);
}

TEST(FirstTestGroup, test2) {
    bool res = simpleTestWor();
    CHECK_EQUAL(res, true);
}

int main(int argc, char *argv[]) {
    return CommandLineTestRunner::RunAllTests(argc, argv);
}
