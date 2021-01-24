#include <iostream>

#include <CppUTest/CommandLineTestRunner.h>

using namespace std;

//включаю файлы, которые буду тестировать
#include "../Censor/argsparser.hpp"

TEST_GROUP(FirstTestGroup) {
};

TEST(FirstTestGroup, argHelpTest) {
    //кол-во строк
    int argc = 2;

    //0 первая строка
    char firstStr[100] = "/home/user/directory/executableFile";

    //1 вторая строка
    char secondStr[100] = "--help";

    char *argv[2];
    argv[0] = firstStr;
    argv[1] = secondStr;

    try {
        //Парсер аргументов командной строки
        std::shared_ptr<Arguments::ArgsParser> argPars
                = Arguments::ArgsParser::getInstance();

        //паршу аргументы
        argPars->processCommandLineOptions(argc, argv);

        //если это хелп:
        CHECK_EQUAL(true, argPars->isHelp());
    } catch (Arguments::ArgsParserException &exc) {
        std::cout << exc.what() << std::endl;
        FAIL("Exception during work");
    }
}

int main(int argc, char *argv[]) {
    return CommandLineTestRunner::RunAllTests(argc, argv);
}
