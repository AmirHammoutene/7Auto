#include "keypushbutton.h"
#include <QKeyEvent>
#include <QTimer>
#include <QToolTip>
#include "mainwindow.h"

KeyPushButton::KeyPushButton(QWidget *parent)
  : QPushButton(parent)
{
    connect(this,&QPushButton::toggled, this,&KeyPushButton::catchInput);
}

void KeyPushButton::setMainWindow(MainWindow *m)
{
    connect(this, &KeyPushButton::keyPushButtonSet, m, &MainWindow::onKeyPushButtonSet);
}

void KeyPushButton::catchInput(bool val)
{
    blockSignals(true);
    if(val)
        QTimer::singleShot(5000, this, &KeyPushButton::unckeck);
}

void KeyPushButton::unckeck()
{
    setChecked(false);
    blockSignals(false);
}

void KeyPushButton::keyPressEvent(QKeyEvent *event)
{
    if(isChecked())
    {
        if (event->key() != Qt::Key_Escape)
        {
            m_keyNative = event->nativeVirtualKey();
            m_key = QKeySequence(event->key()).toString();
            m_key = m_key.isValidUtf16() ? m_key : "";
            m_modNative = event->nativeModifiers();
            m_mod = QKeySequence(event->modifiers().toInt()).toString();
            m_isMouse = false;
        }
        else
        {
            m_key = m_mod = "";
            m_keyNative = m_modNative = 0;
            m_isMouse = false;
        }
        blockSignals(false);
        setText(m_mod+ m_key);
        emit keyPushButtonSet(m_mod,m_key,m_modNative,m_keyNative,m_isMouse);
    }
}

void KeyPushButton::mousePressEvent(QMouseEvent *event)
{

    if(isChecked() && (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonDblClick))
    {
        if(property("type").toInt() == 2)
        {
            setText("Can't use mouse buttons...try again");
            return;
        }
        switch (event->button())
        {
            case Qt::LeftButton:
                m_key = "LeftClick";
                m_keyNative = 0x0002;
                break;
            case Qt::RightButton:
                m_key = "RightClick";
                m_keyNative = 0x0008;
                break;
            case Qt::MiddleButton:
                m_key = "MiddleClick";
                m_keyNative = 0x0020;
                break;
            case Qt::BackButton:
                m_key = "Mouse4Click";
                m_keyNative = 0;
                break;
            case Qt::ForwardButton:
                m_key = "Mouse5Click";
                m_keyNative = 0;
                break;
            default:
                break;
        }
        QKeyEvent keyEv = QKeyEvent(QEvent::KeyPress, Qt::Key_Enter, event->modifiers());
        m_modNative = keyEv.nativeModifiers();
        QString m_mod = QKeySequence(event->modifiers().toInt()).toString();
        m_isMouse = true;
        blockSignals(false);
        setText(m_mod+m_key);
        emit keyPushButtonSet(m_mod,m_key,m_modNative,m_keyNative,m_isMouse);
    }
    else
        QPushButton::mousePressEvent(event);
}
