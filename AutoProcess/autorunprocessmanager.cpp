#include "autorunprocessmanager.h"

AutorunProcessManager::AutorunProcessManager(QObject *parent)
    : QObject{parent}
{
    m_thread = nullptr;
    m_process = nullptr;
    m_tools = new AutoTools(this);
}

bool AutorunProcessManager::configure(QString ingameModForward, QString ingameKeyForward, QString ingameModRun, QString ingameKeyRun,
                                      quint32 ingameModForwardNative, quint32 ingameKeyForwardNative, quint32 ingameModRunNative, quint32 ingameKeyRunNative, bool ingameKeyForwardIsMouse, bool ingameKeyRunIsMouse,
                                      double timeRun, double timeWalk)
{
    if( (ingameModForward.isEmpty() && ingameKeyForward.isEmpty()) || (ingameModRun.isEmpty() && ingameKeyRun.isEmpty()))
        return false;

    if(timeRun < 0. || timeWalk < 0.)
        return false;

    m_ingameModForwardNative = ingameModForwardNative;
    m_ingameKeyForwardNative = ingameKeyForwardNative;
    m_ingameModRunNative = ingameModRunNative;
    m_ingameKeyRunNative = ingameKeyRunNative;
    m_ingameKeyForwardIsMouse = ingameKeyForwardIsMouse;
    m_ingameKeyRunIsMouse = ingameKeyRunIsMouse;

    m_limitTimeRun = (quint32)(timeRun*1000);
    m_limitTimeWalk = (quint32)(timeWalk*1000);

    return true;
}

void AutorunProcessManager::run()
{
    m_thread = new QThread(this);
    m_process = new AutorunProcess();
    m_process->moveToThread(m_thread);
    m_process->m_tools = m_tools;
    m_process->m_ingameModForwardNative = m_ingameModForwardNative;
    m_process->m_ingameKeyForwardNative = m_ingameKeyForwardNative;
    m_process->m_ingameModRunNative = m_ingameModRunNative;
    m_process->m_ingameKeyRunNative = m_ingameKeyRunNative;
    m_process->m_ingameKeyForwardIsMouse = m_ingameKeyForwardIsMouse;
    m_process->m_ingameKeyRunIsMouse = m_ingameKeyRunIsMouse;
    m_process->m_limitTimeRun = m_limitTimeRun;
    m_process->m_limitTimeWalk = m_limitTimeWalk;
    connect( m_thread, &QThread::started, m_process, &AutorunProcess::process);
    connect( m_thread, &QThread::finished, m_thread, &QThread::deleteLater);
    m_thread->start();
}

void AutorunProcessManager::stop()
{
    if(m_thread!= nullptr && m_thread->isRunning())
    {
        m_thread->quit();
        m_tools->releaseKey(m_ingameModForwardNative);
        m_tools->releaseKey(m_ingameKeyForwardNative,m_ingameKeyForwardIsMouse);
        m_tools->releaseKey(m_ingameModRunNative);
        m_tools->releaseKey(m_ingameKeyRunNative,m_ingameKeyRunIsMouse);

        m_thread->wait();

        delete m_thread;
        delete m_process;
        m_thread = nullptr;
        m_process = nullptr;
    }
}
