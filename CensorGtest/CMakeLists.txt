cmake_minimum_required(VERSION 3.5)

project(CensorTests LANGUAGES CXX)


add_definitions(-DGTEST_LANGUAGE_CXX11)

find_package(Threads REQUIRED)

if ($ENV{GOOGLETEST_DIR})
    set(GOOGLETEST_DIR $ENV{GOOGLETEST_DIR})
else ()
    if (NOT "" STREQUAL "")
        message(WARNING "Using googletest src dir specified at Qt Creator wizard")
    endif ()
    set(GOOGLETEST_DIR "/usr/src")
endif ()
if (EXISTS ${GOOGLETEST_DIR})
    set(GTestSrc ${GOOGLETEST_DIR}/googletest)
    set(GMockSrc ${GOOGLETEST_DIR}/gmock)
elseif (UNIX AND EXISTS /usr/src/gtest)
    set(GTestSrc /usr/src/gtest)
    message(WARNING "Using gtest from system")
    if (EXISTS /usr/src/gmock)
        set(GMockSrc /usr/src/gmock)
    endif ()
else ()
    message( FATAL_ERROR "No googletest src dir found - set GOOGLETEST_DIR to enable!")
endif ()

set(GTestFiles ${GTestSrc}/src/gtest-all.cc)
set(GTestIncludes ${GTestSrc} "/usr/include/gtest")

if (NOT ${GMockSrc} STREQUAL "")
    list(APPEND GTestFiles ${GMockSrc}/src/gmock-all.cc)
    list(APPEND GTestIncludes ${GMockSrc} ${GMockSrc}/include)
endif ()

include_directories(${GTestIncludes})

# Добавляю библиотеки
set (CMAKE_CXX_FLAGS "-lboost_program_options")

# Добавляю сырци
set(censorSources
    "../Censor/argsparser.cpp"
    )

add_executable(CensorTests main.cpp tst_censortests.h
               ${censorSources} ${GTestFiles})
add_test(NAME CensorTests COMMAND CensorTests)
target_link_libraries(CensorTests PRIVATE Threads::Threads)

