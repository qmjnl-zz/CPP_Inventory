#include <QDataStream>
#include <QNetworkInterface>

#include "inventoryservermodel.h"

InventoryServerModel::InventoryServerModel(QObject *parent) :
    InventoryLocalModel(parent),
    m_server(new QTcpServer(this))
{
    // Server starting
    if (!m_server->listen()) {
        m_server->close();
        m_lastError = tr("Unable to start the game server: %1").arg(m_server->errorString());
    }

    // Free IP finding
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    for (auto it = ipAddressesList.begin(); it != ipAddressesList.end(); ++it) {
        if (*it != QHostAddress::LocalHost && it->toIPv4Address()) {
            m_serverAddress = it->toString();
            break;
        }
    }
    if (m_serverAddress.isEmpty()) {
        m_serverAddress = QHostAddress(QHostAddress::LocalHost).toString();
    }
    m_serverPort = m_server->serverPort();

    QObject::connect(m_server, &QTcpServer::newConnection, this, &InventoryServerModel::sendInitialData);
}

InventoryServerModel::~InventoryServerModel()
{

}

QString InventoryServerModel::serverAddress() const
{
    return m_serverAddress;
}

quint16 InventoryServerModel::serverPort() const
{
    return m_serverPort;
}

void InventoryServerModel::setInventoryItem(const InventoryItemData &inventoryItemData)
{
    InventoryLocalModel::setInventoryItem(inventoryItemData);

    // out to socket
    QTcpSocket* socket;
    foreach (socket, socketList) {
        if (socket != Q_NULLPTR) {
            QByteArray data;
            QDataStream stream(&data, QIODevice::WriteOnly);

            stream << qint32(DT_Item) << inventoryItem();
            socket->write(data);
        }
    }
}

void InventoryServerModel::updateCellData(const InventoryCellData& cellData)
{
    InventoryLocalModel::updateCellData(cellData);

    // out to socket
    QTcpSocket* socket;
    foreach (socket, socketList) {
        if (socket != Q_NULLPTR) {
            QByteArray data;
            QDataStream stream(&data, QIODevice::WriteOnly);

            stream << qint32(DT_Cell) << cellData;
            socket->write(data);
        }
    }
}

void InventoryServerModel::clearInventoryTable()
{
    InventoryLocalModel::clearInventoryTable();

    // out to socket
    QTcpSocket* socket;
    foreach (socket, socketList) {
        if (socket != Q_NULLPTR) {
            QByteArray data;
            QDataStream stream(&data, QIODevice::WriteOnly);

            stream << qint32(DT_ClearTable);
            socket->write(data);
        }
    }
}

void InventoryServerModel::sendInitialData()
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);

    stream << qint32(DT_Item) << inventoryItem();
    stream << qint32(DT_Table) << inventoryTable();

    QTcpSocket* socket = m_server->nextPendingConnection();
    socketList.push_back(socket);

    QObject::connect(socket, &QAbstractSocket::disconnected, socket, &QObject::deleteLater);
    QObject::connect(socket, &QAbstractSocket::disconnected, [this, socket]() {
        socketList.removeAll(socket);
    });

    socket->write(data);
}
