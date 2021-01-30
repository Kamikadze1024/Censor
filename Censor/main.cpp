#include <iostream>
#include <string>
#include <fstream>
#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/filesystem.hpp>
#include "argsparser.hpp"

uint64_t       CONST_FILE_SIZE   = 9663676416;
std::string    CONST_STR_PATTERN = "String number is = ";

//функция создания большого файла
void createBigFile() {
    std::cout << "Создаю огромный файл" << std::endl;

    std::ofstream f("bigFile.txt", std::ios::app | std::ios::out);

    if(!f.is_open()) {
        std::cout << "Невозможно открыть файл на запись" << std::endl;
        return;
    }

    //дописываю файл до того как аккумулятор не сравняется с размером
    decltype(CONST_FILE_SIZE) sizeAccum = 0;
    decltype(CONST_FILE_SIZE) i = 0;
    while(sizeAccum <= CONST_FILE_SIZE) {
        std::stringstream ss;
        ss << "String number is = " << std::to_string(i) << std::endl;
        f << ss.str() << std::endl;
        sizeAccum += ss.str().size();
        std::cout << std::to_string(sizeAccum) << "/"
                  << std::to_string(CONST_FILE_SIZE) << std::endl;
        i++;
    }

    f.close();
}

//Читаю большой файл
void readBigFile() {
    boost::filesystem::path p("bigFile.txt");

    if(!boost::filesystem::exists(p)) {
        std::cout << "Файл недоступен" << std::endl;
        return;
    }

    //получаю размер файла в байтах
    boost::uintmax_t fileSize = boost::filesystem::file_size(p);

    //мапплю файл
    boost::iostreams::mapped_file_source f;
    f.open(p);

    //проверяю, открыт ли файл
    if(!f.is_open()) {
        std::cout << "Файл не открыт" << std::endl;
    }

    std::cout << "Размер файла - " << fileSize << std::endl;
    std::cout << "Размер мапа  - " << f.size() << std::endl;

    //получаю указатель на начало смапленного файла
    const char *pStartByte = static_cast<const char*>(f.data());

    //устанавливаю указатель на начало последних 100 байт
    const char *pLastStr = pStartByte + (CONST_FILE_SIZE - 100 - 1);

    //читаю последние 100 байт
    char arr[100];
    memcpy(arr, pLastStr, 100);
    std::string res = arr;

    std::cout << "Res string = " << res << std::endl;

    f.close();
}

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

    //создаю огромный файл
    createBigFile();

    return 0;
}
