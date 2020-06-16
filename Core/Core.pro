QMAKE_EXTRA_TARGETS += before_build makefilehook
makefilehook.target = $(MAKEFILE)
makefilehook.depends = .beforebuild

PRE_TARGETDEPS += .beforebuild
before_build.target = .beforebuild
before_build.depends = FORCE
before_build.commands = chcp 1251

QT += core gui widgets

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++17

SOURCES += $$files(src/*.cpp)
HEADERS += $$files(src/*.h)
FORMS += $$files(src/*.ui)
