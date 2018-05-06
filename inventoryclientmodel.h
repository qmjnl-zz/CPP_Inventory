#ifndef INVENTORYCLIENTMODEL_H
#define INVENTORYCLIENTMODEL_H

#include <QDataStream>
#include <QTcpSocket>

#include "common.h"
#include "inventoryabstractmodel.h"

class InventoryClientModel : public InventoryAbstractModel
{
    Q_OBJECT

public:
    explicit InventoryClientModel(const QString& serverAddress, quint16 serverPort, QObject *parent = 0);
    virtual ~InventoryClientModel();

    virtual InventoryItemData inventoryItem() const;
    virtual void setInventoryItem(const InventoryItemData &inventoryItemData);
    virtual InventoryTableData inventoryTable() const;

signals:

public slots:
    virtual void updateCellData(const InventoryCellData& cellData);
    virtual void clearInventoryTable();

protected slots:
    void readData();

protected:
    QTcpSocket* m_socket;
    QString m_serverAddress;
    quint16 m_serverPort;
    QDataStream m_stream;

    InventoryItemData m_inventoryItemData;
    InventoryTableData m_inventoryTableData;
};

#endif // INVENTORYCLIENTMODEL_H
