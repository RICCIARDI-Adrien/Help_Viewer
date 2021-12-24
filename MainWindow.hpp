/** @file MainWindow.hpp
 * Display the help content and the program main controls.
 * @author Adrien RICCIARDI
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    /** Called when the user is allowed to go forward. */
    void _slotTextBrowserBackwardAvailable(bool isAvailable);
    /** Called when the user is allowed to go forward. */
    void _slotTextBrowserForwardAvailable(bool isAvailable);
};
#endif // MAINWINDOW_H
