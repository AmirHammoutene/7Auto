#ifndef AUTORUNPROCESSMANAGER_H
#define AUTORUNPROCESSMANAGER_H

#include <QObject>
#include <QThread>
#include "autorunprocess.h"
#include "autotools.h"

class AutorunProcessManager : public QObject
{
    Q_OBJECT
public:
    explicit AutorunProcessManager(QObject *parent = nullptr);
    bool configure(QString ingameModForward, QString ingameKeyForward, QString ingameModRun, QString ingameKeyRun,
                   quint32 ingameModForwardNative, quint32 ingameKeyForwardNative, quint32 ingameModRunNative, quint32 ingameKeyRunNative,
                   bool ingameKeyForwardIsMouse, bool ingameKeyRunIsMouse,
                   double timeRun, double timeWalk);
    void run();
    void stop();
private:
    quint32 m_ingameModForwardNative;
    quint32 m_ingameKeyForwardNative;
    quint32 m_ingameModRunNative;
    quint32 m_ingameKeyRunNative;
    bool m_ingameKeyForwardIsMouse;
    bool m_ingameKeyRunIsMouse;
    QThread *m_thread;
    AutorunProcess * m_process;
    AutoTools *m_tools;
    quint32 m_limitTimeRun;
    quint32 m_limitTimeWalk;
};

#endif // AUTORUNPROCESSMANAGER_H
