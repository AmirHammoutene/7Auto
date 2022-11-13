#include "autotools.h"
#include <QTimer>

AutoTools::AutoTools(QObject *parent)
    : QObject{parent}
{

}

void AutoTools::pressKey(WORD keycode, bool isMouse)
{
    INPUT ip;
    if(!isMouse)
    {
        ip.type = INPUT_KEYBOARD;
        ip.ki.wScan = 0;
        ip.ki.time = 0;
        ip.ki.dwExtraInfo = 0;
        ip.ki.wVk =  keycode;
        ip.ki.dwFlags =  0;
    }
    else
    {
        ip.type = INPUT_MOUSE;
        ip.mi.dx = 0;
        ip.mi.dy = 0;
        ip.mi.mouseData = 0;
        ip.mi.time = 0;
        ip.mi.dwExtraInfo = 0;
        ip.mi.dwFlags = keycode;
    }

    SendInput(1, &ip, sizeof(INPUT));
    if(isMouse)
        QTimer::singleShot(40,this, [this, keycode, isMouse]{ releaseKey(keycode,isMouse);});
}

void AutoTools::releaseKey(WORD keycode, bool isMouse)
{
    INPUT ip;
    if(!isMouse)
    {
        ip.type = INPUT_KEYBOARD;
        ip.ki.wScan = 0;
        ip.ki.time = 0;
        ip.ki.dwExtraInfo = 0;
        ip.ki.wVk =  keycode;
        ip.ki.dwFlags =  KEYEVENTF_KEYUP;
    }
    else
    {
        ip.type = INPUT_MOUSE;
        ip.mi.dx = 0;
        ip.mi.dy = 0;
        ip.mi.mouseData = 0;
        ip.mi.time = 0;
        ip.mi.dwExtraInfo = 0;
        ip.mi.dwFlags = mouseUpConversion(keycode);
    }

    SendInput(1, &ip, sizeof(INPUT));
}

WORD AutoTools::mouseUpConversion(WORD mouseDown)
{
    WORD returnedUpValue;
    switch(mouseDown)
    {
    case 0x0002:
        returnedUpValue = 0x0004;
        break;
    case 0x0008:
        returnedUpValue = 0x0010;
        break;
    case 0x0020:
        returnedUpValue = 0x0040;
        break;
    default:
        returnedUpValue = 0;
        break;
    }
    return returnedUpValue;
}
