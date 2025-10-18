#include "MainWindow.h"
#include "ShowFolders.h"
#include <QWidget>
#include <QSettings>
#include <windows.h>

ShowFolders::ShowFolders( QWidget *parent)
{
    ui.setupUi(this);

    this->setFixedSize(340, 475);
    setWidgetOpacity(ui.FileShowList, 0.9);


    connect(ui.copyFileButton, &QPushButton::clicked, this, &ShowFolders::ShowFolderMNC);
    connect(ui.updateFileButton, &QPushButton::clicked, this, &ShowFolders::ShowFolderMNCUpdate);
    connect(ui.InstallationButton, &QPushButton::clicked, this, &ShowFolders::onInstallationButtonClicked);

    ui.updateFileButton->setStyleSheet(StyleSheetManager::buttonStyle());
    ui.copyFileButton->setStyleSheet(StyleSheetManager::buttonStyle());
    ui.InstallationButton->setStyleSheet(StyleSheetManager::buttonStyle());
    ui.messageLabel->setText("Please select the installation folder.");
    ui.messageLabel->setStyleSheet(StyleSheetManager::LabelStyle());
    ui.FileShowList->setStyleSheet(StyleSheetManager::listWidgetStyle());
    ui.pathLineEdit->setStyleSheet(StyleSheetManager::lineEditStyle());
    ui.progressBar->setStyleSheet(StyleSheetManager::ProgressBarStyle());
    ui.progressBar->setRange(0, 100);
    ui.progressBar->setValue(0);


}
////////////////////////////////////////////////////////////////////////////
#include <QGraphicsOpacityEffect>
void ShowFolders::setWidgetOpacity(QWidget *widget, qreal opacity)
{
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(widget);
    effect->setOpacity(opacity);
    widget->setGraphicsEffect(effect);
}
/////////////////////////////////////////////////////////////////////////////

void ShowFolders::ShowFolderMNC(){

    QString sourceFolderPath = "./MNC_SCADA";

    // Step 1: Display folder contents in a checklist
    QDir sourceDir(sourceFolderPath);
    QStringList folders = sourceDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

    if (folders.isEmpty()) {
        m_showMessages->showMessage("The source folder is empty!", QMessageBox::Critical, QMessageBox::Ok);
        return;
    }

    // Clear and populate the QListWidget
    ui.FileShowList->clear(); // Assuming listWidget is defined in the UI
    for (const QString &folder : folders) {
        QListWidgetItem *item = new QListWidgetItem(folder, ui.FileShowList);
    }
    // Add a special "Back" item with a button
    QListWidgetItem *bakItem = new QListWidgetItem(ui.FileShowList);
    bakItem->setSizeHint(QSize(150, 45));
    auto *button = new QPushButton("Back", ui.FileShowList);
    button->setStyleSheet(StyleSheetManager::buttonStyle());
    // Set the button as the widget for the "Back" item
    ui.FileShowList->setItemWidget(bakItem, button);


    // Connect signal to slot
    connect(button, &QPushButton::clicked, this, &ShowFolders::onItemClicked);

    currentAction = "ShowFolderMNC";

}
///////////////////////////////////////////////////////////////////////////////
void ShowFolders::onItemClicked() {

    ui.FileShowList->clear();
    ui.updateFileButton->setDisabled(false);
    ui.copyFileButton->setDisabled(false);
}
//////////////////////////////////////////////////////////////////////////////
void ShowFolders::onInstallationButtonClicked() {

    if (currentAction == "ShowFolderMNC") {
        onCopyFileButtonClicked();
        ui.updateFileButton->setDisabled(false);
        qDebug() << "Action for ShowFolderMNC";
    } else if (currentAction == "ShowFolderMNCUpdate") {
        onUpdateFileButtonClicked();
        ui.copyFileButton->setDisabled(false);
        qDebug() << "Action for ShowFolderMNCUpdate";
    } else {
        qDebug() << "No action set!";
    }
}

