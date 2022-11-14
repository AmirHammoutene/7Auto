#include "automineprocess.h"
#include <QTimer>
#include <QThread>

AutomineProcess::AutomineProcess(QObject *parent)
    : QObject{parent}
{

}

void AutomineProcess::process()
{
    if(!m_tools)
        return;
    lastActionPhaseOne = false;
    lastActionPhaseOneStepA = false;
    lastActionPhaseTwo = false;
    m_inHitActionNow = false;
    m_sequenceIndex = -1;
    m_phaseOneTimer.start();
    AllPhases();
}

void AutomineProcess::AllPhases()
{
    if(m_inHitActionNow)
    {
        QTimer::singleShot(50,this,&AutomineProcess::AllPhases);
        return;
    }

    if(m_phaseOneTimer.elapsed() < m_walkDelay || m_walkDelay == 0)
    {
        if(lastActionPhaseTwo)
        {
            m_tools->releaseKey(m_ingameModForwardNative);
            m_tools->releaseKey(m_ingameKeyForwardNative, m_ingameKeyForwardIsMouse);
            lastActionPhaseOneStepA = false;
            m_sequenceIndex = -1;
            m_phaseOneStepATimer.start();
        }
        PhaseOne();
    }
    else
    {
        if(lastActionPhaseOne)
        {
            m_tools->releaseKey(m_ingameModPrimaryActNative);
            m_tools->releaseKey(m_ingameKeyPrimaryActNative, m_ingameKeyPrimaryActIsMouse);
            m_tools->releaseKey(m_ingameModPrimaryActNative);
            m_tools->releaseKey(m_ingameModSecondaryActNative);
            m_tools->releaseKey(m_ingameKeySecondaryActNative, m_ingameKeySecondaryActIsMouse);
            m_phaseTwoTimer.start();
        }
        PhaseTwo();
        lastActionPhaseOne = false;
        lastActionPhaseTwo = true;
        if(m_phaseTwoTimer.elapsed() > m_limitTimeWalk)
            m_phaseOneTimer.start();
    }

    QTimer::singleShot(50,this,&AutomineProcess::AllPhases);
}

void AutomineProcess::PhaseOne()
{
    if(m_phaseOneStepATimer.elapsed() < m_limitTimeHit)
    {
        PhaseOneStepA();
    }
    else
    {
        if(lastActionPhaseOneStepA)
        {
            m_tools->releaseKey(m_ingameModPrimaryActNative);
            m_tools->releaseKey(m_ingameKeyPrimaryActNative, m_ingameKeyPrimaryActIsMouse);
            m_tools->releaseKey(m_ingameModPrimaryActNative);
            m_tools->releaseKey(m_ingameModSecondaryActNative);
            m_tools->releaseKey(m_ingameKeySecondaryActNative, m_ingameKeySecondaryActIsMouse);
            m_sequenceIndex = -1;
            m_phaseOneStepBTimer.start();
        }
        PhaseOneStepB();
        lastActionPhaseOneStepA = false;
        lastActionPhaseOne = true;
        lastActionPhaseTwo = false;
        if(m_phaseOneStepBTimer.elapsed() > m_limitTimePause)
            m_phaseOneStepATimer.start();
    }
}

void AutomineProcess::PhaseOneStepA()
{
    if(++m_sequenceIndex >= m_hitSequence.size())
        m_sequenceIndex = 0;

    quint32 hitDuration = 0;
    if(m_hitSequence.at(m_sequenceIndex))
    {
        if(m_durationSecondaryAct != 0)
        {
            m_tools->pressKey(m_ingameModSecondaryActNative);
            m_tools->pressKey(m_ingameKeySecondaryActNative, m_ingameKeySecondaryActIsMouse);
            hitDuration = m_durationSecondaryAct;
        }
    }
    else
    {
        if(m_durationPrimaryAct != 0)
        {
            m_tools->pressKey(m_ingameModPrimaryActNative);
            m_tools->pressKey(m_ingameKeyPrimaryActNative, m_ingameKeyPrimaryActIsMouse);
            hitDuration = m_durationPrimaryAct;
        }
    }

    lastActionPhaseOneStepA = true;
    lastActionPhaseOne = true;
    lastActionPhaseTwo = false;

    if(hitDuration > 0)
    {
        m_inHitActionNow = true;
        QThread::msleep(hitDuration);
        m_inHitActionNow = false;
    }
}

void AutomineProcess::PhaseOneStepB()
{
        // Do nothing, a pause means that you stay still
}

void AutomineProcess::PhaseTwo()
{
    m_tools->pressKey(m_ingameModForwardNative);
    m_tools->pressKey(m_ingameKeyForwardNative, m_ingameKeyForwardIsMouse);
}
