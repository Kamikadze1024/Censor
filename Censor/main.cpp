#include <iostream>
#include <string>
#include "Functions.hpp"
#include "argsparser.hpp"

int main(int argc, char *argv[]) {
    try {
        //Парсер аргументов командной строки
        std::shared_ptr<Arguments::ArgsParser> argPars
                = Arguments::ArgsParser::getInstance();

        //паршу аргументы
        argPars->processCommandLineOptions(argc, argv);

        //если это хелп:
        if(argPars->isHelp()) {
            return 0;
        }
    } catch (Arguments::ArgsParserException &exc) {
        std::cout << exc.what() << std::endl;
    }

    return 0;
}
