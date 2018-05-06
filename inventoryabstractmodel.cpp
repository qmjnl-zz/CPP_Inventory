#include "inventoryabstractmodel.h"

InventoryAbstractModel::InventoryAbstractModel(QObject *parent) : QObject(parent)
{

}

InventoryAbstractModel::~InventoryAbstractModel()
{

}

QString InventoryAbstractModel::lastError() const
{
    return m_lastError;
}
