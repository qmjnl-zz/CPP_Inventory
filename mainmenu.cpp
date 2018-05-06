#include <QLayout>

#include "mainmenu.h"

MainMenu::MainMenu(QWidget *parent) : QWidget(parent),
    m_applicationRole(AR_Local)
{
    QPalette pal = palette();
    QColor color = parent->palette().color(QPalette::AlternateBase);

    pal.setColor(QPalette::Window, color);
    setPalette(pal);
    setAutoFillBackground(true);

    buttonStart = new QPushButton(tr("Начать"), this);
    buttonExit = new QPushButton(tr("Выход"), this);

    const int w = 400;
    buttonStart->setMaximumWidth(w);
    buttonExit->setMaximumWidth(w);

    connect(buttonStart, SIGNAL(clicked(bool)), this, SIGNAL(clickedStart()));
    connect(buttonExit, SIGNAL(clicked(bool)), this, SIGNAL(clickedExit()));

    setLayout(new QHBoxLayout(this));
    layout()->addWidget(buttonStart);
    layout()->addWidget(buttonExit);
}

MainMenu::~MainMenu()
{

}

void MainMenu::setApplicationRole(ApplicationRole role)
{
    m_applicationRole = role;
    buttonStart->setEnabled(m_applicationRole != AR_Client);
}
