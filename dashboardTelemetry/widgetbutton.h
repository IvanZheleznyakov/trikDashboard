#pragma once

#include <QPushButton>

class WidgetButton : public QPushButton
{
public:
    WidgetButton(QString text, QString mSensorName);
    QString getSensorName();

private:
    QString mSensorName;
};
