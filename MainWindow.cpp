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

void MainWindow::_slotTextBrowserBackwardAvailable(bool isAvailable)
{
    ui->pushButtonPrevious->setEnabled(isAvailable);
}

void MainWindow::_slotTextBrowserForwardAvailable(bool isAvailable)
{
    ui->pushButtonNext->setEnabled(isAvailable);
}