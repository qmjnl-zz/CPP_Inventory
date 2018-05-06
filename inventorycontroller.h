#ifndef INVENTORYCONTROLLER_H
#define INVENTORYCONTROLLER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include "inventoryabstractmodel.h"
#include "mainwindow.h"

class InventoryController : public QObject
{
    Q_OBJECT
public:
    explicit InventoryController(MainWindow* view, QObject *parent = 0);
    virtual ~InventoryController();

signals:

public slots:

protected:
    InventoryAbstractModel* m_model;
    MainWindow* m_view;

    ApplicationRole m_applicationRole;
    QString m_windowTitle;

    QString m_serverAddress;
    quint16 m_serverPort;

};

#endif // INVENTORYCONTROLLER_H
