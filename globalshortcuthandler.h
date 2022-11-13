#ifndef GLOBALSHORTCUTHANDLER_H
#define GLOBALSHORTCUTHANDLER_H

#include <QObject>
#include "lib/qxtglobalshortcut/src/qxtglobalshortcut.h"

class GlobalShortcutHandler : public QObject
{
    Q_OBJECT
public:
    explicit GlobalShortcutHandler(QObject *parent = nullptr);
    void setShortcutAndEnable(QString shortcutStr = "");
    void disable();

public slots:
    void handleGlobalShortcut();

private:
    QString m_shortcutStr;
    QxtGlobalShortcut m_globalShortcut;
signals:
    void triggered();

};

#endif // GLOBALSHORTCUTHANDLER_H
