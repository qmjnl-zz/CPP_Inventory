#include <QPropertyAnimation>
#include <QSignalTransition>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_applicationRole(AR_Local)
{
    ui->setupUi(this);

    m_inventoryTable = new InventoryTable(3, 3, true, this);
    ui->horizontalLayout->insertWidget(1, m_inventoryTable);
    ui->horizontalLayout->setAlignment(m_inventoryTable, Qt::AlignVCenter);

    ui->pushButtonMenu->setMaximumWidth(200);

    m_inventoryItem = new InventoryItem(true, this);
    ui->verticalLayout->insertWidget(1, m_inventoryItem);

    ui->horizontalLayout->setStretch(0, 1);
    ui->horizontalLayout->setStretch(1, 6);
    ui->horizontalLayout->setStretch(2, 1);
    ui->horizontalLayout->setStretch(3, 2);
    ui->horizontalLayout->setStretch(4, 1);

    const int menuHeight = 60;
    m_mainMenu = new MainMenu(this);
    m_mainMenu->setGeometry(0, 0, width(), menuHeight);

    connect(m_mainMenu, SIGNAL(clickedStart()), this, SIGNAL(newGameStarted()));
    connect(m_mainMenu, SIGNAL(clickedExit()), this, SLOT(close()));
    connect(m_inventoryTable, &InventoryTable::cellDataChanged, this, &MainWindow::cellDataChanged);



    QState* s1 = new QState();
    QState* s2 = new QState();

    QSignalTransition* t1 = s1->addTransition(m_mainMenu, SIGNAL(clickedStart()), s2);
    QSignalTransition* t2 = s2->addTransition(ui->pushButtonMenu, SIGNAL(clicked()), s1);

    QPropertyAnimation* a = new QPropertyAnimation(m_mainMenu, "geometry", this);
    a->setDuration(500);

    t1->addAnimation(a);
    t2->addAnimation(a);

    s1->assignProperty(m_mainMenu, "geometry", QRect(0, 0, width(), menuHeight));
    s2->assignProperty(m_mainMenu, "geometry", QRect(0, 0, width(), 0));


    m_stateMachine.addState(s1);
    m_stateMachine.addState(s2);
    m_stateMachine.setInitialState(s1);
    m_stateMachine.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reset()
{
    m_inventoryTable->clearContents();
    m_inventoryTable->clearFocus();
}

void MainWindow::setInventoryItem(const InventoryItemData &inventoryItemData)
{
    m_inventoryItem->setPixmap(QPixmap(inventoryItemData[itemImage]));
    m_inventoryTable->setSoundName(inventoryItemData[itemSound]);
}

void MainWindow::setInventoryTable(const InventoryTableData &inventoryTableData)
{
    for (auto it = inventoryTableData.begin(); it != inventoryTableData.end(); ++it) {
        m_inventoryTable->addNewItem(*it);
    }
}

void MainWindow::setCellData(const InventoryCellData &inventoryCellData)
{
    m_inventoryTable->addNewItem(inventoryCellData);
}

void MainWindow::setApplicationRole(ApplicationRole role)
{
    m_applicationRole = role;
    m_inventoryItem->setApplicationRole(role);
    m_inventoryTable->setApplicationRole(role);
    m_mainMenu->setApplicationRole(role);
}

void MainWindow::resizeEvent(QResizeEvent* /*event*/)
{
    m_mainMenu->resize(width(), m_mainMenu->height());
}
