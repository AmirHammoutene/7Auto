#ifndef KEYPUSHBUTTON_H
#define KEYPUSHBUTTON_H

#include <QPushButton>
#include <QObject>
#include <QElapsedTimer>
class MainWindow;

class KeyPushButton : public QPushButton
{
    Q_OBJECT
public:
    KeyPushButton(QWidget *parent = nullptr);
    QElapsedTimer m_timer;
    void setMainWindow(MainWindow *m);
    QString m_mod;
    QString m_key;
    quint32 m_keyNative;
    quint32 m_modNative;
    bool m_isMouse;
public slots:
    void catchInput(bool);
    void unckeck();
signals:
    void keyPushButtonSet(QString modifiers, QString key,quint32 modNative, quint32 keyNative, bool isMousePressed);
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
};

#endif // KEYPUSHBUTTON_H
