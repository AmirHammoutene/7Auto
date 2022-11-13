#ifndef PRESETSWITCHWIDGET_H
#define PRESETSWITCHWIDGET_H

#include <QWidget>

namespace Ui {
class PresetSwitchWidget;
}

class PresetSwitchWidget : public QWidget
{
    Q_OBJECT

public:
    enum class AutoType
    {
        Autorun, Autotrack, Automine, Undefined
    };
    explicit PresetSwitchWidget(QWidget *parent = nullptr);
    ~PresetSwitchWidget();
    unsigned int m_count = 1;
    unsigned int m_current = 0;
    AutoType m_autotype = AutoType::Undefined;
    void load(unsigned int index);
    void initialize(AutoType autotype, unsigned int lastIndex);
public slots:
    void add();
    void saveCurrent();
    void next();
    void previous();
signals:
    void saveRequest(PresetSwitchWidget::AutoType autotype, unsigned int currentIndex, QString name);
    void sendAutorunValues(double runDuring, double walkDuring);
    void sendAutotrackValues(double runDuring, double crouchDuring);
    void sendAutomineValues(QString sequence, QString tool, double hitDuring, double pauseDuring, double moveDelay, double moveDuring);
private:
    Ui::PresetSwitchWidget *ui;
};

#endif // PRESETSWITCHWIDGET_H
