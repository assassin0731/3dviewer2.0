QT       += core gui opengl openglwidgets gifimage
include(../src/QtGifImage/gifimage/qtgifimage.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../src/View/main.cc \
    ../src/View/object_window.cc \
    ../src/Model/obj_model.cc \
    ../src/Controller/controller.cc \
    ../src/View/main_window.cc \
    ../src/Matrix/help_functions.cc \
    ../src/Matrix/operators.cc \
    ../src/Matrix/s21_matrix_oop.cc \
    ../src/Model/command.cc \
    ../src/Model/facade.cc \
    ../src/Model/geometry.cc

HEADERS += \
    ../src/View/object_window.h \
    ../src/Model/obj_model.h \
    ../src/Controller/controller.h \
    ../src/View/main_window.h \
    ../src/Model/settings.h \
    ../src/Matrix/s21_matrix_oop.h \
    ../src/Model/command.h \
    ../src/Model/facade.h \
    ../src/Model/geometry.h \
    ../src/Model/memento.h

FORMS += \
    ../src/View/main_window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../src/Resources/MyResource.qrc


