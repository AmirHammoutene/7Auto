#include "autodriveprocessmanager.h"

AutodriveProcessManager::AutodriveProcessManager(QObject *parent)
    : QObject{parent}
{
    m_thread = nullptr;
    m_process = nullptr;
    m_tools = new AutoTools(this);
}

bool AutodriveProcessManager::configure(QString ingameModForward, QString ingameKeyForward, QString ingameModTurbo, QString ingameKeyTurbo,
        quint32 ingameModForwardNative, quint32 ingameKeyForwardNative, quint32 ingameModTurboNative, quint32 ingameKeyTurboNative,
        bool ingameKeyForwardIsMouse, bool ingameKeyTurboIsMouse)
{
    if( (ingameModForward.isEmpty() && ingameKeyForward.isEmpty()) || (ingameModTurbo.isEmpty() && ingameKeyTurbo.isEmpty()))
        return false;

    m_ingameModForwardNative = ingameModForwardNative;
    m_ingameKeyForwardNative = ingameKeyForwardNative;
    m_ingameModTurboNative = ingameModTurboNative;
    m_ingameKeyTurboNative = ingameKeyTurboNative;
    m_ingameKeyForwardIsMouse = ingameKeyForwardIsMouse;
    m_ingameKeyTurboIsMouse = ingameKeyTurboIsMouse;

    return true;
}

void AutodriveProcessManager::run()
{
    m_thread = new QThread(this);
    m_process = new AutodriveProcess();
    m_process->moveToThread(m_thread);
    m_process->m_tools = m_tools;
    m_process->m_ingameModForwardNative = m_ingameModForwardNative;
    m_process->m_ingameKeyForwardNative = m_ingameKeyForwardNative;
    m_process->m_ingameModTurboNative = m_ingameModTurboNative;
    m_process->m_ingameKeyTurboNative = m_ingameKeyTurboNative;
    m_process->m_ingameKeyForwardIsMouse = m_ingameKeyForwardIsMouse;
    m_process->m_ingameKeyTurboIsMouse = m_ingameKeyTurboIsMouse;
    connect( m_thread, &QThread::started, m_process, &AutodriveProcess::process);
    connect( m_thread, &QThread::finished, m_thread, &QThread::deleteLater);
    m_thread->start();
}

void AutodriveProcessManager::stop()
{
    if(m_thread!= nullptr && m_thread->isRunning())
    {
        m_thread->quit();
        m_tools->releaseKey(m_ingameModForwardNative);
        m_tools->releaseKey(m_ingameKeyForwardNative,m_ingameKeyForwardIsMouse);
        m_tools->releaseKey(m_ingameModTurboNative);
        m_tools->releaseKey(m_ingameKeyTurboNative,m_ingameKeyTurboIsMouse);

        m_thread->wait();

        delete m_thread;
        delete m_process;
        m_thread = nullptr;
        m_process = nullptr;
    }
}
