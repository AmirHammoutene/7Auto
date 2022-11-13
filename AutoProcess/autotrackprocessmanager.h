#ifndef AUTOTRACKPROCESSMANAGER_H
#define AUTOTRACKPROCESSMANAGER_H

#include <QObject>
#include <QThread>
#include "autotrackprocess.h"
#include "autotools.h"

class AutotrackProcessManager : public QObject
{
    Q_OBJECT
public:
    explicit AutotrackProcessManager(QObject *parent = nullptr);
    bool configure(QString ingameModForward, QString ingameKeyForward, QString ingameModRun, QString ingameKeyRun,
                   QString ingameModCrouch, QString ingameKeyCrouch,
                   quint32 ingameModForwardNative, quint32 ingameKeyForwardNative, quint32 ingameModRunNative, quint32 ingameKeyRunNative,
                   quint32 ingameModCrouchNative, quint32 ingameKeyCrouchNative,
                   bool ingameKeyForwardIsMouse, bool ingameKeyRunIsMouse,bool ingameKeyCrouchIsMouse,
                   double timeRun, double timeCrouch);
    void run();
    void stop();
private:
    quint32 m_ingameModForwardNative;
    quint32 m_ingameKeyForwardNative;
    quint32 m_ingameModRunNative;
    quint32 m_ingameKeyRunNative;
    quint32 m_ingameModCrouchNative;
    quint32 m_ingameKeyCrouchNative;
    bool m_ingameKeyForwardIsMouse;
    bool m_ingameKeyRunIsMouse;
    bool m_ingameKeyCrouchIsMouse;
    QThread *m_thread;
    AutotrackProcess * m_process;
    AutoTools *m_tools;
    quint32 m_limitTimeRun;
    quint32 m_limitTimeCrouch;
};

#endif // AUTOTRACKPROCESSMANAGER_H
