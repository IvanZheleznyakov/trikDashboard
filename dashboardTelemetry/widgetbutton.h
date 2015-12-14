#pragma once

#include <QPushButton>

class WidgetButton : public QPushButton
{
public:
    WidgetButton(QString text, QString mSensorName);
    QString getSensorName();
    bool isActive();

private slots:
    void buttonIsClicked();

private:
    QString mSensorName;
    bool mWidgetIsActive;
};
