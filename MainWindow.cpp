/** @file MainWindow.cpp
 * See MainWindow.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <MainWindow.hpp>
#include <ui_MainWindow.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set a custom window title if specified on build command line
    if (strlen(HELP_VIEWER_PROGRAM_NAME) > 0) this->setWindowTitle(tr("%1 - Help").arg(HELP_VIEWER_PROGRAM_NAME));
    else this->setWindowTitle(tr("Help"));

    // Connect slots
    connect(ui->pushButtonPrevious, &QPushButton::clicked, ui->textBrowser, &QTextBrowser::backward);
    connect(ui->pushButtonNext, &QPushButton::clicked, ui->textBrowser, &QTextBrowser::forward);
    connect(ui->pushButtonHome, &QPushButton::clicked, ui->textBrowser, &QTextBrowser::home);
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
}

void MainWindow::_slotTextBrowserBackwardAvailable(bool isAvailable)
{
    ui->pushButtonPrevious->setEnabled(isAvailable);
}

void MainWindow::_slotTextBrowserForwardAvailable(bool isAvailable)
{
    ui->pushButtonNext->setEnabled(isAvailable);
}
