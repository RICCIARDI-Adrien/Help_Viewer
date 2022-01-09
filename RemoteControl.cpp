/** @file RemoteControl.cpp
 * See RemoteControl.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <QFile>
#include <QMessageBox>
#include <RemoteControl.hpp>
#ifdef Q_OS_UNIX
    #include <sys/select.h>
    #include <unistd.h>
#elif defined(Q_OS_WINDOWS)
    #include <windows.h>
#endif

RemoteControl::RemoteControl()
    : QThread()
{}

RemoteControl::~RemoteControl()
{
    this->requestInterruption();
    this->wait();
}

void RemoteControl::run()
{
    char stringCommand[1024];

    #ifdef Q_OS_UNIX
        int fileDescriptor = fileno(stdin), result;
        fd_set readFileDescriptorsSet;
        struct timeval timeout;
        ssize_t readBytesCount;

        // Wait for an URL to be received on stdin
        while (!isInterruptionRequested())
        {
            // Fill the set with the stdin file descriptor
            FD_ZERO(&readFileDescriptorsSet);
            FD_SET(fileDescriptor, &readFileDescriptorsSet);

            // Set the timeout to 250 milliseconds, so the thread is not too slow to quit for an human user
            timeout.tv_sec = 0;
            timeout.tv_usec = 250000;

            // Check whether some data are available on stdin
            result = select(fileDescriptor + 1, &readFileDescriptorsSet, nullptr, nullptr, &timeout);
            if (result == -1) return; // TODO : handle better an error
            else if (result == 0) continue; // No data is available, wait for it another time

            // Data is available
            readBytesCount = read(fileDescriptor, stringCommand, sizeof(stringCommand));
            if (readBytesCount > 0) _sendCommand(stringCommand, readBytesCount);
        }
    #elif defined(Q_OS_WINDOWS)
        // Retrieve stdin handle, it changes on each program launch
        HANDLE fileHandle = GetStdHandle(STD_INPUT_HANDLE);
        if (fileHandle == INVALID_HANDLE_VALUE) return;

        DWORD readBytesCount = 0;
        BOOL isSuccess;
        while (!isInterruptionRequested())
        {
            // Check whether data is available in the console input buffer without blocking
            isSuccess = PeekNamedPipe(fileHandle, nullptr, 0, nullptr, &readBytesCount, nullptr);
            if (!isSuccess || (readBytesCount == 0))
            {
                this->msleep(250);
                continue;
            }

            // Data is available
            if (!ReadFile(fileHandle, stringCommand, sizeof(stringCommand) - 1, &readBytesCount, nullptr)) return;
            if (readBytesCount > 0) _sendCommand(stringCommand, readBytesCount);
        }
    #else
        #error Unsupported architecture.
    #endif
}

void RemoteControl::_sendCommand(char *pointerStringCommand, int length)
{
    // Make sure the provided length is valid
    if (length <= 0) return;

    // Make sure the string is terminated (this also removes the trailing "\n" if any)
    pointerStringCommand[length - 1] = 0;

    emit commandReceived(pointerStringCommand);
}
