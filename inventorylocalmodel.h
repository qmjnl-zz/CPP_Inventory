#ifndef INVENTORYLOCALMODEL_H
#define INVENTORYLOCALMODEL_H

#include <QSqlDatabase>
#include <QSqlQuery>

#include "common.h"
#include "inventoryabstractmodel.h"

class InventoryLocalModel : public InventoryAbstractModel
{
    Q_OBJECT

public:
    explicit InventoryLocalModel(QObject *parent = 0);
    virtual ~InventoryLocalModel();

    virtual InventoryItemData inventoryItem() const;
    virtual void setInventoryItem(const InventoryItemData &inventoryItemData);
    virtual InventoryTableData inventoryTable() const;

signals:

public slots:
    virtual void updateCellData(const InventoryCellData& cellData);
    virtual void clearInventoryTable();

protected:
    QString m_databaseName = "inventory.db";
    QSqlDatabase m_database;

};

#endif // INVENTORYLOCALMODEL_H
