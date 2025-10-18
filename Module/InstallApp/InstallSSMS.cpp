#include "InstallSSMS.h"

InstallSSMS::InstallSSMS(QObject *parent) : QObject(parent)
{

}


void InstallSSMS::install(){
    // First, we check if SQL Server Management Studio (SSMS) is installed or not
    if (isInstall()) {
        qDebug() << "SQL Server Management Studio installed successfully.";
        m_showMessages->showMessage("SQL Server Management Studio installed successfully", QMessageBox::Information, QMessageBox::Ok);
    } else {
        // If SSMS is not installed, we start the installation process
        QString installerPath2 = "./Module/InstallApp/SQL.Server.Management.Studio.18.12.1.x64/SSMS-Setup-ENU.exe";

        if (QFile::exists(installerPath2)) {
            QProcess process2;
            process2.setProgram("cmd.exe");
            process2.setArguments(QStringList() << "/c" << "start /wait SSMS-Setup-ENU.exe");

            process2.setWorkingDirectory(QFileInfo(installerPath2).absolutePath());
            process2.start();

            if (!process2.waitForStarted()) {
                qDebug() << "Failed to start the SQL Server Management Studio installer!";
            } else {
                qDebug() << "SQL Server Management Studio installer started successfully.";
            }

            if (!process2.waitForFinished()) {
                qDebug() << "Error while waiting for SQL Server Management Studio installer to finish!";
            } else {
                qDebug() << "SQL Server Management Studio installer finished.";
            }

            // After installation, we check again if SSMS is installed or not
            if (isInstall()) {
                qDebug() << "SQL Server Management Studio installed successfully.";
                m_showMessages->showMessage("SQL Server Management Studio installed successfully", QMessageBox::Information, QMessageBox::Ok);
            } else {
                qDebug() << "SQL Server Management Studio installation failed.";
                m_showMessages->showMessage("SQL Server Management Studio installation failed or not detected!", QMessageBox::Critical, QMessageBox::Ok);
            }
        } else {
            qDebug() << "Checking if file 2 exists:" << installerPath2;
            qDebug() << "Installer 2 exists: " << QFile::exists(installerPath2);
            m_showMessages->showMessage("SQL Server Management Studio installers are missing in the application directory.", QMessageBox::Critical, QMessageBox::Ok);
        }
    }

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <QFileInfo>
#include <QDebug>
#include <QSettings>

bool InstallSSMS::isInstall() {
    try {

            QSettings ssmsRegistry64("HKEY_CURRENT_USER\\Software\\Microsoft\\SQL Server Management Studio", QSettings::NativeFormat);
            ssmsRegistry64.setFallbacksEnabled(false);

            if (!ssmsRegistry64.allKeys().isEmpty()) {
                qDebug() << " SSMS registry keys found.";
            } else {
                qDebug() << " SSMS registry keys not found.";
                return false; // Registry check failed
            }


            QString ssmsPath = "C:/Program Files (x86)/Microsoft SQL Server Management Studio 18";
            if (QFileInfo::exists(ssmsPath) && QFileInfo(ssmsPath).isFile()) {
                qDebug() << " SSMS found at path: " << ssmsPath;
            } else {
                qDebug() << " SSMS not found at path: " << ssmsPath;
                return false; // Path check failed
            }

            // If both checks are successful
            qDebug() << " SQL Server Management Studio (SSMS) is installed.";
            return true;

        } catch (...) {
            qDebug() << " Error while checking SSMS installation!";
            return false;
        }
    }
