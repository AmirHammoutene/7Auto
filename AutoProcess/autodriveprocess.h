#ifndef AUTODRIVEPROCESS_H
#define AUTODRIVEPROCESS_H

#include <QObject>
#include "autotools.h"

class AutodriveProcess : public QObject
{
    Q_OBJECT
public:
    explicit AutodriveProcess(QObject *parent = nullptr);
    quint32 m_ingameModForwardNative;
    quint32 m_ingameKeyForwardNative;
    quint32 m_ingameModTurboNative;
    quint32 m_ingameKeyTurboNative;
    bool m_ingameKeyForwardIsMouse;
    bool m_ingameKeyTurboIsMouse;
    AutoTools *m_tools;

public slots:
    void process();
    void OnlyPhase();
};

#endif // AUTODRIVEPROCESS_H
