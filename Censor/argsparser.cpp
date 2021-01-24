#include "argsparser.hpp"
#include <iostream>

namespace Arguments {

static std::shared_ptr<ArgsParser> m_instance = nullptr;

ArgsParser::ArgsParser() {
    //это не хелп
    m_isHelp = false;

    //создаю объект меню
    m_menu.reset(new options_description{"Опции"});

    //задаю возможные ключи и их обработку
    m_menu->add_options()
            ("help,h", "Помощь")
            ("input,I", value<std::string>()->default_value(""),
             "Входной файл")
            ("output,O", value<std::string>()->default_value(""),
             "Выходной файл")
            ("prohibited,P", value<std::string>()->default_value(""),
             "Словарь запрещенных слов")
            ("substitution,S", value<std::string>()->default_value(""),
             "Словарь подстановок");
}

ArgsParser::~ArgsParser() {

}

ArgsParser::ArgsParser(ArgsParser &&other) {
    //умный указатель на объект меню
    m_menu = std::move(other.m_menu);

    //карта переменных
    m_vm = std::move(other.m_vm);

    //хелп ли это?
    m_isHelp = std::move(other.m_isHelp);

    //входной файл
    m_inputFile = std::move(other.m_inputFile);

    //выходной файл
    m_outputFile = std::move(other.m_outputFile);

    //файл с подстановками
    m_prohibitedFile = std::move(other.m_prohibitedFile);

    //файл запрещенных слов
    m_substitutionFile = std::move(other.m_substitutionFile);
}

ArgsParser& ArgsParser::operator=(ArgsParser &&other) {
    //умный указатель на объект меню
    m_menu = std::move(other.m_menu);

    //карта переменных
    m_vm = std::move(other.m_vm);

    //хелп ли это?
    m_isHelp = std::move(other.m_isHelp);

    //входной файл
    m_inputFile = std::move(other.m_inputFile);

    //выходной файл
    m_outputFile = std::move(other.m_outputFile);

    //файл с подстановками
    m_prohibitedFile = std::move(other.m_prohibitedFile);

    //файл запрещенных слов
    m_substitutionFile = std::move(other.m_substitutionFile);

    return *this;
}

//получить экземпляр парсера аргументов
std::shared_ptr<ArgsParser> ArgsParser::getInstance() {
    try {
        if(m_instance == nullptr) {
            m_instance.reset(new ArgsParser());
        }
    } catch (boost::program_options::error &err) {
        //бросаю "свое" исключение, чтобы отгородить свою логику от бустовой
        throw ArgsParserException(err.what());
    }

    return m_instance;
}

//обработать аргументы командной строки
void ArgsParser::processCommandLineOptions(int argc, char *argv[]) {
    try {
        //создаю карту переменных
        m_vm.reset(new variables_map());

        //паршу аргументы командной строки
        boost::program_options::store(
                    boost::program_options::parse_command_line(
                        argc, argv, *(m_menu.get())), *(m_vm.get()));

        boost::program_options::notify(*(m_vm.get()));

        //проверяю, может быть это --help
        //остальные поля не заполняю
        if(m_vm->count("help")) {
            m_isHelp = true;
            return;
        }

        //заполняю поля путей файлов
        //входной файл
        m_inputFile = m_vm.get()->operator[]("input").as<std::string>();

        //выходной файл
        m_outputFile = m_vm.get()->operator[]("output").as<std::string>();

        //файл с подстановками
        m_prohibitedFile = m_vm.get()->operator[]("prohibited")
                                    .as<std::string>();

        //файл запрещенных слов
        m_substitutionFile = m_vm.get()->operator[]("substitution")
                                        .as<std::string>();

    } catch (boost::program_options::error &err) {
        //бросаю "свое" исключение, чтобы отгородить свою логику от бустовой
        throw ArgsParserException(err.what());
    }
}

//хелп ли это?
bool ArgsParser::isHelp() const {
    return m_isHelp;
}

}
