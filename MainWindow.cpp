/** @file MainWindow.cpp
 * See MainWindow.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <Configuration.hpp>
#include <MainWindow.hpp>
#include <QMessageBox>
#include <QMenuBar>
#include <ui_MainWindow.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create a menu bar on macOS filled with the mandatory menu entries, this also makes the Qt-provided translations work for this menu
    #ifdef Q_OS_MACOS
        // Create the menu bar
        QMenuBar *pointerMenuBar = new QMenuBar(this);

        // Create the necessary menus
        QMenu *pointerMenuFile = pointerMenuBar->addMenu("File"); // No need to translate the menu name as this menu won't be displayed
        QMenu *pointerMenuHelp = pointerMenuBar->addMenu("Help"); // No need to translate the menu name as this menu won't be displayed

        // Create the "Quit" entry in the "File" menu
        QAction *pointerActionQuit = new QAction("Quit", pointerMenuBar); // The action name will be automatically translated by Qt-provided translations because it is identified as the default "Quit" entry
        pointerActionQuit->setMenuRole(QAction::QuitRole);
        pointerMenuFile->addAction(pointerActionQuit);
        connect(pointerActionQuit, &QAction::triggered, this, &QApplication::quit);

        // Create the "About" entry in the "Help" menu
        QAction *pointerActionAbout = new QAction("About", pointerMenuBar); // The action name will be automatically translated by Qt-provided translations because it is identified as the default "About" entry
        pointerActionAbout->setMenuRole(QAction::AboutRole);
        pointerMenuHelp->addAction(pointerActionAbout);
        connect(pointerActionAbout, &QAction::triggered, this, &MainWindow::_slotPushButtonAboutClicked);
    #endif

    // Set a custom window title if specified on build command line
    if (strlen(HELP_VIEWER_PROGRAM_NAME) > 0) this->setWindowTitle(tr("%1 - Help").arg(HELP_VIEWER_PROGRAM_NAME));
    else this->setWindowTitle(tr("Help"));

    // Connect slots
    connect(ui->pushButtonPrevious, &QPushButton::clicked, ui->textBrowser, &QTextBrowser::backward);
    connect(ui->pushButtonNext, &QPushButton::clicked, ui->textBrowser, &QTextBrowser::forward);
    connect(ui->pushButtonHome, &QPushButton::clicked, ui->textBrowser, &QTextBrowser::home);
    connect(ui->pushButtonAbout, &QPushButton::clicked, this, &MainWindow::_slotPushButtonAboutClicked);
    connect(ui->pushButtonQuit, &QPushButton::clicked, this, &QApplication::quit);
    connect(ui->textBrowser, &QTextBrowser::backwardAvailable, this, &MainWindow::_slotTextBrowserBackwardAvailable);
    connect(ui->textBrowser, &QTextBrowser::forwardAvailable, this, &MainWindow::_slotTextBrowserForwardAvailable);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setContentSettings(QString basePath, QString homeDocumentName, QString displayedDocumentName)
{
    QStringList searchPaths;
    searchPaths.append(":" + basePath);
    ui->textBrowser->setSearchPaths(searchPaths);

    ui->textBrowser->setSource(QUrl(homeDocumentName)); // Set the home document as first, so it is considered the home by the text browser
    ui->textBrowser->setSource(QUrl(displayedDocumentName));
}

void MainWindow::displayDocument(QString documentName)
{
    ui->textBrowser->setSource(QUrl(documentName));

    // Put the application window on top
    this->raise();
    this->activateWindow();
}

void MainWindow::_slotTextBrowserBackwardAvailable(bool isAvailable)
{
    ui->pushButtonPrevious->setEnabled(isAvailable);
}

void MainWindow::_slotTextBrowserForwardAvailable(bool isAvailable)
{
    ui->pushButtonNext->setEnabled(isAvailable);
}

void MainWindow::_slotPushButtonAboutClicked(bool)
{
    QString currentYear = QString(__DATE__).mid(7, 4);
    QMessageBox::information(this, tr("About"), tr("(C) 2021-%1 Adrien RICCIARDI<br /><br />Build date: %2 %3<br /><br />This application is using Qt framework under <a href=\"https://www.gnu.org/licenses/lgpl-3.0-standalone.html\">LGPLv3 license</a>.").arg(currentYear, __DATE__, __TIME__), QMessageBox::Ok);
}
