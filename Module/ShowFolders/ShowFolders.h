#ifndef SHOWFOLDERS_H
#define SHOWFOLDERS_H

#include <QString>
#include <QProcess>
#include <QFile>
#include <QSettings>
#include <QCoreApplication>
#include <windows.h>
#include <QDebug>
#include <QFileDialog>
#include <QWidget>
#include <QProgressBar>
#include "ui_ShowFolders.h"
#include "showmessages.h"
#include "StyleSheetManager.h"



class ShowFolders : public QWidget
{
    Q_OBJECT

public:
    Ui::ShowFolders ui;
    explicit ShowFolders( QWidget *parent = nullptr);
    void ShowFolderMNC();
    void ShowFolderMNCUpdate();
    void onItemClicked();
    void onInstallationButtonClicked();
    void onCopyFileButtonClicked();
    void onUpdateFileButtonClicked();
    void compareAndMergeFiles(QString src, QString dst , QProgressBar *progressBar , int &counter, int totalItem);
    void copyPath(QString src, QString dst , QProgressBar *progressBar);
    void setWidgetOpacity(QWidget *widget, qreal opacity);







private:
    MainWindow *m_mainWindow;
    showMessages *m_showMessages;
    QString currentAction;
    QString destinationFolder;




//    MainWindow *m_mainWindow;


};


#endif // SHOWFOLDERS_H
