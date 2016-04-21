#include "elementarydatasource.h"

ElementaryDataSource::ElementaryDataSource()
{

}

void ElementaryDataSource::updateData(QVector<float> submittedData)
{
    setData(submittedData);
    emit this->recieveNewData(submittedData);
}

void ElementaryDataSource::refreshData(QVector<float> submittedData)
{
    submittedData.clear();
    emit this->recieveNewData(getData());
}
