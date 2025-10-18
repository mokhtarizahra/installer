#include "Designer.h"
#include "showmessages.h"
#include "StyleSheetManager.h"
#include <QDebug>
#include <QMessageBox>
#include <windows.h>
#include <Shellapi.h>

Designer::Designer( QWidget *parent )
    : QWidget(parent)
{


}
////////////////////////////////////////////////////////////////////////////
#include <QGraphicsOpacityEffect>
void Designer::setWidgetOpacity(QWidget *widget, qreal opacity)
{
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(widget);
    effect->setOpacity(opacity);
    widget->setGraphicsEffect(effect);
}
//////////////////////////////////////////////////////////////////////////////////////////////
void Designer::showRegitryfile(){

    this->setFixedSize(340, 475);

    setWidgetOpacity(ui.FileShowRegistry, 0.9);

    ui.registryButton->setStyleSheet(StyleSheetManager::buttonStyle());
    ui.messageLabel->setText("We will configure the necessary registry settings to ensure the application functions correctly");
    ui.messageLabel->setStyleSheet(StyleSheetManager::LabelStyle());
    ui.FileShowRegistry->setStyleSheet(StyleSheetManager::listWidgetStyle());
    ui.pathLineEditRej->setStyleSheet(StyleSheetManager::lineEditStyle());


    QString sourceFolderPath = "./Module/Registry/RegistryDesigner/RegistryFiles";
    qDebug() << "Checking directory:" << sourceFolderPath;

    QDir sourceDir(sourceFolderPath);
    QStringList regFiles = sourceDir.entryList(QStringList() << "*.reg", QDir::Files | QDir::NoDotAndDotDot);
    qDebug() << "Directory does exist!";


    if (regFiles.isEmpty()) {
        m_showMessages->showMessage("The source folder is empty!!", QMessageBox::Critical, QMessageBox::Ok);
        return;
    }

    qDebug() << "Files found: " << regFiles;
    if (ui.FileShowRegistry == nullptr) {
        qDebug() << "FileShowRegistry is nullptr!";
    } else {
        qDebug() << "FileShowRegistry is valid!";
    }
    ui.FileShowRegistry->setSelectionMode(QAbstractItemView::SingleSelection);


    ui.FileShowRegistry->clear(); // Assuming listWidget is defined in the UI
    for (const QString &folder : regFiles) {
        ui.FileShowRegistry->addItem(folder);
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <QProcess>

void Designer::Registryhandle(QListWidget *FileShowRegistry, QLineEdit *pathLineEditRej , showMessages *showMsgs) {
    QStringList selectedFiles;
    QString sourceFolderPath = "./Module/Registry/RegistryDesigner/RegistryFiles";

    QDir sourceDir(sourceFolderPath);
    QStringList regFiles = sourceDir.entryList(QStringList() << "*.reg", QDir::Files | QDir::NoDotAndDotDot);

    ui.FileShowRegistry->setSelectionMode(QAbstractItemView::SingleSelection);

    QListWidgetItem *selectedItem = FileShowRegistry->currentItem();
    if (selectedItem) {
        selectedFiles.append(selectedItem->text());
        qDebug() << selectedFiles;
    }

    if (selectedFiles.isEmpty()) {
        m_showMessages->showMessage("No registry files selected!", QMessageBox::Information, QMessageBox::Ok);
        return;
    }

    ui.pathLineEditRej->clear();
    ui.pathLineEditRej->setText(selectedFiles.join("; "));
    ui.pathLineEditRej->setEnabled(true);

    for (const QString &file : selectedFiles) {
        QString regFilePath = sourceFolderPath + "/" + file;

        if (QFile::exists(regFilePath)) {
            QString command = "C:\\Windows\\System32\\reg.exe";
            QStringList args = {"import", regFilePath, "/reg:64"}; // /reg:64

            QProcess process;
            process.start(command, args);
            process.waitForFinished();

            if (process.exitCode() == 0) {
                m_showMessages->showMessage("The registry file has been added successfully.", QMessageBox::Information, QMessageBox::Ok);
            } else {
                m_showMessages->showMessage("Failed to add the registry file. Make sure you have administrator privileges.", QMessageBox::Critical, QMessageBox::Ok);
            }
        } else {
            m_showMessages->showMessage("Registry file not found.", QMessageBox::Critical, QMessageBox::Ok);
        }
    }

    updateRegistryDSN();
}

///////////////////////////////////////////////////////////////////////////////////////////////
void Designer::onRegistry() {
    selectedFiles.clear();
    Registryhandle(ui.FileShowRegistry, ui.pathLineEditRej, m_showMessages);
}
//////////////////////////////////////////////////////////////////////////////////////////////
void Designer::updateRegistryDSN() {

    HKEY hKey;
    const char *keyPath = "SOFTWARE\\MNC\\SCADA";

    struct RegistryEntry {
        const char *name;
        const char *value;
    };

    RegistryEntry entries[] = {
        {"DSN Name", "MNC_SCADA"},
        {"Event DSN Name", "Event_DB"},
        {"HIS DSN Name", "HIS"},
        {"ICC DSN Name", "PAYA_ICC"}
    };

    LONG openResult = RegOpenKeyExA(HKEY_LOCAL_MACHINE, keyPath, 0, KEY_SET_VALUE | KEY_WOW64_64KEY, &hKey);
    qDebug() << "RegOpenKeyExA Result:" << openResult;

    if (openResult == ERROR_SUCCESS) {
        bool success = true;

        for (const auto &entry : entries) {
            LONG setResult = RegSetValueExA(hKey, entry.name, 0, REG_SZ, (BYTE*)entry.value, strlen(entry.value) + 1);
            qDebug() << "Setting" << entry.name << "to" << entry.value << "Result:" << setResult;

            if (setResult != ERROR_SUCCESS) {
                success = false;
                qDebug() << "Error setting value for" << entry.name << "Error Code:" << setResult;
            }
        }

        RegCloseKey(hKey);

        if (success) {
            qDebug() << "All registry values updated successfully!";
        } else {
            qDebug() << "Failed to update some registry values!";
        }
    } else {
        qDebug() << "Failed to open registry key! Error Code:" << openResult;
    }
}
