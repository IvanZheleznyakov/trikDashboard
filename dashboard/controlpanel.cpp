#include "controlpanel.h"

ControlPanel::ControlPanel()
{
    layout.addWidget(&labelMessage, 0, 0);
    layout.addWidget(&lineEdit, 1, 0);
    layout.addWidget(&sendButton, 1, 1);
    setLayout(&layout);

    sendButton.setText("command");
    connect(&sendButton, SIGNAL(clicked()), this, SLOT(pushCommandButton()));
}

void ControlPanel::pushCommandButton()
{
    emit readyCommand(lineEdit.text());
    lineEdit.setText("");
}

void ControlPanel::setLabelText(QString text)
{
    labelMessage.setText(text);
}
