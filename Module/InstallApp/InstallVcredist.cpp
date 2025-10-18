#include "InstallVcredist.h"
#include "showmessages.h"
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QSettings>
#include <QDebug>
#include <QProcess>



InstallVcredist::InstallVcredist(QObject *parent) : QObject(parent)
{

}


void InstallVcredist::install() {
    qDebug() << "Installing vcredist_2008...";

    if (isInstall()) {
        qDebug() << "vcredist_2008 is already installed.";
        m_showMessages->showMessage("vcredist_2008 is already installed.", QMessageBox::Information, QMessageBox::Ok);
    } else {
        // Path to the vcredist_2008 installer
        QString installerPath = QCoreApplication::applicationDirPath() + "/Module/InstallApp/tools/vcredist_2008.exe";

        // Debug: Print the installer path
        qDebug() << "Installer path:" << installerPath;

        if (QFile::exists(installerPath)) {
            QProcess process;
            process.setProgram(installerPath);

            // Start the installation process interactively


            if (!process.startDetached()) {
                qDebug() << "Failed to start the vcredist_2008 installer!";
                m_showMessages->showMessage("Failed to start the vcredist_2008 installer!", QMessageBox::Critical, QMessageBox::Ok);
                return;
            } else {
                qDebug() << "vcredist_2008 installer started successfully.";
            }

            // Inform the user to complete the installation
           // m_showMessages->showMessage("Please complete the vcredist_2008 installation process.", QMessageBox::Information, QMessageBox::Ok);
        } else {
            qDebug() << "Installer file does not exist:" << installerPath;
            m_showMessages->showMessage("vcredist_2008 installer is missing in the application directory.", QMessageBox::Critical, QMessageBox::Ok);
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool InstallVcredist::isInstall() {
    // Check if vcredist_2008 is installed by looking for its registry entry
    QSettings registry("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", QSettings::NativeFormat);
    QStringList keys = registry.childGroups();

    for (const QString &key : keys) {
        registry.beginGroup(key);
        QString displayName = registry.value("DisplayName").toString();
        registry.endGroup();

        if (displayName.contains("Microsoft Visual C++ 2008", Qt::CaseInsensitive)) {
            qDebug() << "vcredist_2008 is installed.";
            return true;
        }
    }

    qDebug() << "vcredist_2008 is NOT installed.";
    return false;
}
