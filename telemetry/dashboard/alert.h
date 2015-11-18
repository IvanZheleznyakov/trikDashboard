#pragma once

#include "widgetslib_global.h"
#include <QWidget>
#include <QPushButton>
#include <QDockWidget>
#include <QLineEdit>
#include <QLabel>

class Alert : public QObject
{
    Q_OBJECT

public:
    Alert(QString title);
    QPushButton *button();

signals:
    void newDockWidget(QDockWidget *);

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
    QLineEdit *minValueText;
    QLabel *minValueLabel;
    QLineEdit *maxValueText;
    QLabel *maxValueLabel;
};
