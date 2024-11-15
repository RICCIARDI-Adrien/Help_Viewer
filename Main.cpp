/** @file Main.cpp
 * Program entry point and main loop.
 * @author Adrien RICCIARDI
 */
#include <MainWindow.hpp>
#include <RemoteControl.hpp>
#include <QApplication>
#include <QLibraryInfo>
#include <QMessageBox>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    // Load Qt-provided translations (used for instance in default dialogs)
    QTranslator qtTranslator;
    bool isLocaleLoaded = qtTranslator.load(QLocale::system(), "qt", "_", QLibraryInfo::path(QLibraryInfo::TranslationsPath));
    if (isLocaleLoaded) application.installTranslator(&qtTranslator);

    // Select the right application translation according to system language
    QTranslator translator;
    // Retrieve the current language code of the system
    const QString languageCode = QLocale::languageToCode(QLocale::system().language());
    // Load the corresponding translation
    isLocaleLoaded = translator.load(":/Translations/" + languageCode + ".qm");
    if (isLocaleLoaded) application.installTranslator(&translator);

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

        // The preceding QMessageBox runs its own event loop, so there is no need to call application.exec()
        return 0;
    }

    // Create and configure application main window
    MainWindow mainWindow;
    mainWindow.setContentSettings(argv[1], argv[2], argv[3]);
    mainWindow.showMaximized();
    // Set task bar icon on Linux
    #ifdef Q_OS_LINUX
        mainWindow.setWindowIcon(QIcon(":/Icon/Icon.svg"));
    #endif

    // Create a thread that will listen to commands on process stdin
    RemoteControl remoteControlThread;
    remoteControlThread.start();
    QObject::connect(&remoteControlThread, &RemoteControl::commandReceived, &mainWindow, &MainWindow::displayDocument);

    return application.exec();
}
