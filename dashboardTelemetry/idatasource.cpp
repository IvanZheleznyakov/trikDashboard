#include "idatasource.h"

QVector<float> IDataSource::getData() const
{
    return mData;
}

void IDataSource::setData(const QVector<float> &value)
{
    mData = value;
}

QString IDataSource::getName() const
{
    return name;
}

void IDataSource::setName(const QString &value)
{
    name = value;
}

