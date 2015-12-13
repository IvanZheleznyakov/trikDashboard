#pragma once

#include <QObject>
#include <QVector>

class IDataSource : public QObject
{
    Q_OBJECT

public:
    void readData(QVector<double> submittedData);
protected:
    QVector<double> data;
};
