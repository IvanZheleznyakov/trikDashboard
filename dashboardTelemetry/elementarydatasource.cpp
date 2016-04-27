#include "elementarydatasource.h"

ElementaryDataSource::ElementaryDataSource(QString name)
{
    setName(name);
}

void ElementaryDataSource::updateData(QVector<float> submittedData)
{
    setData(submittedData);
    emit this->recieveNewData(submittedData);
}
