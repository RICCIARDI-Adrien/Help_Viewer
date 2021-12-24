/** @file Main.cpp
 * Program entry point and main loop.
 * @author Adrien RICCIARDI
 */
#include <MainWindow.hpp>
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    // TODO set up translations

    // Check arguments
    if (argc < 4)
    {
        // This error string is displayed only for debugging purpose, so no need to translate it
        QMessageBox::critical(nullptr, "Bad command line arguments",
            "One or more command line arguments are missing.\n\n"
            "The first argument must be the base path of the documents to display (this is the relative path for the document internal hyperlinks). This path starts from the root of the content resource file.\n\n"
            "The second argument is the name of the document to consider as \"home\", its path is relative to the base path.\n\n"
            "The third argument is the name of the document to display, its path is relative to the base path.",
            QMessageBox::Ok);

        return application.exec();
    }

    // Create and configure application main window
    MainWindow window;
    window.setContentSettings(argv[1], argv[2], argv[3]);
    window.showMaximized();

    return application.exec();
}
