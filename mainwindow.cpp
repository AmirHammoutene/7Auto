#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QSettings>
#include <QRegularExpression>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window
        | Qt::WindowContextHelpButtonHint
        | Qt::WindowCloseButtonHint);
    QFile darkQssFile("dark.qss");
    if(darkQssFile.exists())
    {
        if(darkQssFile.open(QFile::ReadOnly))
        {
            qApp->setStyleSheet(QLatin1String(darkQssFile.readAll()));
            darkQssFile.close();
        }
    }

    QRegularExpression rx("[1,2]*");
    QValidator *validator = new QRegularExpressionValidator(rx, this);
    ui->automineSequenceEdit->setValidator(validator);

    QSettings settings("settings.ini", QSettings::IniFormat);

    ui->keyForwardButton->setProperty("id","keyForwardButton");
    ui->keyForwardButton->setProperty("type", 1);
    ui->keyForwardButton->m_mod = settings.value("keyForwardButton/mod").toString();
    ui->keyForwardButton->m_key = settings.value("keyForwardButton/key").toString();
    ui->keyForwardButton->m_keyNative = settings.value("keyForwardButton/keyNative").toInt();
    ui->keyForwardButton->m_modNative = settings.value("keyForwardButton/modNative").toInt();
    ui->keyForwardButton->m_isMouse = settings.value("keyForwardButton/isMouse").toBool();
    ui->keyForwardButton->setText(ui->keyForwardButton->m_mod+ui->keyForwardButton->m_key);
    ui->keyForwardButton->setMainWindow(this);
    ui->keyRunButton->setProperty("id","keyRunButton");
    ui->keyRunButton->setProperty("type", 1);
    ui->keyRunButton->m_mod = settings.value("keyRunButton/mod").toString();
    ui->keyRunButton->m_key = settings.value("keyRunButton/key").toString();
    ui->keyRunButton->m_keyNative = settings.value("keyRunButton/keyNative").toInt();
    ui->keyRunButton->m_modNative = settings.value("keyRunButton/modNative").toInt();
    ui->keyRunButton->m_isMouse = settings.value("keyRunButton/isMouse").toBool();
    ui->keyRunButton->setText(ui->keyRunButton->m_mod+ui->keyRunButton->m_key);
    ui->keyRunButton->setMainWindow(this);
    ui->keyTurboButton->setProperty("id","keyTurboButton");
    ui->keyTurboButton->setProperty("type", 1);
    ui->keyTurboButton->m_mod = settings.value("keyTurboButton/mod").toString();
    ui->keyTurboButton->m_key = settings.value("keyTurboButton/key").toString();
    ui->keyTurboButton->m_keyNative = settings.value("keyTurboButton/keyNative").toInt();
    ui->keyTurboButton->m_modNative = settings.value("keyTurboButton/modNative").toInt();
    ui->keyTurboButton->m_isMouse = settings.value("keyTurboButton/isMouse").toBool();
    ui->keyTurboButton->setText(ui->keyTurboButton->m_mod+ui->keyTurboButton->m_key);
    ui->keyTurboButton->setMainWindow(this);
    ui->keyCrouchButton->setProperty("id","keyCrouchButton");
    ui->keyCrouchButton->setProperty("type", 1);
    ui->keyCrouchButton->m_mod = settings.value("keyCrouchButton/mod").toString();
    ui->keyCrouchButton->m_key = settings.value("keyCrouchButton/key").toString();
    ui->keyCrouchButton->m_keyNative = settings.value("keyCrouchButton/keyNative").toInt();
    ui->keyCrouchButton->m_modNative = settings.value("keyCrouchButton/modNative").toInt();
    ui->keyCrouchButton->m_isMouse = settings.value("keyCrouchButton/isMouse").toBool();
    ui->keyCrouchButton->setText(ui->keyCrouchButton->m_mod+ui->keyCrouchButton->m_key);
    ui->keyCrouchButton->setMainWindow(this);
    ui->keyActionButton->setProperty("id","keyActionButton");
    ui->keyActionButton->setProperty("type", 1);
    ui->keyActionButton->m_mod = settings.value("keyActionButton/mod").toString();
    ui->keyActionButton->m_key = settings.value("keyActionButton/key").toString();
    ui->keyActionButton->m_keyNative = settings.value("keyActionButton/keyNative").toInt();
    ui->keyActionButton->m_modNative = settings.value("keyActionButton/modNative").toInt();
    ui->keyActionButton->m_isMouse = settings.value("keyActionButton/isMouse").toBool();
    ui->keyActionButton->setText(ui->keyActionButton->m_mod+ui->keyActionButton->m_key);
    ui->keyActionButton->setMainWindow(this);
    ui->keySecActionButton->setProperty("id","keySecActionButton");
    ui->keySecActionButton->setProperty("type", 1);
    ui->keySecActionButton->m_mod = settings.value("keySecActionButton/mod").toString();
    ui->keySecActionButton->m_key = settings.value("keySecActionButton/key").toString();
    ui->keySecActionButton->m_keyNative = settings.value("keySecActionButton/keyNative").toInt();
    ui->keySecActionButton->m_modNative = settings.value("keySecActionButton/modNative").toInt();
    ui->keySecActionButton->m_isMouse = settings.value("keySecActionButton/isMouse").toBool();
    ui->keySecActionButton->setText(ui->keySecActionButton->m_mod+ui->keySecActionButton->m_key);
    ui->keySecActionButton->setMainWindow(this);

    ui->autorunWindowsKey->setProperty("id","autorunWindowsKey");
    ui->autorunWindowsKey->setProperty("type", 2);
    ui->autorunWindowsKey->setText(settings.value("autorunWindowsKey/mod").toString()+settings.value("autorunWindowsKey/key").toString());
    ui->autorunWindowsKey->setMainWindow(this);
    ui->autodriveWindowsKey->setProperty("id","autodriveWindowsKey");
    ui->autodriveWindowsKey->setProperty("type", 2);
    ui->autodriveWindowsKey->setText(settings.value("autodriveWindowsKey/mod").toString()+settings.value("autodriveWindowsKey/key").toString());
    ui->autodriveWindowsKey->setMainWindow(this);
    ui->autotrackWindowsKey->setProperty("id","autotrackWindowsKey");
    ui->autotrackWindowsKey->setProperty("type", 2);
    ui->autotrackWindowsKey->setText(settings.value("autotrackWindowsKey/mod").toString()+settings.value("autotrackWindowsKey/key").toString());
    ui->autotrackWindowsKey->setMainWindow(this);
    ui->automineWindowsKey->setProperty("id","automineWindowsKey");
    ui->automineWindowsKey->setProperty("type", 2);
    ui->automineWindowsKey->setText(settings.value("automineWindowsKey/mod").toString()+settings.value("automineWindowsKey/key").toString());
    ui->automineWindowsKey->setMainWindow(this);

    autorunGlobalShortcut.setShortcutAndEnable(settings.value("autorunWindowsKey/mod").toString()+settings.value("autorunWindowsKey/key").toString());
    autodriveGlobalShortcut.setShortcutAndEnable(settings.value("autodriveWindowsKey/mod").toString()+settings.value("autodriveWindowsKey/key").toString());
    autotrackGlobalShortcut.setShortcutAndEnable(settings.value("autotrackWindowsKey/mod").toString()+settings.value("autotrackWindowsKey/key").toString());
    automineGlobalShortcut.setShortcutAndEnable(settings.value("automineWindowsKey/mod").toString()+settings.value("automineWindowsKey/key").toString());

    toolsDialog = new ToolsHitDurationsDialog(this);
    refreshToolsComboBox();
    connect(ui->editToolsButton, &QPushButton::released, toolsDialog, &ToolsHitDurationsDialog::showAndFillTable);
    connect(toolsDialog, &ToolsHitDurationsDialog::iniFileChanged, this, &MainWindow::refreshToolsComboBox);


    connect(ui->autorunPresetWidget,&PresetSwitchWidget::saveRequest, this, &MainWindow::savePreset);
    connect(ui->autotrackPresetWidget,&PresetSwitchWidget::saveRequest, this, &MainWindow::savePreset);
    connect(ui->autominePresetWidget,&PresetSwitchWidget::saveRequest, this, &MainWindow::savePreset);

    connect(ui->autorunPresetWidget,&PresetSwitchWidget::sendAutorunValues, this, &MainWindow::setAutorunValues);
    connect(ui->autotrackPresetWidget,&PresetSwitchWidget::sendAutotrackValues, this, &MainWindow::setAutotrackValues);
    connect(ui->autominePresetWidget,&PresetSwitchWidget::sendAutomineValues, this, &MainWindow::setAutomineValues);

    ui->autorunPresetWidget->initialize(PresetSwitchWidget::AutoType::Autorun,settings.value("presetsLastIndex/autorun",0).toInt());
    ui->autotrackPresetWidget->initialize(PresetSwitchWidget::AutoType::Autotrack,settings.value("presetsLastIndex/autotrack",0).toInt());
    ui->autominePresetWidget->initialize( PresetSwitchWidget::AutoType::Automine,settings.value("presetsLastIndex/automine",0).toInt());

    connect(ui->autorunButton,&QPushButton::released, this, &MainWindow::onAutorunPushed);
    connect(ui->autodriveButton,&QPushButton::released, this, &MainWindow::onAutodrivePushed);
    connect(ui->autotrackButton,&QPushButton::released, this, &MainWindow::onAutotrackPushed);
    connect(ui->automineButton,&QPushButton::released, this, &MainWindow::onAutominePushed);

    connect(ui->executeRun,&QPushButton::toggled, this, &MainWindow::onAutorunExec);
    connect(ui->executeDrive,&QPushButton::toggled, this, &MainWindow::onAutodriveExec);
    connect(ui->executeTrack,&QPushButton::toggled, this, &MainWindow::onAutotrackExec);
    connect(ui->executeMine,&QPushButton::toggled, this, &MainWindow::onAutomineExec);

    connect(&autorunGlobalShortcut,&GlobalShortcutHandler::triggered, this, &MainWindow::onAutorunExecTrigger);
    connect(&autodriveGlobalShortcut,&GlobalShortcutHandler::triggered, this, &MainWindow::onAutodriveExecTrigger);
    connect(&autotrackGlobalShortcut, &GlobalShortcutHandler::triggered, this, &MainWindow::onAutotrackExecTrigger);
    connect(&automineGlobalShortcut,&GlobalShortcutHandler::triggered, this, &MainWindow::onAutomineExecTrigger);

    connect(ui->autorunRunSpinBox, &QDoubleSpinBox::valueChanged, ui->autorunPresetWidget, &PresetSwitchWidget::saveCurrent);
    connect(ui->autorunWalkSpinBox, &QDoubleSpinBox::valueChanged, ui->autorunPresetWidget, &PresetSwitchWidget::saveCurrent);

    connect(ui->autotrackRunSpinBox, &QDoubleSpinBox::valueChanged, ui->autotrackPresetWidget, &PresetSwitchWidget::saveCurrent);
    connect(ui->autotrackCrouchSpinBox, &QDoubleSpinBox::valueChanged, ui->autotrackPresetWidget, &PresetSwitchWidget::saveCurrent);

    connect(ui->automineSequenceEdit, &QLineEdit::textChanged, ui->autominePresetWidget, &PresetSwitchWidget::saveCurrent);
    connect(ui->toolsComboBox, &QComboBox::currentTextChanged, ui->autominePresetWidget, &PresetSwitchWidget::saveCurrent);
    connect(ui->automineHitSpinBox, &QDoubleSpinBox::valueChanged, ui->autominePresetWidget, &PresetSwitchWidget::saveCurrent);
    connect(ui->autominePauseSpinBox, &QDoubleSpinBox::valueChanged, ui->autominePresetWidget, &PresetSwitchWidget::saveCurrent);
    connect(ui->automineMoveDelaySpinBox, &QDoubleSpinBox::valueChanged, ui->autominePresetWidget, &PresetSwitchWidget::saveCurrent);
    connect(ui->automineMoveDuringSpinBox, &QDoubleSpinBox::valueChanged, ui->autominePresetWidget, &PresetSwitchWidget::saveCurrent);

    m_autorunStatus = new QLabel("Autorun is running",nullptr);
    m_autodriveStatus = new QLabel("Autodrive is running",nullptr);
    m_autotrackStatus = new QLabel("Autotrack is running",nullptr);
    m_automineStatus = new QLabel("Automine is running",nullptr);

    statusBar()->addWidget(m_autorunStatus);
    statusBar()->addWidget(m_autodriveStatus);
    statusBar()->addWidget(m_autotrackStatus);
    statusBar()->addWidget(m_automineStatus);

    m_autorunStatus->hide();
    m_autodriveStatus->hide();
    m_autotrackStatus->hide();
    m_automineStatus->hide();

    m_autodriveProcessManager =  new AutodriveProcessManager(this);
    m_autorunProcessManager = new AutorunProcessManager(this);
    m_autotrackProcessManager = new AutotrackProcessManager(this);
    m_automineProcessManager = new AutomineProcessManager(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAutorunPushed()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::onAutodrivePushed()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::onAutotrackPushed()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::onAutominePushed()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::onAutorunExec(bool val)
{
    bool configureSuccess = m_autorunProcessManager->configure(ui->keyForwardButton->m_mod,ui->keyForwardButton->m_key,
                                                                 ui->keyRunButton->m_mod,ui->keyRunButton->m_key,
                                                                 ui->keyForwardButton->m_modNative,ui->keyForwardButton->m_keyNative,
                                                                 ui->keyRunButton->m_modNative,ui->keyRunButton->m_keyNative,
                                                               ui->keyForwardButton->m_isMouse,ui->keyRunButton->m_isMouse,
                                                               ui->autorunRunSpinBox->value(), ui->autorunWalkSpinBox->value());
    if(val)
    {
        if(configureSuccess)
        {
            ui->executeRun->setText("Stop");
            m_autorunStatus->show();
            m_autorunProcessManager->run();
            ui->autorunGroupBox->setEnabled(false);
        }
        else
        {
            QMessageBox::critical(this,"Keys are not recognized or bad values","Forward or Run ingame keys that you provided are not supported \
                                    by this program, or run or walk time values are incorrect. Sorry for the inconvenience.");
            ui->executeRun->setChecked(false);
        }

    }
    else
    {
        ui->executeRun->setText("Execute");
        m_autorunStatus->hide();
        m_autorunProcessManager->stop(); // we want to stop even if configuration failed
        ui->autorunGroupBox->setEnabled(true);
    }
}

void MainWindow::onAutodriveExec(bool val)
{
    bool configureSuccess = m_autodriveProcessManager->configure(ui->keyForwardButton->m_mod,ui->keyForwardButton->m_key,
                                                                 ui->keyTurboButton->m_mod,ui->keyTurboButton->m_key,
                                                                 ui->keyForwardButton->m_modNative,ui->keyForwardButton->m_keyNative,
                                                                 ui->keyTurboButton->m_modNative,ui->keyTurboButton->m_keyNative,
                                                                 ui->keyForwardButton->m_isMouse, ui->keyTurboButton->m_isMouse);
    if(val)
    {
        if(configureSuccess)
        {
            ui->executeDrive->setText("Stop");
            m_autodriveStatus->show();
            m_autodriveProcessManager->run();
        }
        else
        {
            QMessageBox::critical(this,"Keys are not recognized","Forward or Vehicule Turbo ingame keys that you provided are not supported \
                                    by this program. Sorry for the inconvenience.");
            ui->executeDrive->setChecked(false);
        }

    }
    else
    {
        ui->executeDrive->setText("Execute");
        m_autodriveStatus->hide();
        m_autodriveProcessManager->stop(); // we want to stop even if configuration failed
    }
}

void MainWindow::onAutotrackExec(bool val)
{
    bool configureSuccess = m_autotrackProcessManager->configure(ui->keyForwardButton->m_mod,ui->keyForwardButton->m_key,
                                                                 ui->keyRunButton->m_mod,ui->keyRunButton->m_key,
                                                                 ui->keyCrouchButton->m_mod,ui->keyCrouchButton->m_key,
                                                                 ui->keyForwardButton->m_modNative,ui->keyForwardButton->m_keyNative,
                                                                 ui->keyRunButton->m_modNative,ui->keyRunButton->m_keyNative,
                                                                 ui->keyCrouchButton->m_modNative,ui->keyCrouchButton->m_keyNative,
                                                               ui->keyForwardButton->m_isMouse,ui->keyRunButton->m_isMouse,ui->keyCrouchButton->m_isMouse,
                                                               ui->autotrackRunSpinBox->value(), ui->autotrackCrouchSpinBox->value());

    if(val)
    {
        if(configureSuccess)
        {
            ui->executeTrack->setText("Stop");
            m_autotrackStatus->show();
            m_autotrackProcessManager->run();
            ui->autotrackGroupBox->setEnabled(false);
        }
        else
        {
            QMessageBox::critical(this,"Keys are not recognized or bad values","Forward or Run or Crouch ingame keys that you provided are not supported \
                                    by this program, or run or crouch time values are incorrect. Sorry for the inconvenience.");
            ui->executeTrack->setChecked(false);
        }
    }
    else
    {
        ui->executeTrack->setText("Execute");
        m_autotrackStatus->hide();
        m_autotrackProcessManager->stop(); // we want to stop even if configuration failed
        ui->autotrackGroupBox->setEnabled(true);
    }
}

void MainWindow::onAutomineExec(bool val)
{
    bool configureSuccess = m_automineProcessManager->configure(ui->keyForwardButton->m_mod,ui->keyForwardButton->m_key,
                                                                 ui->keyActionButton->m_mod,ui->keyActionButton->m_key,
                                                                 ui->keySecActionButton->m_mod,ui->keySecActionButton->m_key,
                                                                 ui->keyForwardButton->m_modNative,ui->keyForwardButton->m_keyNative,
                                                                 ui->keyActionButton->m_modNative,ui->keyActionButton->m_keyNative,
                                                                 ui->keySecActionButton->m_modNative,ui->keySecActionButton->m_keyNative,
                                                               ui->keyForwardButton->m_isMouse,ui->keyActionButton->m_isMouse,ui->keySecActionButton->m_isMouse,
                                                               ui->automineHitSpinBox->value(), ui->autominePauseSpinBox->value(),ui->automineMoveDelaySpinBox->value(),
                                                                ui->automineMoveDuringSpinBox->value(), m_toolsDurList[ui->toolsComboBox->currentText()].first,
                                                                 m_toolsDurList[ui->toolsComboBox->currentText()].second, ui->automineSequenceEdit->text());

    if(val)
    {
        if(configureSuccess)
        {
            ui->executeMine->setText("Stop");
            m_automineStatus->show();
            m_automineProcessManager->run();
            ui->automineGroupBox->setEnabled(false);
        }
        else
        {
            QMessageBox::critical(this,"Keys are not recognized or bad values","Forward or Primary Action or Secondary Action ingame keys that you provided are not supported \
                                    by this program, or values are incorrect. Sorry for the inconvenience.");
            ui->executeMine->setChecked(false);
        }
    }
    else
    {
        ui->executeMine->setText("Execute");
        m_automineStatus->hide();
        m_automineProcessManager->stop(); // we want to stop even if configuration failed
        ui->automineGroupBox->setEnabled(true);
    }
}

void MainWindow::onAutorunExecTrigger()
{
    if(ui->executeRun->isChecked())
    {
        ui->executeRun->setChecked(false);
    }
    else
    {
        ui->executeRun->setChecked(true);
    }
}

void MainWindow::onAutodriveExecTrigger()
{
    if(ui->executeDrive->isChecked())
    {
        ui->executeDrive->setChecked(false);
    }
    else
    {
        ui->executeDrive->setChecked(true);
    }
}

void MainWindow::onAutotrackExecTrigger()
{
    if(ui->executeTrack->isChecked())
    {
        ui->executeTrack->setChecked(false);
    }
    else
    {
        ui->executeTrack->setChecked(true);
    }
}

void MainWindow::onAutomineExecTrigger()
{
    if(ui->executeMine->isChecked())
    {
        ui->executeMine->setChecked(false);
    }
    else
    {
        ui->executeMine->setChecked(true);
    }
}

void MainWindow::onKeyPushButtonSet(QString modifiers, QString key, quint32 modNative, quint32 keyNative, bool isMousePressed)
{
    QString id = sender()->property("id").toString();
    QSettings settings("settings.ini", QSettings::IniFormat);
    settings.setValue(id+"/mod", modifiers);
    settings.setValue(id+"/key", key);
    settings.setValue(id+"/modNative", modNative);
    settings.setValue(id+"/keyNative", keyNative);
    settings.setValue(id+"/isMouse", isMousePressed);

    if(sender()->property("type").toInt() == 2)
    {
        if(id == "autorunWindowsKey")
            autorunGlobalShortcut.setShortcutAndEnable(modifiers+key);
        else if(id == "autodriveWindowsKey")
            autodriveGlobalShortcut.setShortcutAndEnable(modifiers+key);
        else if(id == "autotrackWindowsKey")
            autotrackGlobalShortcut.setShortcutAndEnable(modifiers+key);
        else if(id == "automineWindowsKey")
            automineGlobalShortcut.setShortcutAndEnable(modifiers+key);
    }
}

void MainWindow::savePreset(PresetSwitchWidget::AutoType autotype, unsigned int currentIndex, QString name)
{
    switch (autotype) {
    case PresetSwitchWidget::AutoType::Autorun:
        {
            QSettings settings("autorunPresets.ini", QSettings::IniFormat);
            settings.setValue(QString::number(currentIndex)+"/name",name);
            settings.setValue(QString::number(currentIndex)+"/runDuring",ui->autorunRunSpinBox->value());
            settings.setValue(QString::number(currentIndex)+"/walkDuring",ui->autorunWalkSpinBox->value());
        }
        break;
    case PresetSwitchWidget::AutoType::Autotrack:
        {
            QSettings settings("autotrackPresets.ini", QSettings::IniFormat);
            settings.setValue(QString::number(currentIndex)+"/name",name);
            settings.setValue(QString::number(currentIndex)+"/runDuring",ui->autotrackRunSpinBox->value());
            settings.setValue(QString::number(currentIndex)+"/crouchDuring",ui->autotrackCrouchSpinBox->value());
        }
        break;
    case PresetSwitchWidget::AutoType::Automine:
        {
            QSettings settings("autominePresets.ini", QSettings::IniFormat);
            settings.setValue(QString::number(currentIndex)+"/name",name);
            settings.setValue(QString::number(currentIndex)+"/hitSequence",ui->automineSequenceEdit->text());
            settings.setValue(QString::number(currentIndex)+"/tool",ui->toolsComboBox->currentText());
            settings.setValue(QString::number(currentIndex)+"/hitDuring",ui->automineHitSpinBox->value());
            settings.setValue(QString::number(currentIndex)+"/pauseDuring",ui->autominePauseSpinBox->value());
            settings.setValue(QString::number(currentIndex)+"/moveDelay",ui->automineMoveDelaySpinBox->value());
            settings.setValue(QString::number(currentIndex)+"/moveDuring",ui->automineMoveDuringSpinBox->value());
        }
        break;
    default:
        break;
    }
}

void MainWindow::setAutorunValues(double runDuring, double walkDuring)
{
    ui->autorunRunSpinBox->setValue(runDuring);
    ui->autorunWalkSpinBox->setValue(walkDuring);
}

void MainWindow::setAutotrackValues(double runDuring, double crouchDuring)
{
    ui->autotrackRunSpinBox->setValue(runDuring);
    ui->autotrackCrouchSpinBox->setValue(crouchDuring);
}

void MainWindow::setAutomineValues(QString sequence, QString tool, double hitDuring, double pauseDuring, double moveDelay, double moveDuring)
{
    ui->automineSequenceEdit->setText(sequence);
    ui->toolsComboBox->setCurrentText(tool);
    ui->automineHitSpinBox->setValue(hitDuring);
    ui->autominePauseSpinBox->setValue(pauseDuring);
    ui->automineMoveDelaySpinBox->setValue(moveDelay);
    ui->automineMoveDuringSpinBox->setValue(moveDuring);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings("settings.ini", QSettings::IniFormat);
    settings.setValue("presetsLastIndex/autorun", ui->autorunPresetWidget->m_current);
    settings.setValue("presetsLastIndex/autotrack", ui->autotrackPresetWidget->m_current);
    settings.setValue("presetsLastIndex/automine", ui->autominePresetWidget->m_current);

    QMainWindow::closeEvent(event);
}

void MainWindow::refreshToolsComboBox()
{
    QString savedToolName = ui->toolsComboBox->currentText();
    m_toolsDurList = toolsDialog->getList();
    ui->toolsComboBox->clear();
    ui->toolsComboBox->addItems(m_toolsDurList.keys());
    ui->toolsComboBox->setCurrentText(savedToolName);
}
