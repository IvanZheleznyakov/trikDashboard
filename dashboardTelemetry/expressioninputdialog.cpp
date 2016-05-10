#include "expressioninputdialog.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

ExpressionInputDialog::ExpressionInputDialog(): QDialog()
{
    setWindowTitle("Input expression");
    nameLabel = new QLabel("Name: ", this);
    expressionLabel = new QLabel("Expression: ", this);
    nameLineEdit = new QLineEdit();
    expressionLineEdit = new QLineEdit();
    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");
    okButton->setEnabled(false);

    connect(okButton, QPushButton::clicked, this, ExpressionInputDialog::okButtonIsClicked);
    connect(cancelButton, QPushButton::clicked, this, ExpressionInputDialog::close);
    connect(nameLineEdit, QLineEdit::textChanged, this, ExpressionInputDialog::textIsChanged);
    connect(expressionLineEdit, QLineEdit::textChanged, this, ExpressionInputDialog::textIsChanged);

    QHBoxLayout *nameLayout = new QHBoxLayout;
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(nameLineEdit);
    QHBoxLayout *expressionLayout = new QHBoxLayout;
    expressionLayout->addWidget(expressionLabel);
    expressionLayout->addWidget(expressionLineEdit);
    QVBoxLayout *inputLayout = new QVBoxLayout;
    inputLayout->addLayout(nameLayout);
    inputLayout->addLayout(expressionLayout);
    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(cancelButton);
    buttonsLayout->addWidget(okButton);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(inputLayout);
    mainLayout->addLayout(buttonsLayout);
}

void ExpressionInputDialog::okButtonIsClicked()
{
    emit sendDataToExpression(nameLineEdit->text(), expressionLineEdit->text());
    this->close();
}

void ExpressionInputDialog::cancelButtonIsClicked()
{
    this->close();
}

void ExpressionInputDialog::textIsChanged()
{
    okButton->setEnabled(!nameLineEdit->text().isEmpty() && !expressionLineEdit->text().isEmpty());
}
