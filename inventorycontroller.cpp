#include <QApplication>
#include <QMessageBox>
#include <QNetworkInterface>

#include "applicationroledialog.h"
#include "inventorycontroller.h"
#include "inventoryclientmodel.h"
#include "inventorylocalmodel.h"
#include "inventoryservermodel.h"

InventoryController::InventoryController(MainWindow* view, QObject *parent)
    : QObject(parent), m_view(view)
{
    ApplicationRoleDialog dialog;
    dialog.exec();

    m_applicationRole = dialog.applicationRole();

    switch (m_applicationRole) {
    case AR_Local:
        m_model = new InventoryLocalModel(this);
        m_windowTitle = "Game Local";
        break;
    case AR_Server:
        m_model = new InventoryServerModel(this);
        m_serverAddress = qobject_cast<InventoryServerModel*>(m_model)->serverAddress();
        m_serverPort = qobject_cast<InventoryServerModel*>(m_model)->serverPort();
        m_windowTitle = tr("Game Server - IP: %2, port: %3").arg(m_serverAddress).arg(m_serverPort);
        break;
    case AR_Client:
        m_serverAddress = dialog.serverAddress();
        m_serverPort = dialog.serverPort();
        m_model = new InventoryClientModel(m_serverAddress, m_serverPort, this);
        m_windowTitle = tr("Game Client - IP: %2, port: %3").arg(m_serverAddress).arg(m_serverPort);
        break;
    default:
        m_model = new InventoryLocalModel(this);
        m_windowTitle = "Game Local";
        break;
    }

    m_windowTitle = tr("%1 %2").arg(qApp->applicationDisplayName()).arg(m_windowTitle);

    if (m_view != Q_NULLPTR) {
        QObject::connect(m_model, &InventoryAbstractModel::inventoryItemChanged, m_view, &MainWindow::setInventoryItem);
        QObject::connect(m_model, &InventoryAbstractModel::inventoryTableCleared, m_view, &MainWindow::reset);
        if (m_applicationRole == AR_Client) {
            QObject::connect(m_model, &InventoryAbstractModel::inventoryTableChanged, m_view, &MainWindow::setInventoryTable);
            QObject::connect(m_model, &InventoryAbstractModel::inventoryCellChanged, m_view, &MainWindow::setCellData);
        }
        QObject::connect(m_view, &MainWindow::cellDataChanged, m_model, &InventoryAbstractModel::updateCellData);
        QObject::connect(m_view, &MainWindow::newGameStarted, m_model, &InventoryAbstractModel::clearInventoryTable);
    }

    if (m_applicationRole == AR_Local || m_applicationRole == AR_Server) {
        InventoryItemData inventoryItemData;
        inventoryItemData[itemImage] = ":/images/apple.jpg";
        inventoryItemData[itemSound] = ":/sounds/apple.wav";
        m_model->setInventoryItem(inventoryItemData);
    }

    if (m_view != Q_NULLPTR) {
        m_view->setApplicationRole(m_applicationRole);
        m_view->setWindowTitle(m_windowTitle);
        m_view->setInventoryTable(m_model->inventoryTable());
        m_view->show();
    }
}

InventoryController::~InventoryController()
{

}
