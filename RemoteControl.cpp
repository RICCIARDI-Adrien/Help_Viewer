/** @file RemoteControl.cpp
 * See RemoteControl.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <QFile>
#include <QMessageBox>
#include <RemoteControl.hpp>

RemoteControl::RemoteControl()
    : QThread()
{}

void RemoteControl::run()
{
    // Try to open stdin to read commands from
    QFile controlFile;
    if (!controlFile.open(stdin, QFile::ReadOnly))
    {
        // This error should never happen, so no need to translate the error message
        QMessageBox::critical(nullptr, "Remote control error", "Could not open stdin for reading remote control commands.\nDisabling remote control feature.");
        return;
    }

    // Wait for an URL to be received on stdin
    char stringCommand[1024];
    qint64 readBytesCount;
    while (1)
    {
        // Try to get the URL to display
        readBytesCount = controlFile.readLine(stringCommand, sizeof(stringCommand));
        if (readBytesCount > 0)
        {
            // Remove the trailing "\n" if any
            if (stringCommand[readBytesCount - 1] == '\n') stringCommand[readBytesCount - 1] = 0;
            emit commandReceived(stringCommand);
        }
    }
}
