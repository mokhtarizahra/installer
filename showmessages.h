#ifndef SHOWMESSAGES_H
#define SHOWMESSAGES_H


#include <QMessageBox>
#include <QWidget>

class MainWindow;

class showMessages : public QWidget
{
    Q_OBJECT
public:
    explicit showMessages(QWidget *parent = nullptr);
    static QMessageBox* createCustomMessageBox(const QString &text, QMessageBox::Icon icon, QMessageBox::StandardButtons buttons);
    void showMessage(const QString &messages, QMessageBox::Icon icon = QMessageBox::Information, QMessageBox::StandardButtons buttons = QMessageBox::Ok);
    QMessageBox::StandardButton showMessageWithResponse(const QString &messages, QMessageBox::Icon icon, QMessageBox::StandardButtons buttons);


private:
    MainWindow *m_mainWindow;

signals:

};

#endif // SHOWMESSAGES_H
