win32-msvc*{
    QMAKE_EXTRA_TARGETS += before_build makefilehook
    makefilehook.target = $(MAKEFILE)
    makefilehook.depends = .beforebuild

    PRE_TARGETDEPS += .beforebuild
    before_build.target = .beforebuild
    before_build.depends = FORCE
    before_build.commands = chcp 1251
}

QT += core gui widgets opengl

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++17

INCLUDEPATH += "include/"

SOURCES += $$files(src/*.cpp) \
           $$files(src/openGL/*.cpp) \
           $$files(src/software/*.cpp) \
           $$files(src/utils/*.cpp)
HEADERS += $$files(src/*.h) \
           $$files(src/openGL/*.h) \
           $$files(src/software/*.h) \
           $$files(src/utils/*.h)
FORMS += $$files(src/*.ui)

RESOURCES += \
    $$files(res/*.qrc)

DISTFILES += \
    .clang-format \
    $$files(include/*) \
    $$files(include/OpenGLApps/*) \
    $$files(include/SoftwareApps/*) \
    $$files(include/Utils/*)
