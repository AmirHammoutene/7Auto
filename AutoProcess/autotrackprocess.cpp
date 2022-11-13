#include "autotrackprocess.h"
#include <QTimer>

AutotrackProcess::AutotrackProcess(QObject *parent)
    : QObject{parent}
{

}

void AutotrackProcess::process()
{
    if(!m_tools)
        return;
    lastActionPhaseOne = false;
    lastActionPhaseTwo = false;
    m_phaseOneTimer.start();
    AllPhases();
}

void AutotrackProcess::AllPhases()
{
    if(m_phaseOneTimer.elapsed() < m_limitTimeRun)
    {
        if(lastActionPhaseTwo)
        {
            m_tools->releaseKey(m_ingameModCrouchNative);
            m_tools->releaseKey(m_ingameKeyCrouchNative, m_ingameKeyCrouchIsMouse);
        }
        PhaseOne();
        lastActionPhaseOne = true;
        lastActionPhaseTwo = false;
    }
    else
    {
        if(lastActionPhaseOne)
        {
            m_tools->releaseKey(m_ingameModRunNative);
            m_tools->releaseKey(m_ingameKeyRunNative, m_ingameKeyRunIsMouse);
            m_phaseTwoTimer.start();
        }
        PhaseTwo();
        lastActionPhaseOne = false;
        lastActionPhaseTwo = true;
        if(m_phaseTwoTimer.elapsed() > m_limitTimeCrouch)
            m_phaseOneTimer.start();
    }

    QTimer::singleShot(50,this,&AutotrackProcess::AllPhases);
}

void AutotrackProcess::PhaseOne()
{
    m_tools->pressKey(m_ingameModForwardNative);
    m_tools->pressKey(m_ingameKeyForwardNative, m_ingameKeyForwardIsMouse);
    m_tools->pressKey(m_ingameModRunNative);
    m_tools->pressKey(m_ingameKeyRunNative, m_ingameKeyRunIsMouse);
}

void AutotrackProcess::PhaseTwo()
{
    m_tools->pressKey(m_ingameModForwardNative);
    m_tools->pressKey(m_ingameKeyForwardNative, m_ingameKeyForwardIsMouse);
    m_tools->pressKey(m_ingameModCrouchNative);
    m_tools->pressKey(m_ingameKeyCrouchNative, m_ingameKeyCrouchIsMouse);
}
