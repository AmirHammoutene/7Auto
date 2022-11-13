#ifndef AUTOMINEPROCESS_H
#define AUTOMINEPROCESS_H

#include <QObject>
#include "autotools.h"
#include <QElapsedTimer>

class AutomineProcess : public QObject
{
    Q_OBJECT
public:
    explicit AutomineProcess(QObject *parent = nullptr);
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
    quint32 m_limitTimeHit;
    quint32 m_limitTimePause;
    quint32 m_walkDelay;
    quint32 m_limitTimeWalk;
    quint32 m_durationPrimaryAct;
    quint32 m_durationSecondaryAct;
    AutoTools *m_tools;

    void PhaseOne();
    void PhaseOneStepA();
    void PhaseOneStepB();
    void PhaseTwo();
public slots:
    void process();
    void AllPhases();
private:
    bool lastActionPhaseOne;
    bool lastActionPhaseOneStepA;
    bool lastActionPhaseTwo;
    QElapsedTimer m_phaseOneTimer;
    QElapsedTimer m_phaseOneStepATimer;
    QElapsedTimer m_phaseOneStepBTimer;
    QElapsedTimer m_phaseTwoTimer;
    int m_sequenceIndex;

    bool m_inHitActionNow;

};

#endif // AUTOMINEPROCESS_H
