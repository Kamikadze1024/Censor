#include <iostream>
#include <string>
#include <fstream>
#include "FileReader.hpp"
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

        //получить путь к входному файлу
        std::string inputFileName = argPars->getInputFileName();

        //объект чтения большого файла
        std::shared_ptr<File::FileReader> inputFr = File::FileReader
                                                            ::getInstance();

        //устанавливаю имя файла для чтения
        inputFr->setReadFilePath(inputFileName);

        //устанавливаю указатель на потокобезопасную очередь
        std::shared_ptr<Containers::ThreadsafeQueue<std::string>> buffer;
        buffer.reset(new Containers::ThreadsafeQueue<std::string>());
        inputFr->setBuffer(buffer);

        //читаю файл
        inputFr->readFile();
    } catch (Arguments::ArgsParserException &exc) {
        std::cout << exc.what() << std::endl;
    } catch (File::FileException &exc) {
        std::cout << exc.what() << std::endl;
    } catch (...) {
        std::cout << "Неизвестное исключение" << std::endl;
    }

    return 0;
}
