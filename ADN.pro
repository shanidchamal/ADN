#-------------------------------------------------
#
# Project created by QtCreator 2018-09-23T11:15:21
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = ADN
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    dialog_fd_input.cpp \
    dialog_fd_display.cpp \
    dialog_dm_view.cpp \
    dialog_dg_view.cpp \
    dialog_path_matrix.cpp \
    dialog_transitive_view.cpp \
    dialog_closure_view.cpp \
    dialog2nf.cpp

HEADERS += \
        mainwindow.h \
    dialog_fd_input.h \
    dialog_fd_display.h \
    dialog_dm_view.h \
    dialog_dg_view.h \
    dialog_path_matrix.h \
    dialog_transitive_view.h \
    dialog_closure_view.h \
    dialog2nf.h

FORMS += \
        mainwindow.ui \
    dialog_fd_input.ui \
    dialog_fd_display.ui \
    dialog_dm_view.ui \
    dialog_dg_view.ui \
    dialog_path_matrix.ui \
    dialog_transitive_view.ui \
    dialog_closure_view.ui \
    dialog2nf.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
