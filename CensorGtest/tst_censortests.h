#ifndef TST_CENSORTESTS_H
#define TST_CENSORTESTS_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

TEST(CensorGtests, CensorTests)
{
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}

//включаю файлы, которые буду тестировать
#include "../Censor/argsparser.hpp"

TEST(CensorGtests, argHelpTest1) {
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
        ASSERT_EQ(true, argPars->isHelp());
    } catch (Arguments::ArgsParserException &exc) {
        std::cout << exc.what() << std::endl;
        FAIL();
    }
}

TEST(CensorGtests, argHelpTest2) {
    //кол-во строк
    int argc = 2;

    //0 первая строка
    char firstStr[100] = "/home/user/directory/executableFile";

    //1 вторая строка
    char secondStr[100] = "-h";

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
        ASSERT_EQ(true, argPars->isHelp());
    } catch (Arguments::ArgsParserException &exc) {
        std::cout << exc.what() << std::endl;
        FAIL();
    }
}

TEST(CensorGtests, argHelpTest3) {
    //кол-во строк
    int argc = 3;

    //0 первая строка
    char firstStr[100] = "/home/user/directory/executableFile";

    //1 вторая строка
    char secondStr[100] = "-h";

    //2 третья строка
    char thirdStr[100] = "-IinputFile.txt";

    char *argv[3];
    argv[0] = firstStr;
    argv[1] = secondStr;
    argv[2] = thirdStr;

    try {
        //Парсер аргументов командной строки
        std::shared_ptr<Arguments::ArgsParser> argPars
                = Arguments::ArgsParser::getInstance();

        //паршу аргументы
        argPars->processCommandLineOptions(argc, argv);

        //если это хелп:
        ASSERT_EQ(true, argPars->isHelp());
    } catch (Arguments::ArgsParserException &exc) {
        std::cout << exc.what() << std::endl;
        FAIL();
    }
}

TEST(CensorGtests, argHelpTest4) {
    //кол-во строк
    int argc = 3;

    //0 первая строка
    char firstStr[100] = "/home/user/directory/executableFile";

    //1 вторая строка
    char secondStr[100] = "-h";

    //2 третья строка
    char thirdStr[100] = "-IinputFile.txt";

    char *argv[3];
    argv[0] = firstStr;
    argv[1] = secondStr;
    argv[2] = thirdStr;

    try {
        //Парсер аргументов командной строки
        std::shared_ptr<Arguments::ArgsParser> argPars
                = Arguments::ArgsParser::getInstance();

        //паршу аргументы
        argPars->processCommandLineOptions(argc, argv);

        //если это хелп:
        ASSERT_EQ(true, argPars->isHelp());

        //если имя файла не выдает - валимся
        //получить путь к входному файлу
        std::string inputFileName = argPars->getInputFileName();

        std::string neStr = "";
        ASSERT_STREQ(neStr.c_str(), inputFileName.c_str());
    } catch (Arguments::ArgsParserException &exc) {
        std::cout << exc.what() << std::endl;
        FAIL();
    }
}

#endif // TST_CENSORTESTS_H
