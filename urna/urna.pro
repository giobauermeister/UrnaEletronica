TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

# Platform specific macros
CONFIG(IMG_YOCTO,IMG_YOCTO|IMG_RASPBIAN):DEFINES+=PLATFORM_YOCTO
CONFIG(IMG_RASPBIAN,IMG_YOCTO|IMG_RASPBIAN):DEFINES+=PLATFORM_RASPBIAN

