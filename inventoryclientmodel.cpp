#include "inventoryclientmodel.h"

InventoryClientModel::InventoryClientModel(const QString& serverAddress, quint16 serverPort, QObject *parent) :
    InventoryAbstractModel(parent),
    m_socket(new QTcpSocket(this)),
    m_serverAddress(serverAddress),
    m_serverPort(serverPort)
{
    m_stream.setDevice(m_socket);
    QObject::connect(m_socket, &QIODevice::readyRead, this, &InventoryClientModel::readData);
    QObject::connect(m_socket, static_cast<void(QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error), [=](/*QAbstractSocket::SocketError socketError*/) {
        m_lastError = m_socket->errorString();
    });

    m_socket->abort();
    m_socket->connectToHost(m_serverAddress, m_serverPort, QIODevice::ReadOnly);
}

InventoryClientModel::~InventoryClientModel()
{

}

InventoryItemData InventoryClientModel::inventoryItem() const
{
    return m_inventoryItemData;
}

void InventoryClientModel::setInventoryItem(const InventoryItemData &inventoryItemData)
{
    m_inventoryItemData = inventoryItemData;
    emit inventoryItemChanged(inventoryItemData);
}

InventoryTableData InventoryClientModel::inventoryTable() const
{
    return m_inventoryTableData;
}

void InventoryClientModel::updateCellData(const InventoryCellData& /*cellData*/)
{

}

void InventoryClientModel::clearInventoryTable()
{
    emit inventoryTableCleared();
}

void InventoryClientModel::readData()
{
    qint32 token;
    InventoryItemData itemData;
    InventoryCellData cellData;

    m_stream.startTransaction();

    while (!m_stream.atEnd()) {
        m_stream >> token;

        switch (token) {
        case DT_Item:
            m_stream >> itemData;
            setInventoryItem(itemData);
            break;
        case DT_Cell:
            m_stream >> cellData;
            if (cellData[cellImage].toString().isEmpty()) {
                cellData[cellImage] = m_inventoryItemData[itemImage];
            }
            emit inventoryCellChanged(cellData);
            break;
        case DT_Table:
            m_stream >> m_inventoryTableData;
            emit inventoryTableChanged(m_inventoryTableData);
            break;
        case DT_ClearTable:
            clearInventoryTable();
            break;
        default:
            break;
        }
    }

    m_stream.commitTransaction();
}
