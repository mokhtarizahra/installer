#ifndef SETODBC_H
#define SETODBC_H

#include <QString>
#include <QProcess>
#include <QWidget>
#include "showmessages.h"
#include "ui_SetODBC.h"

class MainWindow;


class SetODBC :  public QWidget
{
public:

    SetODBC (QWidget *parent);
   void createODBCDataandandpowershell(const QString &scriptPath);
   void createODBCDataSourceWithAuth();
   void setDefaultDatabaseAndTest(const QString &dsnName, const QString &databaseName );
   void createUserAndSetPrivileges();
   void setWidgetOpacity(QWidget *widget, qreal opacity);




private:
    Ui::SetODBC ui;
    MainWindow *m_mainWindow;
    showMessages *m_showMessages;

};

#endif // SETODBC_H
