#ifndef INVENTORYABSTRACTMODEL_H
#define INVENTORYABSTRACTMODEL_H

#include <QObject>

#include <common.h>

/**
 * @brief Абстрактная модель данных
 */
class InventoryAbstractModel : public QObject
{
    Q_OBJECT

    /**
     * @brief Единица обмена данными между моделью и представлением
     */
    Q_PROPERTY(InventoryItemData inventoryItem READ inventoryItem WRITE setInventoryItem NOTIFY inventoryItemChanged)

public:
    explicit InventoryAbstractModel(QObject *parent = 0);
    virtual ~InventoryAbstractModel();

    /**
     * @brief Сведения о последней ошибке в модели данных
     */
    virtual QString lastError() const;

    /**
     * @brief Получение данных о Предмете
     */
    virtual InventoryItemData inventoryItem() const = 0;

    /**
     * @brief Запись в базу данных о Предмете
     */
    virtual void setInventoryItem(const InventoryItemData &inventoryItemData) = 0;

    /**
     * @brief Получение данных об игровом поле/инвентаре
     */
    virtual InventoryTableData inventoryTable() const = 0;

signals:

    /**
     * @brief Событие изменения объекта Предмет
     */
    void inventoryItemChanged(const InventoryItemData &inventoryItemData);
    /**
     * @brief Событие об изменении в ячейках инвентаря
     */
    void inventoryCellChanged(const InventoryCellData &inventoryCellData);
    /**
     * @brief Событие готовности данных для инвентаря
     */
    void inventoryTableChanged(const InventoryTableData &inventoryTableData);
    /**
     * @brief Событие очистки игрового поля/инвентаря
     */
    void inventoryTableCleared();

public slots:

    /**
     * @brief Запись в базу состояния текущей ячейки игрового поля/инвентаря
     */
    virtual void updateCellData(const InventoryCellData& cellData) = 0;

    /**
     * @brief Очистка данных об игровом поле (ячейках)
     */
    virtual void clearInventoryTable() = 0;

protected:
    mutable QString m_lastError;

};

#endif // INVENTORYABSTRACTMODEL_H
