#include "tablewidget.h"

TableWidget::TableWidget(int axis, QString title) :
    DashboardWidget(axis, title)
{
    connect(paintTimer, &QTimer::timeout, this, &TableWidget::paintWidget);
    pTable = new QTableWidget();
    pRowToWriteData = 0;

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

    QStringList nameOfColumns;
    nameOfColumns.append("time");
    for (int i = 0; i != axis; ++i) {
        nameOfColumns.append(QString::number(i+1)+" value");
    }

    pTable->setHorizontalHeaderLabels(nameOfColumns);
}

void TableWidget::paintWidget()
{
    int currentNumOfRows = pTable->rowCount();
    if (currentNumOfRows < pMaxOfRows) {
        pTable->insertRow(currentNumOfRows);
    }
    QString currentTime = QTime::currentTime().toString();
    QTableWidgetItem *firstItem = new QTableWidgetItem(currentTime);
    firstItem->setFlags(firstItem->flags() ^ Qt::ItemIsEditable);
    pTable->setItem(pRowToWriteData, 0, firstItem);
    for (int i = 1; i != axis + 1; ++i) {
        QTableWidgetItem *newItem = new QTableWidgetItem(QString::number(data.at(i - 1)));
        newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
        pTable->setItem(pRowToWriteData, i, newItem);
    }

    if (pRowToWriteData == pMaxOfRows - 1) {
        pRowToWriteData = 0;
    } else {
        ++pRowToWriteData;
    }
}

const int TableWidget::pMaxOfRows = 10;
