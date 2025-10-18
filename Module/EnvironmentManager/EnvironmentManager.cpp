#include "EnvironmentManager.h"
#include "ui_EnvironmentManager.h"
#include "showmessages.h"
#include "StyleSheetManager.h"
#include <QMessageBox>
#include <QDebug>
#include <QDir>
#include "QFileDialog"
#include <Windows.h>


EnvironmentManager::EnvironmentManager(QWidget *parent)
{
    ui.setupUi(this);
    setWidgetOpacity(ui.messageLabel, 0.8);

    connect(ui.SetEnvironment, &QPushButton::clicked, this, &EnvironmentManager::onSetEnvClicked);
    ui.SetEnvironment->setStyleSheet(StyleSheetManager::buttonStyle());
    ui.messageLabel->setStyleSheet(StyleSheetManager::LabelStyle());
    ui.messageLabel->setText("Set the environment variables and paths before proceeding.");
    ui.pathLineEdit->setStyleSheet(StyleSheetManager::lineEditStyle());

    //    setWidgetOpacity(ui.messageLabel, 0.9);
    this->setFixedSize(340, 475);


}
////////////////////////////////////////////////////////////////////////////
#include <QGraphicsOpacityEffect>
void EnvironmentManager::setWidgetOpacity(QWidget *widget, qreal opacity)
{
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(widget);
    effect->setOpacity(opacity);
    widget->setGraphicsEffect(effect);
}
//////////////////////////////////////////////////////////////////////////////////////////
void EnvironmentManager::onSetEnvClicked()
{
    QString destinationFolderPath = QFileDialog::getExistingDirectory(this, "Select Destination Folder");
    if (destinationFolderPath.isEmpty()) {
        m_showMessages->showMessage(
                    tr("No destination folder selected!"),
                    QMessageBox::Critical,
                    QMessageBox::Ok
                    );
        return;
    }

    destinationFolder = destinationFolderPath;
    ui.pathLineEdit->setText(destinationFolderPath);
    //    nextButton->setDisabled(false);
    QString name;
    QString value;

    if (!destinationFolder.isEmpty() && QDir(destinationFolder).exists()) {
        qDebug() << "Destination folder is:" << destinationFolder;
        name = "PAYA_ROOT";
        value = destinationFolder;
    } else {
        //            nextButton->setDisabled(true);
        qDebug() << "Destination folder is not set!";
        m_showMessages->showMessage("The destination folder is not valid or not set. Please provide a valid path.", QMessageBox::Critical, QMessageBox::Ok);
        return;
    }

    bool success = setEnvironmentVariable(name, value);

    qDebug() << "Set environment variable result: " << success;

    if (success) {
        m_showMessages->showMessage("Environment variable set successfully.", QMessageBox::Information, QMessageBox::Ok);
    } else {
        m_showMessages->showMessage("Failed to set environment variable.", QMessageBox::Critical, QMessageBox::Ok);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////
bool  EnvironmentManager::setEnvironmentVariable(const QString &name, const QString &value)
{
    HKEY hKey;
    LONG result = RegOpenKeyExW(
                HKEY_CURRENT_USER,  // Change to HKEY_CURRENT_USER for testing
                L"Environment",  // This path is for the user's environment variables
                0,
                KEY_SET_VALUE,
                &hKey
                );

    if (result == ERROR_SUCCESS) {
        result = RegSetValueExW(
                    hKey,
                    reinterpret_cast<LPCWSTR>(name.utf16()),  // The name of the variable
                    0,
                    REG_SZ,  // Data type
                    reinterpret_cast<const BYTE *>(value.utf16()),  // The value
                    (value.size() + 1) * sizeof(wchar_t)
                    );

        RegCloseKey(hKey);

        if (result == ERROR_SUCCESS) {
            SendMessageTimeoutW(
                        HWND_BROADCAST,
                        WM_SETTINGCHANGE,
                        0,
                        reinterpret_cast<LPARAM>(L"Environment"),
                        SMTO_ABORTIFHUNG,
                        5000,
                        nullptr
                        );

            qDebug() << "Environment variable set successfully.";
            return true;
        } else {
            DWORD errorCode = GetLastError();
            qDebug() << "Failed to set environment variable. Error:" << errorCode;
            return false;

        }
    } else {
        DWORD errorCode = GetLastError();
        qDebug() << "Failed to open registry key. Error code:" << errorCode;

        m_showMessages->showMessage(
                    QString("Failed to open registry key for environment variables. Error code: %1").arg(errorCode),
                    QMessageBox::Critical,
                    QMessageBox::Ok
                    );
    }
}

////////////////////////////////////////////////////////////////////////////
