#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "globalshortcuthandler.h"
#include "presetswitchwidget.h"
#include <QLabel>
#include "AutoProcess/autodriveprocessmanager.h"
#include "AutoProcess/autorunprocessmanager.h"
#include "AutoProcess/autotrackprocessmanager.h"
#include "AutoProcess/automineprocessmanager.h"
#include "toolshitdurationsdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void onAutorunPushed();
    void onAutodrivePushed();
    void onAutotrackPushed();
    void onAutominePushed();

    void onAutorunExec(bool val);
    void onAutodriveExec(bool val);
    void onAutotrackExec(bool val);
    void onAutomineExec(bool val);

    void onAutorunExecTrigger();
    void onAutodriveExecTrigger();
    void onAutotrackExecTrigger();
    void onAutomineExecTrigger();

    void onKeyPushButtonSet(QString modifiers, QString key, quint32 modNative, quint32 keyNative, bool isMousePressed);

    void savePreset(PresetSwitchWidget::AutoType autotype, unsigned int currentIndex, QString name);
    void setAutorunValues(double runDuring, double walkDuring);
    void setAutotrackValues(double runDuring, double crouchDuring);
    void setAutomineValues(QString sequence, QString tool, double hitDuring, double pauseDuring, double moveDelay, double moveDuring);

    void refreshToolsComboBox();
protected:
    void closeEvent(QCloseEvent *event) override;
private:
    Ui::MainWindow *ui;
    GlobalShortcutHandler autorunGlobalShortcut;
    GlobalShortcutHandler autodriveGlobalShortcut;
    GlobalShortcutHandler autotrackGlobalShortcut;
    GlobalShortcutHandler automineGlobalShortcut;
    QLabel *m_autorunStatus;
    QLabel *m_autodriveStatus;
    QLabel *m_autotrackStatus;
    QLabel *m_automineStatus;
    ToolsHitDurationsDialog *toolsDialog;
    QMap<QString, QPair<double, double> >  m_toolsDurList;

    AutodriveProcessManager *m_autodriveProcessManager;
    AutorunProcessManager *m_autorunProcessManager;
    AutotrackProcessManager *m_autotrackProcessManager;
    AutomineProcessManager *m_automineProcessManager;
};
#endif // MAINWINDOW_H
