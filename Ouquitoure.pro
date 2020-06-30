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

INCLUDEPATH += "include/" \
               "deps/include/"

SOURCES += \
    # root
    $$files(src/*.cpp) \
    # generic app
    $$files(src/apps/*.cpp) \
    # opengl apps class
    $$files(src/apps/openGL/*.cpp) \
    # software base class
    $$files(src/apps/software/*.cpp)

HEADERS += \
    # root
    $$files(src/*.h) \
    # additional
    $$files(src/math/*.h) \
    # generic app
    $$files(src/apps/*.h) \
    # opengl apps
    $$files(src/apps/openGL/*.h) \
    # software apps
    $$files(src/apps/software/*.h)

FORMS += $$files(src/*.ui)

RESOURCES += \
    $$files(res/*.qrc)

DISTFILES += \
    .clang-format \
    # root include files
    $$files(include/*) \
    # additional includes
    $$files(include/Math/*) \
    # generic app includes
    $$files(include/Apps/*) \
    # opengl apps
    $$files(include/Apps/OpenGL/*) \
    # software apps
    $$files(include/Apps/Software/*)
