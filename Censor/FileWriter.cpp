#include "FileWriter.hpp"
#include <fstream>

namespace File {

//умный указатель на инстанцированный объект
static std::shared_ptr<FileWriter> fileWriterInstance = nullptr;

//инстанцирующий метод одиночки
std::shared_ptr<FileWriter> FileWriter::getInstance() {
    if(fileWriterInstance == nullptr) {
        fileWriterInstance.reset(new FileWriter());
    }
    return fileWriterInstance;
}

FileWriter::FileWriter() {
    m_pathToFile = "";
}

FileWriter::~FileWriter() {

}

/*
 * Установка пути к файлу, в который будем писать
 * Если такой путь не установлен - последует исключение
 */
void FileWriter::setWriteFilePath(std::string filePath) {
    m_pathToFile = filePath;
}

/*
 * Установить потокобезопасный буфер в объект для записи
 */
void FileWriter::setBuffer(std::shared_ptr<
                           Containers::ThreadsafeQueue<
                                                       std::string>
                           > buffer) {
    m_buffer = buffer;
}

/*
 * Записать файл
 */
void FileWriter::writeFile() {
    std::fstream f;
    f.open(m_pathToFile, (std::ios::out | std::ios::app));

    if(!f.is_open()) {
        return;
    }

    while(!m_buffer->empty()) {
        std::string valueStr;
        m_buffer->wait_and_pop(valueStr);
        f << valueStr;
    }


    f.close();
}

}
