win32-msvc*{
    QMAKE_EXTRA_TARGETS += before_build makefilehook
    makefilehook.target = $(MAKEFILE)
    makefilehook.depends = .beforebuild

    PRE_TARGETDEPS += .beforebuild
    before_build.target = .beforebuild
    before_build.depends = FORCE
    before_build.commands = chcp 1251
}

QT += core gui widgets

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++17

INCLUDEPATH += "include/"

SOURCES += $$files(src/*.cpp) \
           $$files(src/openGL/*.cpp) \
           $$files(src/software/*.cpp)
HEADERS += $$files(src/*.h) \
           $$files(src/openGL/*.h) \
           $$files(src/software/*.h)
FORMS += $$files(src/*.ui)

RESOURCES += \
    res/icons.qrc

DISTFILES += \
    .clang-format \
    $$files(include/*) \
    $$files(include/OpenGLApps/*) \
    $$files(include/SoftwareApps/*)
