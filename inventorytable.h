#ifndef INVENTORYTABLE_H
#define INVENTORYTABLE_H

#include <QTableWidget>

#include "common.h"

/**
 * @brief Класс, описывающий объект Инвентарь
 */
class InventoryTable : public QTableWidget
{
    Q_OBJECT

public:
    explicit InventoryTable(bool adopted = false, QWidget *parent = Q_NULLPTR);
    InventoryTable(int rows, int columns, bool adopted = false, QWidget *parent = Q_NULLPTR);
    /**
     * @brief Настройка виджета для корректного отображения и работы
     */
    void adoptWidget();
    virtual bool hasHeightForWidth() const;
    virtual int heightForWidth(int w) const;
    virtual ~InventoryTable();
    /**
     * @brief Установка звука (f.e. откусывание яблока)
     */
    void setSoundName(const QString &soundName);

    /**
     * @brief Добавление предмета в инвентарь
     */
    QTableWidgetItem* addNewItem(const InventoryCellData& cellData);
    /**
     * @brief Добавление предмета в инвентарь
     */
    QTableWidgetItem* addNewItem(int row, int column, int count = 0, const QIcon &icon = QIcon(), const QString& sound = "");

    /**
     * @brief Установка режима работы View
     */
    void setApplicationRole(ApplicationRole role);

signals:
    /**
     * @brief Событие изменения предмета в инвентаре (добавление/удаление предмета из ячейки)
     */
    void cellDataChanged(const InventoryCellData& cellData);

protected:
    /**
     * @brief Ключи для записи пользовательских данных в ячейки инвентаря
     */
    enum UserRole {
        UserRoleCount = Qt::UserRole,
        UserRolePixmap,
        UserRoleLocation
    };

    /**
     * @brief Тип Drag'n'Drop события
     */
    QString mimeType() const;

    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void startDrag(Qt::DropActions supportedActions);
    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dragMoveEvent(QDragMoveEvent *event);
    virtual void dropEvent(QDropEvent *event);

    QString m_soundName;

    ApplicationRole m_applicationRole;
};

#endif // INVENTORYTABLE_H
