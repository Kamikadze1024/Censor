/*
 * Чтение файла со входными данными
 */
#ifndef FILEREADER_HPP
#define FILEREADER_HPP

#include <memory>
#include <string>

namespace File {

//класс исключений
class FileException {
private:
    //сообщение
    std::string m_msg;

public:
    FileException(std::string &msg) : m_msg(msg) {}

    //вывести сообщение об ошибке
    std::string what() const noexcept { return m_msg; }
};

//класс читалки входного файла
class FileReader {
private:
    //путь к файлу, который будем читать
    std::string m_pathToFile;

    //конструктор по - умолчанию
    FileReader();

public:

    //метод инстанцирования
    static std::shared_ptr<FileReader> getInstance();

    //правило трех
    ~FileReader();
    FileReader(FileReader &other)            = delete;
    FileReader& operator=(FileReader &other) = delete;

    //запрет копирования
    void operator=(const FileReader &other) = delete;
    FileReader(const FileReader &other)     = delete;

    /*
     * Установка пути к файлу, который будем читать
     * Если такой путь не установлен - последует исключение
     */
    void setReadFilePath(std::string filePath);

    /*
     * Прочитать файл
     */
    void readFile();
};

}

#endif // FILEREADER_HPP