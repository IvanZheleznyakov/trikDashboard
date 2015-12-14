#include "widgetbutton.h"

WidgetButton::WidgetButton(QString text, QString mSensorName) :
    QPushButton(),
    mSensorName(mSensorName)
{
    WidgetButton::setText(text);
    WidgetButton::setStyleSheet("QPushButton { background-color: rgb(170, 170, 170); border-style: outset; border-width: 0.5px; border-radius: 5px; border-color: beige; padding: 4px;}"
                                "QPushButton:pressed { background-color: rgb(200, 200, 200); border-style: inset; }");
}

QString WidgetButton::getSensorName()
{
    return mSensorName;
}
