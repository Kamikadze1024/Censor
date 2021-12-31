/*
 * Класс записи в файл
 * Кашицын Денис <kamikadze1024@yandex.ru>
 */
#ifndef FILEWRITER_HPP
#define FILEWRITER_HPP

#include <memory>
#include <string>
#include "ThreadsafeQueue.hpp"

namespace File {

//класс исключений записи
class FileWriteException {
private:
    //сообщение
    std::string m_msg;

public:
    FileWriteException(std::string &msg) : m_msg(msg) {}

    //вывести сообщение об ошибке
    std::string what() const noexcept { return m_msg; }
};

//класс записи выходного файла
class FileWriter {
private:
    //путь к файлу, в который будем писать
    std::string m_pathToFile;

    //потокобезопасный буфер, куда сложены строки для записи
    std::shared_ptr<Containers::ThreadsafeQueue<std::string>> m_buffer;

    //конструктор по - умолчанию
    FileWriter();

public:

    //метод инстанцирования
    static std::shared_ptr<FileWriter> getInstance();

    //правило трех
    ~FileWriter();
    FileWriter(FileWriter &other)            = delete;
    FileWriter& operator=(FileWriter &other) = delete;

    //запрет копирования
    void operator=(const FileWriter &other) = delete;
    FileWriter(const FileWriter &other)     = delete;

    /*
     * Установка пути к файлу, который будем читать
     * Если такой путь не установлен - последует исключение
     */
    void setWriteFilePath(std::string filePath);

    /*
     * Установить потокобезопасный буфер в объект для чтения
     */
    void setBuffer(std::shared_ptr<
                                  Containers::ThreadsafeQueue<
                                                              std::string>
                                  > buffer);

    /*
     * Записать файл
     */
    void writeFile();
};

}

#endif // FILEWRITER_HPP
