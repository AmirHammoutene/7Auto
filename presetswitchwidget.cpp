#include "presetswitchwidget.h"
#include "ui_presetswitchwidget.h"
#include <QSettings>

PresetSwitchWidget::PresetSwitchWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PresetSwitchWidget)
{
    ui->setupUi(this);

    m_autotype = PresetSwitchWidget::AutoType::Undefined;

    connect(ui->pushButton_add,&QPushButton::released, this, &PresetSwitchWidget::add);
    connect(ui->lineEdit, &QLineEdit::editingFinished, this, &PresetSwitchWidget::saveCurrent);
    connect(ui->pushButton_next, &QPushButton::released, this, &PresetSwitchWidget::next);
    connect(ui->pushButton_previous, &QPushButton::released, this, &PresetSwitchWidget::previous);
}

PresetSwitchWidget::~PresetSwitchWidget()
{
    delete ui;
}

void PresetSwitchWidget::load(unsigned int index)
{
    m_current = index;
    QString fileName;
    switch (m_autotype) {
    case PresetSwitchWidget::AutoType::Autorun:
        fileName = "autorunPresets.ini";
        break;
    case PresetSwitchWidget::AutoType::Autotrack:
        fileName = "autotrackPresets.ini";
        break;
    case PresetSwitchWidget::AutoType::Automine:
        fileName = "autominePresets.ini";
        break;
    default:
        return;
    }
    QSettings settings(fileName, QSettings::IniFormat);
    ui->lineEdit->setText(settings.value(QString::number(m_current)+"/name").toString());

    switch (m_autotype) {
    case PresetSwitchWidget::AutoType::Autorun:
        emit sendAutorunValues(settings.value(QString::number(m_current)+"/runDuring").toDouble(),
                               settings.value(QString::number(m_current)+"/walkDuring").toDouble());
        break;
    case PresetSwitchWidget::AutoType::Autotrack:
        emit sendAutotrackValues(settings.value(QString::number(m_current)+"/runDuring").toDouble(),
                               settings.value(QString::number(m_current)+"/crouchDuring").toDouble());
        break;
    case PresetSwitchWidget::AutoType::Automine:
        emit sendAutomineValues(settings.value(QString::number(m_current)+"/hitSequence", "2211").toString(),
                                settings.value(QString::number(m_current)+"/tool", "Stone Axe").toString(),
                               settings.value(QString::number(m_current)+"/hitDuring").toDouble(),
                                settings.value(QString::number(m_current)+"/pauseDuring").toDouble(),
                                settings.value(QString::number(m_current)+"/moveDelay").toDouble(),
                                settings.value(QString::number(m_current)+"/moveDuring").toDouble());
        break;
    default:
        break;
    }
}

void PresetSwitchWidget::initialize(AutoType autotype, unsigned int lastIndex)
{
    m_autotype = autotype;
    QString fileName;
    switch (m_autotype) {
    case PresetSwitchWidget::AutoType::Autorun:
        fileName = "autorunPresets.ini";
        break;
    case PresetSwitchWidget::AutoType::Autotrack:
        fileName = "autotrackPresets.ini";
        break;
    case PresetSwitchWidget::AutoType::Automine:
        fileName = "autominePresets.ini";
        break;
    default:
        return;
    }
    QSettings settings(fileName, QSettings::IniFormat);
    m_count =  settings.childGroups().count() == 0 ? 1 : settings.childGroups().count();

    load(lastIndex);
}

void PresetSwitchWidget::add()
{
    m_count++;
    m_current = m_count-1;
    ui->lineEdit->setText("");
    ui->lineEdit->setFocus(Qt::MouseFocusReason);
}

void PresetSwitchWidget::saveCurrent()
{
    emit saveRequest(m_autotype, m_current, ui->lineEdit->text());
}

void PresetSwitchWidget::next()
{
    if(m_current< m_count-1)
        load(m_current+1);
    else
        load(0);
}

void PresetSwitchWidget::previous()
{
    if(m_current > 0)
        load(m_current-1);
    else
        load(m_count-1);
}
