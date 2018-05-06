#include <QApplication>

#include "inventorycontroller.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    InventoryController controller(&w);

    return a.exec();
}
