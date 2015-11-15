#include "tablewidget.h"

TableWidget::TableWidget(int axis, QString title) :
    DashboardWidget(axis, title)
{
    connect(paintTimer, &QTimer::timeout, this, &TableWidget::paintWidget);
    pTable = new QTableWidget();

    init();

    pTable->setWindowTitle(title);
    layout->addWidget(pTable);
    setLayout(layout);
}

void TableWidget::init()
{
    this->setInterval(40);

    pTable->setRowCount(1);
    pTable->setColumnCount(axis + 1);
}

void TableWidget::paintWidget()
{
    QString currentTime = QTime::currentTime().toString();
    QTableWidgetItem *firstItem = new QTableWidgetItem(currentTime);
    firstItem->setFlags(firstItem->flags() ^ Qt::ItemIsEditable);
    pTable->setItem(0, 0, firstItem);
    for (int i = 1; i != axis + 1; ++i)
    {
        pTable->setItem(0, i, new QTableWidgetItem(QString::number(data.at(i - 1))));
    }
}

const int TableWidget::pMaxOfRows = 10;
