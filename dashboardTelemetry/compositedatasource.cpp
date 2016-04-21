#include "compositedatasource.h"

CompositeDataSource::CompositeDataSource(QVector<IDataSource *> dataSources)
{
    for (int i = 0; i != dataSources.count(); ++i)
    {
        connect(dataSources.at(i), &IDataSource::recieveNewData, this, &IDataSource::refreshData);
    }
}

void CompositeDataSource::updateData(QVector<float> submittedData)
{
    setData(submittedData);
    emit this->recieveNewData(submittedData);
}

void CompositeDataSource::refreshData(QVector<float> submittedData)
{
    submittedData.clear();
    emit this->recieveNewData(getData());
}
