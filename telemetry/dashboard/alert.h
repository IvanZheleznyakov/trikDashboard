#pragma once

#include "widgetslib_global.h"
#include <QWidget>
#include <QPushButton>
#include <QDockWidget>
#include <QLineEdit>
#include <QLabel>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QMessageBox>

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
    void minValueIsChanged();
    void maxValueIsChanged();
    void checkCriticalValues(QVector<float> values);

private:
    QString title;
    QPushButton *alertButton;
    float minValue;
    float maxValue;
    bool isShowed;
    QLineEdit *minValueText;
    QLabel *minValueLabel;
    QLineEdit *maxValueText;
    QLabel *maxValueLabel;
    QDockWidget *dockWidget;
    void showCriticalAlert();
};
