#include <QDrag>
#include <QHeaderView>
#include <QMimeData>
#include <QMouseEvent>
#include <QSound>

#include "inventorytable.h"

InventoryTable::InventoryTable(bool adopted, QWidget *parent)
    : InventoryTable(0, 0, adopted, parent)
{

}

InventoryTable::InventoryTable(int rows, int columns, bool adopted, QWidget *parent)
    : QTableWidget(rows, columns, parent)
{
    if (adopted) {
        adoptWidget();
    }
}

void InventoryTable::adoptWidget()
{
    horizontalHeader()->hide();
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->hide();
    verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    setMaximumWidth(600);
    setFrameShape(QFrame::NoFrame);

    setSelectionMode(QAbstractItemView::SingleSelection);

    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    setIconSize(QSize(50, 50));

    m_applicationRole = AR_Local;
}

bool InventoryTable::hasHeightForWidth() const
{
    return true;
}

int InventoryTable::heightForWidth(int w) const
{
    return w;
}

InventoryTable::~InventoryTable()
{

}

void InventoryTable::setSoundName(const QString &soundName)
{
    m_soundName = soundName;
}

QTableWidgetItem* InventoryTable::addNewItem(const InventoryCellData& cellData)
{
    return addNewItem(cellData[cellRow].toInt(),
                      cellData[cellColumn].toInt(),
                      cellData[cellCount].toInt(),
                      QPixmap(cellData[cellImage].toString()),
                      cellData[cellSound].toString());
}

QTableWidgetItem* InventoryTable::addNewItem(int row, int column, int count, const QIcon &icon, const QString& sound)
{
    QTableWidgetItem* item = takeItem(row, column);
    if (item != Q_NULLPTR && count <= 0) {
        delete item;
    } else {
        item = new QTableWidgetItem();
        item->setTextAlignment(Qt::AlignRight | Qt::AlignBottom);
        item->setData(UserRoleCount, QVariant(count));
        item->setText(QString::number(count));
        item->setIcon(icon);
        setItem(row, column, item);
    }
    QSound::play(sound);
    return item;
}

void InventoryTable::setApplicationRole(ApplicationRole role)
{
    m_applicationRole = role;
    setDragEnabled(m_applicationRole != AR_Client);
    setAcceptDrops(m_applicationRole != AR_Client);
}

QString InventoryTable::mimeType() const
{
    return tr("application/x-dnditemdata");
}

void InventoryTable::mouseReleaseEvent(QMouseEvent *event)
{
    QTableWidgetItem* item = itemAt(event->pos());

    if (event->button() == Qt::RightButton && item != Q_NULLPTR && m_applicationRole != AR_Client) {
        int count = item->data(UserRoleCount).toInt() - 1;
        item->setData(UserRoleCount, count);
        item->setText(QString::number(count));

        QSound::play(m_soundName);

        InventoryCellData cellData;
        cellData[cellRow] = item->row();
        cellData[cellColumn] = item->column();
        cellData[cellCount] = count;
        cellData[cellImage] = "";
        cellData[cellSound] = m_soundName;
        emit cellDataChanged(cellData);

        if (count <= 0) {
            delete takeItem(item->row(), item->column());
        }

        clearSelection();
        clearFocus();
    }

    QTableWidget::mouseReleaseEvent(event);
}

void InventoryTable::startDrag(Qt::DropActions supportedActions)
{
    QTableWidgetItem *item = currentItem();
    if (item == Q_NULLPTR) {
        return;
    }

    QTableWidget::startDrag(supportedActions);
}

void InventoryTable::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->source() == this || event->mimeData()->hasFormat(mimeType())) {
        event->accept();
    } else {
        event->ignore();
    }
}

void InventoryTable::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->source() == this || event->mimeData()->hasFormat(mimeType())) {
        event->accept();
    } else {
        event->ignore();
    }
}

void InventoryTable::dropEvent(QDropEvent *event)
{
    if (event->source() == this) {
        QTableWidgetItem* sourceItem = currentItem();
        QTableWidgetItem* targetItem = itemAt(event->pos());

        if (sourceItem == targetItem) {
            event->ignore();
            return;
        }

        if (targetItem == Q_NULLPTR) {
            targetItem = addNewItem(rowAt(event->pos().y()), columnAt(event->pos().x()));
        }

        int countSource = sourceItem->data(UserRoleCount).toInt();
        sourceItem->setData(UserRoleCount, 0/*countSource*/);
        sourceItem->setText(QString::number(0/*countSource*/));

        int countTarget = targetItem->data(UserRoleCount).toInt() + countSource;
        targetItem->setData(UserRoleCount, countTarget);
        targetItem->setText(QString::number(countTarget));
        targetItem->setIcon(sourceItem->icon());

        InventoryCellData cellData;
        cellData[cellRow] = sourceItem->row();
        cellData[cellColumn] = sourceItem->column();
        cellData[cellCount] = 0;
        cellData[cellImage] = "";
        emit cellDataChanged(cellData);

        cellData[cellRow] = targetItem->row();
        cellData[cellColumn] = targetItem->column();
        cellData[cellCount] = countTarget;
        cellData[cellImage] = "";
        emit cellDataChanged(cellData);

        delete takeItem(sourceItem->row(), sourceItem->column());

        clearSelection();
        clearFocus();

    } else if (event->mimeData()->hasFormat(mimeType())) {
        QTableWidgetItem* targetItem = itemAt(event->pos());

        if (targetItem == Q_NULLPTR) {
            targetItem = addNewItem(rowAt(event->pos().y()), columnAt(event->pos().x()));
        }

        QByteArray itemData = event->mimeData()->data(mimeType());
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);
        QPixmap pixmap;
        dataStream >> pixmap;

        int count = targetItem->data(UserRoleCount).toInt() + 1;
        targetItem->setData(UserRoleCount, count);
        targetItem->setText(QString::number(count));
        targetItem->setIcon(QIcon(pixmap));

        InventoryCellData cellData;
        cellData[cellRow] = targetItem->row();
        cellData[cellColumn] = targetItem->column();
        cellData[cellCount] = count;
        cellData[cellImage] = "";
        emit cellDataChanged(cellData);

        clearSelection();
        clearFocus();

    } else {
        event->ignore();
    }
}
