#include "Registry.h"
#include "ui_Registry.h"
#include "showmessages.h"
#include <QDebug>
#include <QMessageBox>
#include <windows.h>
#include <Shellapi.h>



Registry::Registry(QWidget *parent)
    : Designer(parent)
{
    qDebug() << "Registry constructor started";

    ui.setupUi(this);
    qDebug() << "After ui.setupUi";

    ui.messageLabel->setText("We will configure the necessary registry settings to ensure the application functions correctly");
    qDebug() << "Before showRegitryfile";
    showRegitryfile();
    qDebug() << "After showRegitryfile";

    connect(ui.registryButton, &QPushButton::clicked, this, &Designer::onRegistry);
    qDebug() << "After connect";

}


//////////////////////////////////////////////////////////////////////////////////////

