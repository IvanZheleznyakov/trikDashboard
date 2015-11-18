#pragma once

#include "widgetslib_global.h"
#include <QWidget>
#include <QPushButton>

class Alert : public QObject
{
    Q_OBJECT

public:
    explicit Alert(QString title);
    QPushButton *button();

public slots:
    void actionTriggered();
    void showOptions();
    void hideOptions();

private:
    QString title;
    QPushButton *alertButton;
    double minValue;
    double maxValue;
    bool isShowed;
};
