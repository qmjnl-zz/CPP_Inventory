#include <QHostInfo>
#include <QNetworkInterface>

#include "applicationroledialog.h"
#include "ui_applicationroledialog.h"

ApplicationRoleDialog::ApplicationRoleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ApplicationRoleDialog)
{
    ui->setupUi(this);
    ui->radioButtonServer->setChecked(true);

    ui->comboBoxServerAddress->setEditable(true);
    ui->comboBoxServerAddress->clear();
    ui->lineEditServerPort->setValidator(new QIntValidator(1, 65535, this));
    ui->labelServerAddress->setBuddy(ui->comboBoxServerAddress);
    ui->labelServerPort->setBuddy(ui->lineEditServerPort);

    // IP Addresses ->

    // find out name of this machine
    QString name = QHostInfo::localHostName();
    if (!name.isEmpty()) {
        ui->comboBoxServerAddress->addItem(name);
        QString domain = QHostInfo::localDomainName();
        if (!domain.isEmpty()) {
            ui->comboBoxServerAddress->addItem(name + QChar('.') + domain);
        }
    }
    if (name != QLatin1String("localhost")) {
        ui->comboBoxServerAddress->addItem(QString("localhost"));
    }

    // find out IP addresses of this machine
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

    // add non-localhost addresses
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (!ipAddressesList.at(i).isLoopback()) {
            ui->comboBoxServerAddress->addItem(ipAddressesList.at(i).toString());
        }
    }

    // add localhost addresses
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i).isLoopback()) {
            ui->comboBoxServerAddress->addItem(ipAddressesList.at(i).toString());
        }
    }


    // <- IP Addresses

    QState* nonClientState = new QState();
    QState* clientState = new QState();

    nonClientState->addTransition(ui->radioButtonClient, SIGNAL(clicked()), clientState);
    clientState->addTransition(ui->radioButtonServer, SIGNAL(clicked()), nonClientState);
    clientState->addTransition(ui->radioButtonLocal, SIGNAL(clicked()), nonClientState);

    nonClientState->assignProperty(ui->comboBoxServerAddress, "enabled", false);
    nonClientState->assignProperty(ui->lineEditServerPort, "enabled", false);
    clientState->assignProperty(ui->comboBoxServerAddress, "enabled", true);
    clientState->assignProperty(ui->lineEditServerPort, "enabled", true);

    m_stateMachine.addState(nonClientState);
    m_stateMachine.addState(clientState);
    m_stateMachine.setInitialState(nonClientState);
    m_stateMachine.start();


}

ApplicationRoleDialog::~ApplicationRoleDialog()
{
    delete ui;
}

ApplicationRole ApplicationRoleDialog::applicationRole() const
{
    ApplicationRole role = AR_Server;

    if (ui->radioButtonServer->isChecked()) {
        role = AR_Server;
    }
    if (ui->radioButtonClient->isChecked()) {
        role = AR_Client;
    }
    if (ui->radioButtonLocal->isChecked()) {
        role = AR_Local;
    }

    return role;
}

QString ApplicationRoleDialog::serverAddress() const
{
    return ui->comboBoxServerAddress->currentText();
}

quint16 ApplicationRoleDialog::serverPort() const
{
    return ui->lineEditServerPort->text().toUShort();
}
