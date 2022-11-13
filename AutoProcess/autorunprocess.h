#ifndef AUTORUNPROCESS_H
#define AUTORUNPROCESS_H

#include <QObject>
#include "autotools.h"
#include <QElapsedTimer>

class AutorunProcess : public QObject
{
    Q_OBJECT
public:
    explicit AutorunProcess(QObject *parent = nullptr);
    quint32 m_ingameModForwardNative;
    quint32 m_ingameKeyForwardNative;
    quint32 m_ingameModRunNative;
    quint32 m_ingameKeyRunNative;
    bool m_ingameKeyForwardIsMouse;
    bool m_ingameKeyRunIsMouse;
    quint32 m_limitTimeRun;
    quint32 m_limitTimeWalk;
    AutoTools *m_tools;

    void PhaseOne();
    void PhaseTwo();
public slots:
    void process();
    void AllPhases();
private:
    bool lastActionPhaseOne;
    QElapsedTimer m_phaseOneTimer;
    QElapsedTimer m_phaseTwoTimer;
};

#endif // AUTORUNPROCESS_H
