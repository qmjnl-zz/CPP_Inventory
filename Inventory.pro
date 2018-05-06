#-------------------------------------------------
#
# Project created by QtCreator 2016-12-10T10:46:55
#
#-------------------------------------------------

QT       += core gui sql multimedia widgets


TARGET = Inventory
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mainmenu.cpp \
    inventoryitem.cpp \
    inventorytable.cpp \
    inventorycontroller.cpp \
    applicationroledialog.cpp \
    inventoryabstractmodel.cpp \
    inventoryservermodel.cpp \
    inventorylocalmodel.cpp \
    inventoryclientmodel.cpp

HEADERS  += mainwindow.h \
    mainmenu.h \
    inventoryitem.h \
    inventorytable.h \
    common.h \
    inventorycontroller.h \
    applicationroledialog.h \
    inventoryabstractmodel.h \
    inventoryservermodel.h \
    inventorylocalmodel.h \
    inventoryclientmodel.h

FORMS    += mainwindow.ui \
    applicationroledialog.ui

RESOURCES += \
    inventory.qrc
