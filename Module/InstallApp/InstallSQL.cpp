#include "InstallSQL.h"
#include "showmessages.h"
#include <QCoreApplication>

InstallSQL::InstallSQL(QObject *parent) : QObject(parent) {
    m_showMessages = new showMessages();
}

void InstallSQL::install() {
    qDebug() << "Installing SQL Server...";
    if (isInstall()) {
        qDebug() << "SQL Server 2019 installed successfully.";
        m_showMessages->showMessage("SQL Server 2019 installed successfully.", QMessageBox::Information, QMessageBox::Ok);
    } else {
        // If SQL Server is not installed, we start the installation process
        QString installerPath1 = QCoreApplication::applicationDirPath() + "/Module/InstallApp/Microsoft Sql 2019/setup.exe";

        if (QFile::exists(installerPath1)) {
            QProcess process1;
            process1.setProgram("cmd.exe");
            process1.setArguments(QStringList() << "/c" << "start /wait setup.exe");

            process1.setWorkingDirectory(QFileInfo(installerPath1).absolutePath());
            process1.start();

            if (!process1.waitForStarted()) {
                qDebug() << "Failed to start the Microsoft SQL 2019 Enterprise installer!";
            } else {
                qDebug() << "Microsoft SQL 2019 Enterprise installer started successfully.";
            }

            if (!process1.waitForFinished()) {
                qDebug() << "Error while waiting for Microsoft SQL 2019 Enterprise installer to finish!";
            } else {
                qDebug() << "Microsoft SQL 2019 Enterprise installer finished.";
            }

            // After installation, we check again if SQL Server is installed or not
            if (isInstall()) {
                qDebug() << "SQL Server 2019 installed successfully.";
                m_showMessages->showMessage("SQL Server 2019 installed successfully.", QMessageBox::Information, QMessageBox::Ok);
            } else {
                qDebug() << "SQL Server 2019 installation failed.";
                m_showMessages->showMessage("SQL Server 2019 installation failed or not detected!", QMessageBox::Critical, QMessageBox::Ok);
            }
        } else {
            qDebug() << "Checking if file 1 exists:" << installerPath1;
            qDebug() << "Installer 1 exists: " << QFile::exists(installerPath1);
            m_showMessages->showMessage("SQL Server 2019 installers are missing in the application directory.", QMessageBox::Critical, QMessageBox::Ok);

        }
    }

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <QDir>

bool InstallSQL::isInstall() {
    QString installPath = "C:/Program Files/Microsoft SQL Server/MSSQL15.MSSQLSERVER"; //   SQL Server 2019

    QDir dir(installPath);
    if (dir.exists()) {
        qDebug() << "SQL Server is installed.";
        return true;
    } else {
        qDebug() << "SQL Server is NOT installed.";
        return false;
    }
}
