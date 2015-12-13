#pragma once

#include <QObject>
#include <QVector>

class IDataSource : public QObject
{
    Q_OBJECT

public:
    void readData(QVector<float> submittedData);
protected:
    QVector<float> data;
};
