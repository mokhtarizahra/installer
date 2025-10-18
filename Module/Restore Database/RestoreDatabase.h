#ifndef RESTOREDATABASE_H
#define RESTOREDATABASE_H

#include "showmessages.h"
#include "ui_RestoreDatabase.h"
#include <QWidget>
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QProgressBar>

class RestoreDatabase: public QWidget
{
    Q_OBJECT

public:
    RestoreDatabase(QWidget *parent);
    void checkSelectedComponentsUpdateBackup();
    void restoreDatabase();
    bool setFullAccess(const QString &filePath, const QString &user);
    void setWidgetOpacity(QWidget *widget, qreal opacity);



private:
    Ui::RestoreDatabase ui;
    showMessages *m_showMessages;


};

#endif // RESTOREDATABASE_H
