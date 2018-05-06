#ifndef APPLICATIONROLEDIALOG_H
#define APPLICATIONROLEDIALOG_H

#include <QDialog>
#include <QStateMachine>

#include "common.h"

namespace Ui {
class ApplicationRoleDialog;
}

class ApplicationRoleDialog : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(ApplicationRole applicationRole READ applicationRole)

public:
    explicit ApplicationRoleDialog(QWidget *parent = 0);
    ~ApplicationRoleDialog();
    ApplicationRole applicationRole() const;
    QString serverAddress() const;
    quint16 serverPort() const;

private:
    Ui::ApplicationRoleDialog *ui;

    QStateMachine m_stateMachine;
};

#endif // APPLICATIONROLEDIALOG_H
