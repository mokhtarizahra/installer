#ifndef DESIGNER_H
#define DESIGNER_H

#include <QString>
#include <QStringList>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QListWidget>
#include <QLineEdit>
#include <QWidget>
#include "ui_Registry.h"
#include "showmessages.h"

class Designer  :  public QWidget {
    Q_OBJECT
public:
    Ui::Registry ui;
    explicit Designer(QWidget *parent = nullptr);
    void Registryhandle(QListWidget *FileShowRegistry, QLineEdit *pathLineEditRej, showMessages *showMsgs);
    void showRegitryfile();
    void onRegistry();
    void updateRegistryDSN();
    void setWidgetOpacity(QWidget *widget, qreal opacity);
    bool isAdministrator();
    void writeRegistry64();



    showMessages *m_showMessages;
    QStringList selectedFiles;

};

#endif // DESIGNER_H
