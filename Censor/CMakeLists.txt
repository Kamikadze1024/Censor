cmake_minimum_required(VERSION 3.5)

project(Censor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Добавляю инклуды из текущей директории с проектом
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Добавляю библиотеки
set (CMAKE_CXX_FLAGS "-lboost_program_options -lboost_filesystem -lboost_iostreams")

# Добавляю сырци
set(censorSources
    main.cpp
    argsparser.cpp
    FileReader.cpp
    ThreadPool.cpp
    )

add_executable(Censor ${censorSources})
