#include "elementarydatasource.h"

ElementaryDataSource::ElementaryDataSource()
{

}

void ElementaryDataSource::readData(QVector<float> submittedData)
{
    setData(submittedData);
}
