#include "alert.h"

Alert::Alert(QString title) :
    title(title)
{
    alertButton = new QPushButton();
    alertButton->setStyleSheet("QPushButton { background-color: rgb(170, 170, 170); border-style: outset; border-width: 0.5px; border-radius: 5px; border-color: beige; padding: 4px;}"
                         "QPushButton:pressed { background-color: rgb(200, 200, 200); border-style: inset; }");

    connect(alertButton, SIGNAL(clicked()), this, SLOT(actionTriggered()));

    alertButton->setText("Alert for " + title);

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
    alertOptionsLayout->setContentsMargins(10, 10, 10, 1000);
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
    minValue = minValueText->text().toFloat();
}

void Alert::maxValueIsChanged()
{
    maxValue = maxValueText->text().toFloat();
}

void Alert::checkCriticalValues(QVector<float> values)
{
    for (int i = 0; i != values.size(); ++i) {
        if (values.at(i) < minValue || values.at(i) > maxValue) {
            showCriticalAlert();
        }
    }
}

void Alert::showCriticalAlert()
{
    QMessageBox::critical(0,
                          "Attention!",
                          "Some data in " + title + " are critical!",
                          QMessageBox::Ok | QMessageBox::Escape);
}
