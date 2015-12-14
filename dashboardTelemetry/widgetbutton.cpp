#include "widgetbutton.h"

WidgetButton::WidgetButton(QString mSensorName) :
    QPushButton(),
    mSensorName(mSensorName)
{

}

QString WidgetButton::getSensorName()
{
    return mSensorName;
}
