#include "FileReader.hpp"
#include <iostream>
#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/filesystem.hpp>

namespace File {

//умный указатель на инстанцированный объект
static std::shared_ptr<FileReader> fileReaderInstance = nullptr;

//временные константы
uint64_t       CONST_FILE_SIZE   = 9663676416;
std::string    CONST_STR_PATTERN = "String number is = ";
uint64_t       CONST_STR_ARR_SZ  = 4096;

//инстанцирующий метод одиночки
std::shared_ptr<FileReader> FileReader::getInstance() {
    if(fileReaderInstance == nullptr) {
        fileReaderInstance.reset(new FileReader());
    }
    return fileReaderInstance;
}

FileReader::FileReader() {
    m_pathToFile = "";
}

FileReader::~FileReader() {

}

/*
 * Установка пути к файлу, который будем читать
 * Если такой путь не установлен - последует исключение
 */
void FileReader::setReadFilePath(std::string filePath) {
    m_pathToFile = filePath;
}

/*
 * Прочитать файл
 */
void FileReader::readFile() {
    //если нет пути к файлу
    if(m_pathToFile == "") {
        std::string excMsg = "Нет пути к файлу";
        throw FileException(excMsg);
    }

    try {
        boost::filesystem::path p(m_pathToFile);

        if(!boost::filesystem::exists(p)) {
            std::string excMsg = "Файл недоступен";
            throw  FileException(excMsg);
        }

        //получаю размер файла в байтах
        boost::uintmax_t fileSize = boost::filesystem::file_size(p);

        //мапплю файл
        boost::iostreams::mapped_file_source f;
        f.open(p);

        //проверяю, открыт ли файл
        if(!f.is_open()) {
            std::string excStr = "Мап на файл не открыт";
            throw FileException(excStr);
        }

        //если размер файла и размер мапа не равны - исключение
        if(fileSize != f.size()) {
            std::string excMsg = "Размер мапа не равен размеру файла";
            throw FileException(excMsg);
        }

        //получаю указатель на начало смапленного файла
        const char *pStartByte = static_cast<const char*>(f.data());

        //читаю побайтно строки
        std::vector<char> arr;
        decltype(fileSize) arrIndex = 0;
        for(decltype(fileSize) i = 0; i < fileSize; i++) {
            //когда нашел конец строки, то сохраняю строку в буфер
            if((*(pStartByte + i)) == '\n') {
                //добавляю символ конца строки и нуль, дабы не корежить строки
                arr.emplace_back('\n');
                arr.emplace_back('\0');
                std::string str = arr.data();
                std::cout << str;
                arrIndex = 0;
                arr.clear();
                continue;
            }
            //заполняю массив
            arr.emplace_back(*(pStartByte + i));
            arrIndex++;
        }

        f.close();
    } catch (std::exception &e) {
        //заменяю внешнее исключение моим
        std::string excStr = e.what();
        throw FileException(excStr);
    }
}

}
