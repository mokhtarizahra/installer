#include "showmessages.h"
#include "mainwindow.h"
#include "QMessageBox"

showMessages::showMessages( QWidget *parent) : QWidget(parent)
{

}


void showMessages::showMessage(const QString &messages, QMessageBox::Icon icon, QMessageBox::StandardButtons buttons) {
    QMessageBox *msgBox = createCustomMessageBox(messages, icon, buttons);
    msgBox->exec();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
QMessageBox* showMessages::createCustomMessageBox(const QString &text, QMessageBox::Icon icon, QMessageBox::StandardButtons buttons) {

    QMessageBox *msgBox = new QMessageBox();

    msgBox->setWindowTitle("Modje Niro");

    msgBox->setText(text);

    msgBox->setIcon(icon);
    msgBox->setWindowIcon(QIcon("./Icon.png"));


    msgBox->setStandardButtons(buttons);

    msgBox->setStyleSheet(
                "QMessageBox {"
                "    background-color: #f9f9f9;"
                "    border-radius: 10px;"
                "    font-family: 'Segoe UI', sans-serif;"
                "    font-size: 14px;"
                "    color: #333333;"
                "    border: 2px solid #004C99;"
                "    padding: 10px;"
                "    min-width: 300px;"
                "}"
                "QMessageBox QLabel {"
                "    font-size: 16px;"
                "    color: #333333;"
                "}"
                "QMessageBox QPushButton {"
                "    background-color: #004C99;"
                "    color: #FFEB3B;"
                "    border: 1px solid #004C99;"
                "    border-radius: 5px;"
                "    padding: 5px 15px;"
                "    font-size: 14px;"
                "    margin: 5px;"
                "}"
                "QMessageBox QPushButton:hover {"
                "    background-color: #003366;"
                "}"
                "QMessageBox QPushButton:pressed {"
                "    background-color: #003366;"
                "}"
                );

    return msgBox;
}
//////////////////////////////////////////////////////////////////////
QMessageBox::StandardButton showMessages::showMessageWithResponse(const QString &messages, QMessageBox::Icon icon, QMessageBox::StandardButtons buttons) {
    QMessageBox *msgBox = createCustomMessageBox(messages, icon, buttons);
    return static_cast<QMessageBox::StandardButton>(msgBox->exec());
}
