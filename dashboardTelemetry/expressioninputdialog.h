#pragma once

#include <QDialog>
#include <QObject>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class ExpressionInputDialog : public QDialog
{
    Q_OBJECT
public:
    ExpressionInputDialog();

private slots:
    void okButtonIsClicked();
    void cancelButtonIsClicked();
    void textIsChanged();

private:
    QLabel *nameLabel;
    QLabel *expressionLabel;
    QLineEdit *nameLineEdit;
    QLineEdit *expressionLineEdit;
    QPushButton *okButton;
    QPushButton *cancelButton;
};
