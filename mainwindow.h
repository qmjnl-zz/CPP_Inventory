#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStateMachine>

#include "common.h"
#include "inventoryitem.h"
#include "inventorytable.h"
#include "mainmenu.h"

namespace Ui {
class MainWindow;
}

/**
 * @brief Главное окно приложения/представление
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    /**
     * @brief Сигнал изменения ячейки инвентаря
     */
    void cellDataChanged(const InventoryCellData& cellData);
    /**
     * @brief Начало новой игры
     */
    void newGameStarted();

public slots:
    /**
     * @brief Сброс игровых данных
     */
    void reset();
    /**
     * @brief Настройка виджета Предмет
     */
    void setInventoryItem(const InventoryItemData &inventoryItemData);
    /**
     * @brief Настройка виджета игрового поля/инвентаря
     */
    void setInventoryTable(const InventoryTableData &inventoryTableData);
    /**
     * @brief Настройка виджета игрового поля/инвентаря
     */
    void setCellData(const InventoryCellData &inventoryCellData);
    /**
     * @brief Установка режима работы View
     */
    void setApplicationRole(ApplicationRole role);

protected:
    virtual void resizeEvent(QResizeEvent* event);

private:
    Ui::MainWindow *ui;
    MainMenu* m_mainMenu;
    InventoryTable* m_inventoryTable;
    InventoryItem* m_inventoryItem;

    QStateMachine m_stateMachine;

    ApplicationRole m_applicationRole;
};

#endif // MAINWINDOW_H
