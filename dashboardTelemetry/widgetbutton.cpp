#include "widgetbutton.h"

WidgetButton::WidgetButton(QString text, QString mSensorName) :
    QPushButton(),
    mSensorName(mSensorName)
{
    WidgetButton::setText(text);
}

QString WidgetButton::getSensorName()
{
    return mSensorName;
}
