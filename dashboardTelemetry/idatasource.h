#pragma once

#include <QObject>
#include <QVector>

class IDataSource : public QObject
{
    Q_OBJECT

public:
    virtual void readData(QVector<float> submittedData) = 0;

protected:
    QVector<float> getData() const;
    void setData(const QVector<float> &value);

private:
    QVector<float> data;
};
