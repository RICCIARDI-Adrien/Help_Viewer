/** @file RemoteControl.hpp
 * Listen on stdin for a command.
 * @author Adrien RICCIARDI
 */
#ifndef REMOTECONTROL_HPP
#define REMOTECONTROL_HPP

#include <QThread>

class RemoteControl: public QThread
{
    Q_OBJECT

public:
    RemoteControl();
    virtual ~RemoteControl();

protected:
    void run();

private:
    /** Send the received command to the event loop.
     * @param pointerStringCommand The command string as received from stdin.
     * @param length The command string length in bytes.
     */
    void _sendCommand(char *pointerStringCommand, int length);

signals:
    /** Emit this signal when a command has been fully received. */
    void commandReceived(QString command);
};

#endif // REMOTECONTROL_HPP
