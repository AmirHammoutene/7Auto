#include "globalshortcuthandler.h"
#include <QDebug>

GlobalShortcutHandler::GlobalShortcutHandler(QObject *parent)
    : QObject{parent}
{

}

void GlobalShortcutHandler::disable()
{
    m_globalShortcut.setShortcut(QKeySequence(""));
    m_globalShortcut.setEnabled(false);

    disconnect(&m_globalShortcut, &QxtGlobalShortcut::activated,this, &GlobalShortcutHandler::handleGlobalShortcut);
}

void GlobalShortcutHandler::setShortcutAndEnable(QString shortcutStr)
{
    disable();
    if(shortcutStr.isEmpty())
        return;

    m_globalShortcut.setShortcut(QKeySequence(shortcutStr));
    m_globalShortcut.setEnabled(true);

    connect(&m_globalShortcut, &QxtGlobalShortcut::activated,this, &GlobalShortcutHandler::handleGlobalShortcut);
}

void GlobalShortcutHandler::handleGlobalShortcut()
{
    if(!m_globalShortcut.isValid() || !m_globalShortcut.isEnabled())
        return;

     emit triggered();
}