///////////////////////////////////////////////////////////
void ShowFolders::ShowFolderMNCUpdate(){

    ui.copyFileButton->setDisabled(true);
    ui.updateFileButton->setDisabled(true);
    QString sourceFolderPath = "./UpdateMNC_SCADA";

    // Step 1: Display folder contents in a checklist
    QDir sourceDir(sourceFolderPath);
    QStringList folders = sourceDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

    if (folders.isEmpty()) {
        m_showMessages->showMessage("The source folder is empty!", QMessageBox::Critical, QMessageBox::Ok);
        return;
    }
    ui.FileShowList->clear();
    for (const QString &folder : folders) {
        QListWidgetItem *item = new QListWidgetItem(folder, ui.FileShowList);
    }
    QListWidgetItem *bakItem = new QListWidgetItem(ui.FileShowList);
    bakItem->setSizeHint(QSize(150, 45));
    auto *button = new QPushButton("Back", ui.FileShowList);
    button->setStyleSheet(StyleSheetManager::buttonStyle());
    ui.FileShowList->setItemWidget(bakItem, button);
    connect(button, &QPushButton::clicked, this, &ShowFolders::onItemClicked);

    currentAction = "ShowFolderMNCUpdate";

}
///////////////////////////////////////////////////////////////////
void ShowFolders::onCopyFileButtonClicked()
{
    QString sourceFolderPath = "./MNC_SCADA";

    // Step 1: Display folder contents in the list
    QDir sourceDir(sourceFolderPath);
    QStringList folders = sourceDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

    // Allow single selection
    ui.FileShowList->setSelectionMode(QAbstractItemView::SingleSelection);
    QListWidgetItem *selectedItem = ui.FileShowList->currentItem();


    QStringList selectedFolders;

    // Step 2: Connect itemClicked to track selected folder
    connect(ui.FileShowList, &QListWidget::itemClicked, this, [this](QListWidgetItem *clickedItem) {
        qDebug ()<<"Item clicked :"<< clickedItem->text();

        // Deselect all other items
        for (int i = 0; i < ui.FileShowList->count(); ++i) {
            QListWidgetItem *item = ui.FileShowList->item(i);
            if (item != clickedItem) {
                item->setSelected(false); // Deselect other items
            }
        }
    });

    // Step 3: Get the selected folder after user makes a selection
    if (selectedItem) {
        selectedFolders.append(selectedItem->text());
        qDebug() << selectedFolders;
    }

    // Step 4: Ensure at least one folder is selected
    if (selectedFolders.isEmpty()) {
        m_showMessages->showMessage(
                    tr("No folders selected for copying!"),
                    QMessageBox::Critical,
                    QMessageBox::Ok
                    );
        return;
    }
    qDebug() << "Selected folder for copying: " << selectedFolders;


    // Step 5: Ask the user for a destination folder
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

    // Step 6: Copy selected folders
    for (const QString &folder : selectedFolders) {
        QString sourcePath = sourceFolderPath + "/" + folder;
        QString destinationPath = destinationFolderPath + "/" + folder;

        QDir dir(destinationPath);
        if (!dir.exists()) {
            dir.mkpath(".");  // Create the folder if it doesn't exist
            copyPath(sourcePath, destinationPath, ui.progressBar);  // Copy files and folders
            m_showMessages->showMessage(
                        QString("The folder '%1' has been copied successfully!").arg(folder),
                        QMessageBox::Information,
                        QMessageBox::Ok
                        );

        }
        else {
            QMessageBox::StandardButton reply = m_showMessages->showMessageWithResponse(
                        tr("The folder '%1' already exists in the destination. Do you want to update it?").arg(folder),
                        QMessageBox::Question,
                        QMessageBox::Yes | QMessageBox::No
                        );

            if (reply == QMessageBox::Yes) {
                QDir srcDir(sourcePath);
                int totalItem = srcDir.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot).size();
                int counter = 0;
                compareAndMergeFiles(sourcePath, destinationPath, ui.progressBar, counter, totalItem);

                m_showMessages->showMessage(
                            tr("The folder '%1' has been updated successfully!").arg(folder),
                            QMessageBox::Information,
                            QMessageBox::Ok
                            );
            } else {
                return;
            }


        }
    }

    // save destinationFolder
    QString iniFilePath = QCoreApplication::applicationDirPath() + "/config.ini";

    QSettings settings(iniFilePath, QSettings::IniFormat);

    settings.setValue("Settings/destinationFolder", destinationFolderPath);
    settings.sync();

    qDebug() << "destinationFolder stored in ini file: " << iniFilePath;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ShowFolders::onUpdateFileButtonClicked(){
    QString sourceFolderPath = "./UpdateMNC_SCADA";

    // Step 1: Display folder contents in the list
    QDir sourceDir(sourceFolderPath);
    QStringList folders = sourceDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

    // Allow single selection
    ui.FileShowList->setSelectionMode(QAbstractItemView::SingleSelection);
    QListWidgetItem *selectedItem = ui.FileShowList->currentItem();


    QStringList selectedFolders;

    // Step 2: Connect itemClicked to track selected folder
    connect(ui.FileShowList, &QListWidget::itemClicked, this, [this](QListWidgetItem *clickedItem) {
        // Deselect all other items
        for (int i = 0; i < ui.FileShowList->count(); ++i) {
            QListWidgetItem *item = ui.FileShowList->item(i);
            if (item != clickedItem) {
                item->setSelected(false); // Deselect other items
            }
        }
    });

    // Step 3: Get the selected folder after user makes a selection
    if (selectedItem) {
        selectedFolders.append(selectedItem->text());
        qDebug() << selectedFolders;
    }

    // Step 4: Ensure at least one folder is selected
    if (selectedFolders.isEmpty()) {
        m_showMessages->showMessage(
                    tr("No folders selected for copying!"),
                    QMessageBox::Critical,
                    QMessageBox::Ok
                    );
        return;
    }

    // Step 5: Ask the user for a destination folder
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


    // Step 6: Copy selected folders
    for (const QString &folder : selectedFolders) {
        QString sourcePath = sourceFolderPath + "/" + folder;
        QString destinationPath = destinationFolderPath + "/" + folder;


        QDir dir(destinationPath);
        if (!dir.exists()) {
            m_showMessages->showMessage(
                        QString("The folder '%1' does not exist in the destination. Update cannot proceed!").arg(folder),
                        QMessageBox::Critical,
                        QMessageBox::Ok
                        );
            continue;

        }
        else {

            QDir srcDir(sourcePath);
            int totalItem = srcDir.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot).size();
            int counter = 0;
            compareAndMergeFiles(sourcePath, destinationPath, ui.progressBar, counter, totalItem);

            m_showMessages->showMessage(
                        tr("The folder '%1' has been updated successfully!").arg(folder),
                        QMessageBox::Information,
                        QMessageBox::Ok
                        );
        }
    }

    // save destinationFolder
    QString iniFilePath = QCoreApplication::applicationDirPath() + "/config.ini";

    QSettings settings(iniFilePath, QSettings::IniFormat);

    settings.setValue("Settings/destinationFolder", destinationFolderPath);
    settings.sync();

    qDebug() << "destinationFolder stored in ini file: " << iniFilePath;

}
///////////////////////////////////////////////////////////////////////////////////////////////
void ShowFolders::compareAndMergeFiles(QString src, QString dst , QProgressBar *progressBar , int &counter, int totalItem)
{


    QString direct = src;
    QDir dir(direct);
    QStringList sourcefilesName;

    for (const QFileInfo &file : dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        sourcefilesName.append(file.fileName());
    }

    QDir mydir(dst);
    QStringList DestinationUpdateFile;

    for (const QFileInfo &file : mydir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        DestinationUpdateFile.append(file.fileName());
    }
    for (int i = 0; i < sourcefilesName.size(); i++)
    {
        if (DestinationUpdateFile.contains(sourcefilesName[i]))
        {
            QString folderToDelete = dst + "/" + sourcefilesName[i];
            QDir mydir(folderToDelete);
            if (mydir.exists() && mydir.removeRecursively()) {
                qDebug() << "Folder deleted: " << dst;

            } else {
                qDebug() << "Failed to delete or folder does not exist: " << folderToDelete;
            }
        }
    }

    copyPath(direct,dst,progressBar);

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ShowFolders::copyPath(QString src, QString dst , QProgressBar *progressBar)
{

    QDir dir(src);
    if (! dir.exists())
        return;

    int totalItem = dir.entryList(QDir::Files |QDir::Dirs | QDir::NoDotAndDotDot).size();
    int counter = 0 ;

    foreach (QString d, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        QString dst_path = dst + QDir::separator() + d;
        dir.mkpath(dst_path);
        copyPath(src+ QDir::separator() + d, dst_path , progressBar);
        counter++;
        if (progressBar) progressBar->setValue((counter*100)/totalItem);
    }

    foreach (QString f, dir.entryList(QDir::Files)) {
        QFile::copy(src + QDir::separator() + f, dst + QDir::separator() + f);
        counter++;
        if (progressBar) progressBar->setValue((counter*100)/totalItem);
    }
}
