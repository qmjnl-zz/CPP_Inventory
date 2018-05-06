#ifndef MAINMENU_H
#define MAINMENU_H

#include <QPushButton>
#include <QWidget>

#include "common.h"

/**
 * @brief Виджет главного меню приложения
 */
class MainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = Q_NULLPTR);
    virtual ~MainMenu();
    /**
     * @brief Установка режима работы View
     */
    void setApplicationRole(ApplicationRole role);

signals:
    /**
     * @brief Событие начала новой игры
     */
    void clickedStart();
    /**
     * @brief Выход из приложения
     */
    void clickedExit();

public slots:

protected:
    QPushButton* buttonStart;
    QPushButton* buttonExit;
    ApplicationRole m_applicationRole;

};

#endif // MAINMENU_H
