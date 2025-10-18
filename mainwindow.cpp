#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "TreeWidget.h"
#include "ui_TreeWidget.h"
#include "StyleSheetManager.h"
#include <QPointer>
#include <QPainter>
#include <QImage>
#include <QPixmap>
#include <QPalette>
#include <QGraphicsOpacityEffect>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->clear();
    ui->messageLabel2->hide();

    setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint | Qt::WindowTitleHint);
    setFixedSize(761, 572);

    setWidgetOpacity(ui->messageLabel, 0.8);
    setWidgetOpacity(ui->messageLabel2, 0.8);


    QImage image(":/new/prefix1/moojniro.png");

    QImage imageWithOpacity = image;
    QPainter painter(&imageWithOpacity);
    painter.setOpacity(0.1);
    painter.drawImage(0, 0, image);
    painter.end();

    QPixmap background = QPixmap::fromImage(imageWithOpacity);

    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(background));
    this->setPalette(palette);
    this->setAutoFillBackground(true);

    ui->messageLabel2->setStyleSheet(StyleSheetManager::LabelStyle2());
    ui->messageLabel->setStyleSheet(StyleSheetManager::LabelStyle());
    ui->messageLabel->setText( "Select Installation Mode:\n\n"
                               "- HMI Mode: For users who need a ready-to-use interface for monitoring and control.\n"
                               "- Designer Mode: For developers who need advanced tools to customize and design interfaces.\n\n"
                               "Your choice will determine the features available after installation."
                               );
    setupComboBox();

    ui->cancelButton->setStyleSheet(StyleSheetManager::buttonStyle());

    moduleManager = new ModuleManager(this);
    treeWidget = new TreeWidget(this);
    treeWidget->hide();

    connect(this, &MainWindow::modulesListUpdated, treeWidget, &TreeWidget::updateTreeWidgetFromMainWindow);

    connect(treeWidget, &TreeWidget::itemSelected, this, &MainWindow::receiveSelectedItem);

    connect(this, &MainWindow::activeItemChanged, moduleManager, &ModuleManager::handleActiveItem);

    connect(ui->cancelButton, &QPushButton::clicked, this, &MainWindow::onCancelButtonClicked);

    this->setStyleSheet(StyleSheetManager::mainWindow());


}

MainWindow::~MainWindow()
{
    delete ui;
}

//////////////////////////////////////////////////////////////
void MainWindow::setWidgetOpacity(QWidget *widget, qreal opacity)
{
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(widget);
    effect->setOpacity(opacity);
    widget->setGraphicsEffect(effect);
}
//////////////////////////////////////////////////////////////
void MainWindow::setupComboBox() {

    ui->modeComboBox->addItem("Selecte Mode");
    ui->modeComboBox->addItem("HMI Mode");
    ui->modeComboBox->addItem("Designer Mode");

    connect(ui->modeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onComboBoxChanged);

    ui->modeComboBox->setStyleSheet(StyleSheetManager::modeComboBoxStyle());
}
//////////////////////////////////////////////////////////////
void MainWindow::onComboBoxChanged(int index) {
    QString selectedMode = ui->modeComboBox->currentText();
    qDebug() << "ComboBox Changed - Index:" << index << ", Selected Mode:" << selectedMode;

    QTimer::singleShot(50, this, [this]() {
        ui->modeComboBox->hide();
        ui->modeComboBox->update();
        ui->modeComboBox->repaint();
        ui->messageLabel->hide();

    });


    if (selectedMode == "Designer Mode") {
        qDebug() << "Designer Mode Selected!";
    } else if (selectedMode == "HMI Mode") {
        qDebug() << "HMI Mode Selected!";
    }

    if (moduleManager) {
        qDebug() << "Sending selected mode to moduleManager: " << selectedMode;
        emit modulesListUpdated(moduleManager->receiveSelectedMode(selectedMode));

        ;
    } else {
        qCritical() << "Error: moduleManager is nullptr!";
    }

    if (treeWidget) {
        qDebug() << "Adding treeWidget to mainGridLayout...";
        QLayout *treeLayout = treeWidget->ui->treeLayout;
        ui->TreewidgetLayout->addLayout(treeLayout, 0, 0);
        ui->messageLabel->clear();
        treeWidget->show();
    } else {
        qCritical() << "Error: treeWidget is nullptr!";
    }
}

