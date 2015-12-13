#include "idatasource.h"

QVector<float> IDataSource::getData() const
{
    return data;
}

void IDataSource::setData(const QVector<float> &value)
{
    data = value;
}
