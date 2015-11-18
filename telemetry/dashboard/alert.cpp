#include "alert.h"

Alert::Alert(QString title) :
    title(title)
{
    alertButton = new QPushButton();
    alertButton->setStyleSheet("QPushButton { background-color: rgb(170, 170, 170); border-style: outset; border-width: 0.5px; border-radius: 5px; border-color: beige; padding: 4px;}"
                         "QPushButton:pressed { background-color: rgb(200, 200, 200); border-style: inset; }");

    connect(alertButton, SIGNAL(clicked()), this, SLOT(actionTriggered());

    alertButton->setText(title);

    isShowed = false;
}

void Alert::actionTriggered()
{
    if (!isShowed) {
        showOptions();
    } else {
        hideOptions();
    }
}

void Alert::showOptions()
{

}
