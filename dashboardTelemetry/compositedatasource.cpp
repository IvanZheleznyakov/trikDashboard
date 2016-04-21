#include "compositedatasource.h"

CompositeDataSource::CompositeDataSource(QVector<IDataSource *> dataSources)
{
    for (int i = 0; i != dataSources.count(); ++i)
    {
        connect(dataSources.at(i), &IDataSource::recieveNewData, this, &IDataSource::recieveNewData);
    }
}

void CompositeDataSource::updateData(QVector<float> submittedData)
{
    setData(submittedData);
    emit this->recieveNewData(submittedData);
}
