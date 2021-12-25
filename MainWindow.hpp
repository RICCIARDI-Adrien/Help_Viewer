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

    /** Configure the text browser so it can display the initial document and is able to follow hyperlinks.
     * @param basePath The "website" root directory, each hyperlink relative URL is concatened to this base path.
     * @param homeDocumentName The document to display when the user clicks the "home" button.
     * @param displayedDocumentName The document to display on the text browser.
     */
    void setContentSettings(QString basePath, QString homeDocumentName, QString displayedDocumentName);

    /** Display the specified document.
     * @param documentName The document to display file name and extension. Its path is relative to the base path provided in setContentSettings().
     */
    void displayDocument(QString documentName);

private:
    Ui::MainWindow *ui;

private slots:
    /** Called when the user is allowed to go backward. */
    void _slotTextBrowserBackwardAvailable(bool isAvailable);
    /** Called when the user is allowed to go forward. */
    void _slotTextBrowserForwardAvailable(bool isAvailable);
};
#endif // MAINWINDOW_H
