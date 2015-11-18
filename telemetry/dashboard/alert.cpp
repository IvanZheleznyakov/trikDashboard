#include "alert.h"

Alert::Alert(QString title) :
    title(title)
{
    alertButton = new QPushButton();
    alertButton->setStyleSheet("QPushButton { background-color: rgb(170, 170, 170); border-style: outset; border-width: 0.5px; border-radius: 5px; border-color: beige; padding: 4px;}"
                         "QPushButton:pressed { background-color: rgb(200, 200, 200); border-style: inset; }");

    connect(alertButton, SIGNAL(clicked()), this, SLOT(actionTriggered()));

    title = "Alert for " + title;
    alertButton->setText(title);

    //temp values
    minValue = 0;
    maxValue = 100;

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
    isShowed = true;

    dockWidget = new QDockWidget();
    dockWidget->setObjectName(title);
    dockWidget->setFeatures(dockWidget->features() | QDockWidget::DockWidgetClosable);
    dockWidget->setFeatures(dockWidget->features() | QDockWidget::DockWidgetMovable);
    dockWidget->setFeatures(dockWidget->features() | QDockWidget::DockWidgetFloatable);
    dockWidget->setAllowedAreas(Qt::AllDockWidgetAreas);
    dockWidget->setWindowTitle(title);

    emit newDockWidget(dockWidget);

    QGroupBox *alertOptions = new QGroupBox();
    QVBoxLayout *alertOptionsLayout = new QVBoxLayout();
    minValueLabel = new QLabel("Enter min value");
    minValueText = new QLineEdit(QString::number(minValue));
    connect(minValueText, SIGNAL(editingFinished()), this, SLOT(minValueIsChanged()));

    maxValueLabel = new QLabel("Enter max value");
    maxValueText = new QLineEdit(QString::number(maxValue));
    connect(maxValueText, SIGNAL(editingFinished()), this, SLOT(maxValueIsChanged()));

    alertOptionsLayout->addWidget(minValueLabel);
    alertOptionsLayout->addWidget(minValueText);
    alertOptionsLayout->addWidget(maxValueLabel);
    alertOptionsLayout->addWidget(maxValueText);
    alertOptions->setLayout(alertOptionsLayout);

    dockWidget->setWidget(alertOptions);
}

void Alert::hideOptions()
{
    isShowed = false;

    dockWidget->deleteLater();
}

QPushButton *Alert::button()
{
    return alertButton;
}

void Alert::minValueIsChanged()
{
    minValue = minValueText->text().toDouble();
}

void Alert::maxValueIsChanged()
{
    maxValue = maxValueText->text().toDouble();
}
