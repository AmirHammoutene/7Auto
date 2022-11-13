#ifndef AUTOTRACKPROCESS_H
#define AUTOTRACKPROCESS_H

#include <QObject>
#include "autotools.h"
#include <QElapsedTimer>

class AutotrackProcess : public QObject
{
    Q_OBJECT
public:
    explicit AutotrackProcess(QObject *parent = nullptr);
    quint32 m_ingameModForwardNative;
    quint32 m_ingameKeyForwardNative;
    quint32 m_ingameModRunNative;
    quint32 m_ingameKeyRunNative;
    quint32 m_ingameModCrouchNative;
    quint32 m_ingameKeyCrouchNative;
    bool m_ingameKeyForwardIsMouse;
    bool m_ingameKeyRunIsMouse;
    bool m_ingameKeyCrouchIsMouse;
    quint32 m_limitTimeRun;
    quint32 m_limitTimeCrouch;
    AutoTools *m_tools;

    void PhaseOne();
    void PhaseTwo();
public slots:
    void process();
    void AllPhases();
private:
    bool lastActionPhaseOne;
    bool lastActionPhaseTwo;
    QElapsedTimer m_phaseOneTimer;
    QElapsedTimer m_phaseTwoTimer;
};

#endif // AUTOTRACKPROCESS_H
