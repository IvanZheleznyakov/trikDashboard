#pragma once

#include <QObject>
#include <QVector>

class IDataSource : public QObject
{
    Q_OBJECT

public:
    virtual void updateData(QVector<float> submittedData) = 0;

signals:
    void recieveNewData();

protected:
    QVector<float> getData() const;
    void setData(const QVector<float> &value);

private:
    QVector<float> mData;
};
