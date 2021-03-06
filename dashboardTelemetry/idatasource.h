#pragma once

#include <QObject>
#include <QVector>

class IDataSource : public QObject
{
    Q_OBJECT

public:
    virtual void updateData(QVector<float> submittedData) = 0;

signals:
    void recieveNewData(QVector<float> updates);

public:
    QVector<float> getData() const;

    QString getName() const;
    void setName(const QString &value);

protected:
    void setData(const QVector<float> &value);

private:
    QVector<float> mData;
    QString name;
};
