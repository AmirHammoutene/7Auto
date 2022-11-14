#include "automineprocessmanager.h"

AutomineProcessManager::AutomineProcessManager(QObject *parent)
    : QObject{parent}
{
    m_thread = nullptr;
    m_process = nullptr;
    m_tools = new AutoTools(this);
}

bool AutomineProcessManager::configure(QString ingameModForward, QString ingameKeyForward, QString ingameModPrimaryAct, QString ingameKeyPrimaryAct, QString ingameModSecondaryAct, QString ingameKeySecondaryAct,
                                       quint32 ingameModForwardNative, quint32 ingameKeyForwardNative, quint32 ingameModPrimaryActNative, quint32 ingameKeyPrimaryActNative, quint32 ingameModSecondaryActNative, quint32 ingameKeySecondaryActNative,
                                       bool ingameKeyForwardIsMouse, bool ingameKeyPrimaryActIsMouse, bool ingameKeySecondaryActIsMouse,
                                       double timeHit, double timePause, double delayWalk, double timeWalk, double simpleHitDur, double powerHitDur,
                                       QString hitSequence)
{
    if( (ingameModForward.isEmpty() && ingameKeyForward.isEmpty()) || (ingameModPrimaryAct.isEmpty() && ingameKeyPrimaryAct.isEmpty()) || (ingameModSecondaryAct.isEmpty() && ingameKeySecondaryAct.isEmpty()))
        return false;

    if(timeHit < 0. || timePause < 0. || delayWalk < 0. || timeWalk < 0. || simpleHitDur < 0. || powerHitDur < 0.)
        return false;

    if(hitSequence.isEmpty())
        return false;

    m_ingameModForwardNative = ingameModForwardNative;
    m_ingameKeyForwardNative = ingameKeyForwardNative;
    m_ingameModPrimaryActNative = ingameModPrimaryActNative;
    m_ingameKeyPrimaryActNative = ingameKeyPrimaryActNative;
    m_ingameModSecondaryActNative = ingameModSecondaryActNative;
    m_ingameKeySecondaryActNative = ingameKeySecondaryActNative;
    m_ingameKeyForwardIsMouse = ingameKeyForwardIsMouse;
    m_ingameKeyPrimaryActIsMouse = ingameKeyPrimaryActIsMouse;
    m_ingameKeySecondaryActIsMouse = ingameKeySecondaryActIsMouse;

    m_limitTimeHit = (quint32)(timeHit*1000);
    m_limitTimePause = (quint32)(timePause*1000);
    m_walkDelay = (quint32)(delayWalk*1000);
    m_limitTimeWalk = (quint32)(timeWalk*1000);
    m_durationPrimaryAct = (quint32)(simpleHitDur*1000);
    m_durationSecondaryAct = (quint32)(powerHitDur*1000);

    m_hitSequence.clear();

    for(int i = 0; i< hitSequence.length(); i++)
    {
        m_hitSequence.append(hitSequence.at(i) == '2');
    }

    return true;
}

void AutomineProcessManager::run()
{
    m_thread = new QThread(this);
    m_process = new AutomineProcess();
    m_process->moveToThread(m_thread);
    m_process->m_tools = m_tools;
    m_process->m_ingameModForwardNative = m_ingameModForwardNative;
    m_process->m_ingameKeyForwardNative = m_ingameKeyForwardNative;
    m_process->m_ingameModPrimaryActNative = m_ingameModPrimaryActNative;
    m_process->m_ingameKeyPrimaryActNative = m_ingameKeyPrimaryActNative;
    m_process->m_ingameModSecondaryActNative = m_ingameModSecondaryActNative;
    m_process->m_ingameKeySecondaryActNative = m_ingameKeySecondaryActNative;
    m_process->m_ingameKeyForwardIsMouse = m_ingameKeyForwardIsMouse;
    m_process->m_ingameKeyPrimaryActIsMouse = m_ingameKeyPrimaryActIsMouse;
    m_process->m_ingameKeySecondaryActIsMouse = m_ingameKeySecondaryActIsMouse;
    m_process->m_limitTimeHit = m_limitTimeHit;
    m_process->m_limitTimePause = m_limitTimePause;
    m_process->m_walkDelay = m_walkDelay;
    m_process->m_limitTimeWalk = m_limitTimeWalk;
    m_process->m_durationPrimaryAct = m_durationPrimaryAct;
    m_process->m_durationSecondaryAct = m_durationSecondaryAct;
    m_process->m_hitSequence = m_hitSequence;
    connect( m_thread, &QThread::started, m_process, &AutomineProcess::process);
    connect( m_thread, &QThread::finished, m_thread, &QThread::deleteLater);
    m_thread->start();
}

void AutomineProcessManager::stop()
{
    if(m_thread!= nullptr && m_thread->isRunning())
    {
        m_thread->quit();
        m_tools->releaseKey(m_ingameModForwardNative);
        m_tools->releaseKey(m_ingameKeyForwardNative,m_ingameKeyForwardIsMouse);
        m_tools->releaseKey(m_ingameModPrimaryActNative);
        m_tools->releaseKey(m_ingameKeyPrimaryActNative,m_ingameKeyPrimaryActIsMouse);
        m_tools->releaseKey(m_ingameModSecondaryActNative);
        m_tools->releaseKey(m_ingameKeySecondaryActNative,m_ingameKeySecondaryActIsMouse);

        m_thread->wait();

        delete m_thread;
        delete m_process;
        m_thread = nullptr;
        m_process = nullptr;
    }
}
