#include "toolshitdurationsdialog.h"
#include "ui_toolshitdurationsdialog.h"
#include <QSettings>

ToolsHitDurationsDialog::ToolsHitDurationsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToolsHitDurationsDialog)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnWidth(0,280);
    ui->tableWidget->setColumnWidth(1,150);
    ui->tableWidget->setColumnWidth(2,150);

    connect(ui->tableWidget, &QTableWidget::itemChanged,this, &ToolsHitDurationsDialog::checkChangedItem);
    connect(this, &QDialog::accepted,this, &ToolsHitDurationsDialog::onAccepted);
    connect(ui->pushButton, &QPushButton::released,this, &ToolsHitDurationsDialog::appendEntry);
}

ToolsHitDurationsDialog::~ToolsHitDurationsDialog()
{
    delete ui;
}

QMap<QString, QPair<double, double> > ToolsHitDurationsDialog::getList()
{
    QMap<QString, QPair<double, double> > returnedValue;
    QSettings toolsDurations("toolsHitDurations.ini", QSettings::IniFormat);
    for(const QString &group : toolsDurations.childGroups())
    {
        QPair<double, double> durations;
        durations.first = toolsDurations.value(group+"/simple").toDouble();
        durations.second = toolsDurations.value(group+"/power").toDouble();
        returnedValue.insert(group, durations);
    }

    return returnedValue;
}

void ToolsHitDurationsDialog::showAndFillTable()
{
    ui->tableWidget->setRowCount(0);
    QMap<QString, QPair<double, double> > entryList = getList();

    QMapIterator<QString, QPair<double, double>> itMap(entryList);
    while (itMap.hasNext())
    {
        itMap.next();
        int rowNum = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowNum);
        ui->tableWidget->setItem(rowNum,0,new QTableWidgetItem(itMap.key()));
        ui->tableWidget->setItem(rowNum,1,new QTableWidgetItem(QString::number(itMap.value().first)));
        ui->tableWidget->setItem(rowNum,2,new QTableWidgetItem(QString::number(itMap.value().second)));
    }
    show();
}

void ToolsHitDurationsDialog::checkChangedItem(QTableWidgetItem *item)
{
    if(item->column() == 0 )
        return;
    ui->tableWidget->blockSignals(true);
    double numVal = item->text().toDouble();
    ui->tableWidget->setItem(item->row(),item->column(),new QTableWidgetItem(QString::number(numVal < 0 ? 0. : numVal)));
    ui->tableWidget->blockSignals(false);
}

void ToolsHitDurationsDialog::onAccepted()
{
    QSettings toolsDurations("toolsHitDurations.ini", QSettings::IniFormat);

    for(int row = 0; row < ui->tableWidget->rowCount(); row++)
    {
        QString toolName = ui->tableWidget->item(row,0)->text();
        toolsDurations.setValue(toolName+"/simple", ui->tableWidget->item(row,1)->text().toDouble());
        toolsDurations.setValue(toolName+"/power", ui->tableWidget->item(row,2)->text().toDouble());
    }

    emit iniFileChanged();
}

void ToolsHitDurationsDialog::appendEntry()
{
    int rowNum = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(rowNum);
    ui->tableWidget->setItem(rowNum,0,new QTableWidgetItem("Unnamed tool"));
    ui->tableWidget->setItem(rowNum,1,new QTableWidgetItem(QString::number(0.)));
    ui->tableWidget->setItem(rowNum,2,new QTableWidgetItem(QString::number(0.)));
    ui->tableWidget->setCurrentCell(rowNum,0);
}
