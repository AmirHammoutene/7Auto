#include "autodriveprocess.h"
#include <QTimer>

AutodriveProcess::AutodriveProcess(QObject *parent)
    : QObject{parent}
{

}

void AutodriveProcess::process()
{
    if(!m_tools)
        return;
    OnlyPhase();
}

void AutodriveProcess::OnlyPhase()
{
    m_tools->pressKey(m_ingameModForwardNative);
    m_tools->pressKey(m_ingameKeyForwardNative, m_ingameKeyForwardIsMouse);
    m_tools->pressKey(m_ingameModTurboNative);
    m_tools->pressKey(m_ingameKeyTurboNative, m_ingameKeyTurboIsMouse);

    QTimer::singleShot(50,this,&AutodriveProcess::OnlyPhase);
}
