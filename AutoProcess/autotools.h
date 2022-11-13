#ifndef AUTOTOOLS_H
#define AUTOTOOLS_H

#include <qt_windows.h>
#include <QObject>

class AutoTools: public QObject
{
    Q_OBJECT
public:
    AutoTools(QObject *parent = nullptr);
    void pressKey(WORD keycode, bool isMouse = false);
    void releaseKey(WORD keycode, bool isMouse = false);
private:
    WORD mouseUpConversion(WORD mouseDown);
};

#endif // AUTOTOOLS_H
