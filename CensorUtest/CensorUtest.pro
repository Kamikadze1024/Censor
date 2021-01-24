TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

#CPPUTEST_HOME=/usr/include/CppUTest
#CPPFLAGS += -I$(CPPUTEST_HOME)/include


LIBS += -lCppUTest -lCppUTestExt -lboost_program_options

SOURCES += \
        ../Censor/argsparser.hpp \
        main.cpp
