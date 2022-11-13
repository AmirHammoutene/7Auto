#ifndef AUTODRIVEPROCESSMANAGER_H
#define AUTODRIVEPROCESSMANAGER_H

#include <QObject>
#include <QThread>
#include "autodriveprocess.h"
#include "autotools.h"

class AutodriveProcessManager : public QObject
{
    Q_OBJECT
public:
    explicit AutodriveProcessManager(QObject *parent = nullptr);
    bool configure(QString ingameModForward, QString ingameKeyForward, QString ingameModTurbo, QString ingameKeyTurbo,
                   quint32 ingameModForwardNative, quint32 ingameKeyForwardNative, quint32 ingameModTurboNative, quint32 ingameKeyTurboNative,
                   bool ingameKeyForwardIsMouse, bool ingameKeyTurboIsMouse);
    void run();
    void stop();
private:
    quint32 m_ingameModForwardNative;
    quint32 m_ingameKeyForwardNative;
    quint32 m_ingameModTurboNative;
    quint32 m_ingameKeyTurboNative;
    bool m_ingameKeyForwardIsMouse;
    bool m_ingameKeyTurboIsMouse;

    QThread *m_thread;
    AutodriveProcess * m_process;
    AutoTools *m_tools;

};

#endif // AUTODRIVEPROCESSMANAGER_H
