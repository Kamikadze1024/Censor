#include <iostream>
#include <string>
#include <fstream>
#include "FileReader.hpp"
#include "FileWriter.hpp"
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

        //получить путь к выходному файлу
        std::string outputFileName = argPars->getOutputFileName();

        //объект чтения большого файла
        std::shared_ptr<File::FileReader> inputFr = File::FileReader
                                                            ::getInstance();

        //объект записи выходного файла
        std::shared_ptr<File::FileWriter> outputFr = File::FileWriter
                                                            ::getInstance();

        //устанавливаю имя файла входного текста для чтения
        inputFr->setReadFilePath(inputFileName);

        //устанавливаю имя файла выходного файла для записи
        outputFr->setWriteFilePath(outputFileName);

        //устанавливаю указатель на потокобезопасную очередь
        std::shared_ptr<Containers::ThreadsafeQueue<std::string>> buffer;
        buffer.reset(new Containers::ThreadsafeQueue<std::string>());
        inputFr->setBuffer(buffer);
        outputFr->setBuffer(buffer);

        //читаю файл входного текста
        inputFr->readFile();

        //произвожу обработку (цензурирование)


        //записываю выходной файл
        outputFr->writeFile();

    } catch (Arguments::ArgsParserException &exc) {
        std::cout << exc.what() << std::endl;
    } catch (File::FileReadException &exc) {
        std::cout << exc.what() << std::endl;
    } catch (File::FileWriteException &exc) {
        std::cout << exc.what() << std::endl;
    } catch (...) {
        std::cout << "Неизвестное исключение" << std::endl;
    }

    return 0;
}