////////////////////////////////////////////////////////////////////
void MainWindow::receiveSelectedItem(QString itemText)
{
    qDebug() << "Received item from TreeWidget:" << itemText;
    activeItemText = itemText;
    emit activeItemChanged(itemText);
    updateCancelButtonText(itemText);

}
////////////////////////////////////////////////////////////////////
void MainWindow::updateCancelButtonText(const QString &itemText)
{
    if (itemText == "Finish") {
        ui->cancelButton->setText("Finish");
    } else {
        ui->cancelButton->setText("Cancel");
    }

    if (itemText == "Welcome") {
        ui->messageLabel2->show();
        ui->messageLabel2->setText(
                    "Welcome to the Installation Wizard!\n\n"
                    "Please follow the instructions carefully to ensure a successful setup.\n\n"
                    "Click 'Next' to begin."
                    );
    }
    else if (itemText == "Finish") {
        ui->messageLabel2->show();
        ui->messageLabel2->setText(
                    "Installation Completed Successfully!\n\n"
                    "You can now start using the software.\n"
                    "Click 'Finish' to exit."
                    );
    }
    else {
        ui->messageLabel2->hide();
    }


}

//////////////////////////////////////////////////////////////////////
void MainWindow::onCancelButtonClicked()
{
    QMessageBox::StandardButton reply = m_showMessages->showMessageWithResponse(
                tr("Are you sure you want to exit?"),
                QMessageBox::Question,
                QMessageBox::Yes | QMessageBox::No
                );

    if (reply == QMessageBox::Yes) {
        QApplication::quit();
    }
    return;

}

/////////////////////////////////////////////////////////////////////////
//void MainWindow::setupCustomTitleBar() {

//    this->setWindowFlags(Qt::FramelessWindowHint);

//    QWidget* titleBarWidget = new QWidget(this);
//    titleBarWidget->setStyleSheet("background-color: #white; padding: 5px;");
//    titleBarWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

//    QLabel* iconLabel = new QLabel(titleBarWidget);
//    QPixmap iconPixmap(QCoreApplication::applicationDirPath() + "/Icon.png");
//    iconLabel->setPixmap(iconPixmap.scaled(30, 30, Qt::KeepAspectRatio));

//    QLabel* titleLabel = new QLabel(titleBarWidget);
//    titleLabel->setText("<span style='color:blue;'>Modje</span> <span style='color:yellow;'>Niro</span>");
//    titleLabel->setAlignment(Qt::AlignCenter);
//    titleLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: white;");

//    QPushButton* closeButton = new QPushButton(titleBarWidget);
//    closeButton->setText("✖");
//    closeButton->setFixedSize(30, 30);
//    closeButton->setStyleSheet(
//                "QPushButton {"
//                "    background-color: yellow; "
//                "    color: blue; "
//                "    font-size: 16px; "
//                "    border-radius: 5px; "
//                "}"
//                "QPushButton:hover {"
//                "    background-color: gold; "
//                "}"
//                );

//    connect(closeButton, &QPushButton::clicked, this, &MainWindow::close);

//    QHBoxLayout* titleLayout = new QHBoxLayout(titleBarWidget);
//    titleLayout->addWidget(iconLabel);
//    titleLayout->addWidget(titleLabel);
//    titleLayout->addWidget(closeButton);
//    titleLayout->setContentsMargins(10, 2, 10, 2);
//    titleLayout->setSpacing(10);

//    QVBoxLayout* mainLayout = new QVBoxLayout(this);
//    mainLayout->addWidget(titleBarWidget);
//    mainLayout->addWidget(ui->centralwidget);
//    mainLayout->setContentsMargins(0, 0, 0, 0);
//    setLayout(mainLayout);

//    QWidget* centralWidget = new QWidget(this);
//    centralWidget->setLayout(mainLayout);
//    setCentralWidget(centralWidget);
//}


