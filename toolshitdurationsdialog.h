#ifndef TOOLSHITDURATIONSDIALOG_H
#define TOOLSHITDURATIONSDIALOG_H

#include <QTableWidget>
#include <QDialog>

namespace Ui {
class ToolsHitDurationsDialog;
}

class ToolsHitDurationsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ToolsHitDurationsDialog(QWidget *parent = nullptr);
    ~ToolsHitDurationsDialog();
    QMap<QString, QPair<double,double> > getList();
public slots:
    void showAndFillTable();
    void checkChangedItem(QTableWidgetItem *item);
    void onAccepted();
    void appendEntry();
signals:
    void iniFileChanged();
private:
    Ui::ToolsHitDurationsDialog *ui;
};

#endif // TOOLSHITDURATIONSDIALOG_H
