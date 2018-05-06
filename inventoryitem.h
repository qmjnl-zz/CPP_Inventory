#ifndef INVENTORYITEM_H
#define INVENTORYITEM_H

#include <QLabel>

#include "common.h"

/**
 * @brief Класс, описывающий объект Предмет
 */
class InventoryItem : public QLabel
{
    Q_OBJECT

public:
    explicit InventoryItem(bool adopted = false, QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    explicit InventoryItem(const QString &text, bool adopted = false, QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    /**
     * @brief Настройка виджета для корректного отображения и работы
     */
    void adoptWidget();
    /**
     * @brief Установка режима работы View
     */
    void setApplicationRole(ApplicationRole role);
    virtual bool hasHeightForWidth() const;
    virtual int heightForWidth(int w) const;
    virtual ~InventoryItem();
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    ApplicationRole m_applicationRole;
};

#endif // INVENTORYITEM_H
