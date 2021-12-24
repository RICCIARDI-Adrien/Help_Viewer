/** @file Main.cpp
 * Program entry point and main loop.
 * @author Adrien RICCIARDI
 */
#include <MainWindow.hpp>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    // Create and display application main window
    MainWindow window;
    window.showMaximized();

    return application.exec();
}
