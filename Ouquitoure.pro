TEMPLATE = subdirs
SUBDIRS = Core \

CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS

include(Core/Core.pro)
