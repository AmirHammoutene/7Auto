#ifndef AUTOMINEPROCESSMANAGER_H
#define AUTOMINEPROCESSMANAGER_H

#include <QObject>
#include <QThread>
#include "automineprocess.h"
#include "autotools.h"

class AutomineProcessManager : public QObject
{
    Q_OBJECT
public:
    explicit AutomineProcessManager(QObject *parent = nullptr);
    bool configure(QString ingameModForward, QString ingameKeyForward, QString ingameModPrimaryAct, QString ingameKeyPrimaryAct,
                   QString ingameModSecondaryAct, QString ingameKeySecondaryAct,
                   quint32 ingameModForwardNative, quint32 ingameKeyForwardNative, quint32 ingameModPrimaryActNative, quint32 ingameKeyPrimaryActNative,
                   quint32 ingameModSecondaryActNative, quint32 ingameKeySecondaryActNative,
                   bool ingameKeyForwardIsMouse, bool ingameKeyPrimaryActIsMouse, bool ingameKeySecondaryActIsMouse,
                   double timeHit, double timePause, double delayWalk, double timeWalk, double simpleHitDur, double powerHitDur,
                   QString hitSequence);
    void run();
    void stop();
private:
    quint32 m_ingameModForwardNative;
    quint32 m_ingameKeyForwardNative;
    quint32 m_ingameModPrimaryActNative;
    quint32 m_ingameKeyPrimaryActNative;
    quint32 m_ingameModSecondaryActNative;
    quint32 m_ingameKeySecondaryActNative;
    bool m_ingameKeyForwardIsMouse;
    bool m_ingameKeyPrimaryActIsMouse;
    bool m_ingameKeySecondaryActIsMouse;
    QVector<bool> m_hitSequence;
    QThread *m_thread;
    AutomineProcess * m_process;
    AutoTools *m_tools;
    quint32 m_limitTimeHit;
    quint32 m_limitTimePause;
    quint32 m_walkDelay;
    quint32 m_limitTimeWalk;
    quint32 m_durationPrimaryAct;
    quint32 m_durationSecondaryAct;

};

#endif // AUTOMINEPROCESSMANAGER_H
