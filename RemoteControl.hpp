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

protected:
    void run();

signals:
    /** Emit this signal when a command has been fully received. */
    void commandReceived(QString command);
};

#endif // REMOTECONTROL_HPP
