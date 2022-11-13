#include "autotrackprocessmanager.h"

AutotrackProcessManager::AutotrackProcessManager(QObject *parent)
    : QObject{parent}
{
    m_thread = nullptr;
    m_process = nullptr;
    m_tools = new AutoTools(this);
}

bool AutotrackProcessManager::configure(QString ingameModForward, QString ingameKeyForward, QString ingameModRun, QString ingameKeyRun, QString ingameModCrouch, QString ingameKeyCrouch,
                                        quint32 ingameModForwardNative, quint32 ingameKeyForwardNative, quint32 ingameModRunNative, quint32 ingameKeyRunNative, quint32 ingameModCrouchNative, quint32 ingameKeyCrouchNative,
                                        bool ingameKeyForwardIsMouse, bool ingameKeyRunIsMouse, bool ingameKeyCrouchIsMouse, double timeRun, double timeCrouch)
{
    if( (ingameModForward.isEmpty() && ingameKeyForward.isEmpty()) || (ingameModRun.isEmpty() && ingameKeyRun.isEmpty()) || (ingameModCrouch.isEmpty() && ingameKeyCrouch.isEmpty()))
        return false;

    if(timeRun < 0. || timeCrouch < 0.)
        return false;

    m_ingameModForwardNative = ingameModForwardNative;
    m_ingameKeyForwardNative = ingameKeyForwardNative;
    m_ingameModRunNative = ingameModRunNative;
    m_ingameKeyRunNative = ingameKeyRunNative;
    m_ingameModCrouchNative = ingameModCrouchNative;
    m_ingameKeyCrouchNative = ingameKeyCrouchNative;
    m_ingameKeyForwardIsMouse = ingameKeyForwardIsMouse;
    m_ingameKeyRunIsMouse = ingameKeyRunIsMouse;
    m_ingameKeyCrouchIsMouse = ingameKeyCrouchIsMouse;

    m_limitTimeRun = (quint32)(timeRun*1000);
    m_limitTimeCrouch = (quint32)(timeCrouch*1000);

    return true;
}

void AutotrackProcessManager::run()
{
    m_thread = new QThread(this);
    m_process = new AutotrackProcess();
    m_process->moveToThread(m_thread);
    m_process->m_tools = m_tools;
    m_process->m_ingameModForwardNative = m_ingameModForwardNative;
    m_process->m_ingameKeyForwardNative = m_ingameKeyForwardNative;
    m_process->m_ingameModRunNative = m_ingameModRunNative;
    m_process->m_ingameKeyRunNative = m_ingameKeyRunNative;
    m_process->m_ingameModCrouchNative = m_ingameModCrouchNative;
    m_process->m_ingameKeyCrouchNative = m_ingameKeyCrouchNative;
    m_process->m_ingameKeyForwardIsMouse = m_ingameKeyForwardIsMouse;
    m_process->m_ingameKeyRunIsMouse = m_ingameKeyRunIsMouse;
    m_process->m_ingameKeyCrouchIsMouse = m_ingameKeyCrouchIsMouse;
    m_process->m_limitTimeRun = m_limitTimeRun;
    m_process->m_limitTimeCrouch = m_limitTimeCrouch;
    connect( m_thread, &QThread::started, m_process, &AutotrackProcess::process);
    connect( m_thread, &QThread::finished, m_thread, &QThread::deleteLater);
    m_thread->start();
}

void AutotrackProcessManager::stop()
{
    if(m_thread!= nullptr && m_thread->isRunning())
    {
        m_thread->quit();
        m_tools->releaseKey(m_ingameModForwardNative);
        m_tools->releaseKey(m_ingameKeyForwardNative,m_ingameKeyForwardIsMouse);
        m_tools->releaseKey(m_ingameModRunNative);
        m_tools->releaseKey(m_ingameKeyRunNative,m_ingameKeyRunIsMouse);
        m_tools->releaseKey(m_ingameModCrouchNative);
        m_tools->releaseKey(m_ingameKeyCrouchNative,m_ingameKeyCrouchIsMouse);

        m_thread->wait();

        delete m_thread;
        delete m_process;
        m_thread = nullptr;
        m_process = nullptr;
    }
}
