#ifndef COMMON_H
#define COMMON_H

#include <QMap>
#include <QString>
#include <QVariant>

/**
 * @brief Набор данных "Предмет" для обмена между моделью и представлением
 * image - имя картинки в ресурсах
 * sound - имя звука в ресурсах
 */
const QString itemImage = "image";
const QString itemSound = "sound";
typedef QMap<QString, QString> InventoryItemData;

/**
 * @brief Набор данных ячейки инвентаря для обмена между моделью и представлением
 * row - строка ячейки инвентаря
 * column - колонка ячейки инвентаря
 * count - количество предметов в ячейке
 * image - имя картинки в ресурсах
 * sound - звук, который нужно проиграть
 */
const QString cellRow = "row";
const QString cellColumn = "column";
const QString cellCount = "count";
const QString cellImage = "image";
const QString cellSound = "sound";
typedef QMap<QString, QVariant> InventoryCellData;

/**
 * @brief Набор данных инвентаря для обмена между моделью и представлением
 */
typedef QList<InventoryCellData> InventoryTableData;

/**
 * @brief Тип приложения: сервер, клиент, локальное
 */
enum ApplicationRole {
    AR_Server,
    AR_Client,
    AR_Local
};

/**
 * @brief Что передаём по сети:
 * предмет
 * ячейка инвентаря
 * инвентарь
 * сигнал очистить инвентарь
 */
enum DataToken {
    DT_Item,
    DT_Cell,
    DT_Table,
    DT_ClearTable
};

#endif // COMMON_H
