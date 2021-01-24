/*
 * Парсер аргументов командной строки.
 * Его обязанность - выпарсить:
 * - путь к входной файл
 * - путь к выходной файл
 * - путь к файл запрещенных слов
 * - путь к файл подстановок
 * Кашицын Д.В. <kamikadze1024@yandex.ru>
 * 2021
 */
#ifndef ARGSPARSER_HPP
#define ARGSPARSER_HPP

#include <memory>
#include <string>
#include <boost/program_options.hpp>

namespace Arguments {

using namespace boost::program_options;

//класс - исключение парсинга
class ArgsParserException final {
private:
    //сообщение об ошибке
    std::string m_msg;
public:
    //конструктор по-умолчанию
    ArgsParserException(std::string msg): m_msg(msg) {}

    //вывести сообщение
    std::string what() { return m_msg; }
};

class ArgsParser final {
private:
    //умный указатель на объект меню
    std::shared_ptr<options_description> m_menu;

    //карта переменных
    std::shared_ptr<variables_map>       m_vm;

    //хелп ли это?
    bool                                 m_isHelp;

    //входной файл
    std::string                          m_inputFile;

    //выходной файл
    std::string                          m_outputFile;

    //файл с подстановками
    std::string                          m_prohibitedFile;

    //файл запрещенных слов
    std::string                          m_substitutionFile;

    ArgsParser();

public:
    ~ArgsParser();

    //получить экземпляр парсера аргументов
    static std::shared_ptr<ArgsParser> getInstance();

    //обработать аргументы командной строки
    void processCommandLineOptions(int argc, char *argv[]);

    //хелп ли это?
    bool isHelp() const;

    //разрешаю только перемещающие конструктора и operator=
    ArgsParser(ArgsParser &&other);
    ArgsParser& operator=(ArgsParser &&other);

    //запрещаю копирующие конструктора и operator=
    ArgsParser(const ArgsParser&)            = delete;
    ArgsParser(ArgsParser&)                  = delete;
    ArgsParser& operator=(const ArgsParser&) = delete;
};

}

#endif // ARGSPARSER_HPP
