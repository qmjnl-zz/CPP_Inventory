#ifndef INVENTORYSERVERMODEL_H
#define INVENTORYSERVERMODEL_H

#include <QTcpServer>
#include <QTcpSocket>

#include "inventorylocalmodel.h"

class InventoryServerModel : public InventoryLocalModel
{
    Q_OBJECT

public:
    explicit InventoryServerModel(QObject *parent = 0);
    virtual ~InventoryServerModel();

    QString serverAddress() const;
    quint16 serverPort() const;

    virtual void setInventoryItem(const InventoryItemData &inventoryItemData);

signals:

public slots:
    virtual void updateCellData(const InventoryCellData& cellData);
    virtual void clearInventoryTable();
    virtual void sendInitialData();

protected:
    QTcpServer* m_server;
    QString m_serverAddress;
    quint16 m_serverPort;
    QList<QTcpSocket*> socketList;
};

#endif // INVENTORYSERVERMODEL_H
