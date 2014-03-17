#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>

class ControlPanel : public QWidget
{
    Q_OBJECT
public:
    explicit ControlPanel();
    void setLabelText(QString text);

signals:
    void readyCommand(QString);

private slots:
    void pushCommandButton();

private:
    QLabel labelMessage;
    QLineEdit lineEdit;
    QPushButton sendButton;
    QGridLayout layout;
};
