#include "autorunprocess.h"
#include <QTimer>

AutorunProcess::AutorunProcess(QObject *parent)
    : QObject{parent}
{

}

void AutorunProcess::process()
{
    if(!m_tools)
        return;
    lastActionPhaseOne = false;
    m_phaseOneTimer.start();
    AllPhases();
}

void AutorunProcess::AllPhases()
{
    if(m_phaseOneTimer.elapsed() < m_limitTimeRun)
    {
        PhaseOne();
        lastActionPhaseOne = true;
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
        if(m_phaseTwoTimer.elapsed() > m_limitTimeWalk)
            m_phaseOneTimer.start();
    }

    QTimer::singleShot(50,this,&AutorunProcess::AllPhases);
}

void AutorunProcess::PhaseOne()
{
    m_tools->pressKey(m_ingameModForwardNative);
    m_tools->pressKey(m_ingameKeyForwardNative, m_ingameKeyForwardIsMouse);
    m_tools->pressKey(m_ingameModRunNative);
    m_tools->pressKey(m_ingameKeyRunNative, m_ingameKeyRunIsMouse);
}

void AutorunProcess::PhaseTwo()
{
    m_tools->pressKey(m_ingameModForwardNative);
    m_tools->pressKey(m_ingameKeyForwardNative, m_ingameKeyForwardIsMouse);
}
