TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


SOURCES += \
    src/main.cpp \
    src/filefn/t_filename.cpp \
    src/hfile/filehelper.cpp \
    src/hstring/stringhelper.cpp \
    src/hstring/gettokens.cpp \
    src/htime/timer.cpp \
    src/hfile/fn_control.cpp \
    src/filefn/filetreewalk.cpp

HEADERS += \
    src/filefn/t_filename.h \
    src/filefn/boost_cstdint.h \
    src/ftw/filetreewalk.h \
    src/hfile/filehelper.h \
    src/hstring/stringhelper.h \
    src/hstring/gettokens.h \
    src/txtrw/wList.h \
    src/txtrw/rList.h \
    src/htime/timer.h \
    src/hfile/fn_control.h \
    src/filefn/filetreewalk.h


#DESTDIR += bin
CONFIG  += x86_64

OBJECTS_DIR = .tmp
MOC_DIR = .tmp
UI_DIR = .tmp
RCC_DIR = .tmp

QMAKE_CXXFLAGS += -gdwarf-3

QMAKE_CXXFLAGS_DEBUG += -O0
QMAKE_CXXFLAGS_DEBUG += -std=c++0x
QMAKE_CXXFLAGS_DEBUG += -Wparentheses
QMAKE_CXXFLAGS_DEBUG += -Wreturn-type
QMAKE_CXXFLAGS_DEBUG += -Wshadow
QMAKE_CXXFLAGS_DEBUG += -Wextra
QMAKE_CXXFLAGS_DEBUG += -Wunused-parameter
QMAKE_CXXFLAGS_DEBUG += -Wwrite-strings
QMAKE_CXXFLAGS_DEBUG += -Wno-unused-variable
QMAKE_CXXFLAGS_DEBUG += -Weffc++

QMAKE_CXXFLAGS_RELEASE += -O2
QMAKE_CXXFLAGS_RELEASE += -std=c++0x
QMAKE_CXXFLAGS_RELEASE += -Wparentheses
QMAKE_CXXFLAGS_RELEASE += -Wreturn-type
QMAKE_CXXFLAGS_RELEASE += -Wshadow
QMAKE_CXXFLAGS_RELEASE += -Wextra
QMAKE_CXXFLAGS_RELEASE += -Wunused-parameter
QMAKE_CXXFLAGS_RELEASE += -Wwrite-strings
QMAKE_CXXFLAGS_RELEASE += -Wunused-variable
QMAKE_CXXFLAGS_RELEASE += -Weffc++

message("qmake stl_usage1")

INCLUDEPATH += $$PWD/src
INCLUDEPATH += $$PWD/src/hstring
INCLUDEPATH += $$PWD/src/hfile
INCLUDEPATH += $$PWD/src/filefn
INCLUDEPATH += $$PWD/src/ftw
INCLUDEPATH += $$PWD/src/boost
INCLUDEPATH += $$PWD/src/htime




LIBS += -lboost_thread -lboost_system -lboost_filesystem

OTHER_FILES += \
    lgpl-3.0.txt \
    README.md
