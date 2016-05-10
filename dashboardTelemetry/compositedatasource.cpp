#include "compositedatasource.h"

CompositeDataSource::CompositeDataSource(QString name, QString expression, QVector<IDataSource *> dataSources)
{
    setName(name);
    setExpression(expression);
    for (int i = 0; i != dataSources.count(); ++i)
    {
        connect(dataSources.at(i), &IDataSource::recieveNewData, this, &CompositeDataSource::requestToRefreshData);
    }
}

void CompositeDataSource::updateData(QVector<float> submittedData)
{
    setData(submittedData);
    emit this->recieveNewData(submittedData);
}

QString CompositeDataSource::expression() const
{
    return mExpression;
}

void CompositeDataSource::setExpression(const QString &expression)
{
    mExpression = expression;
}


void CompositeDataSource::requestToRefreshData(QVector<float> submittedData)
{
    submittedData.clear();
    emit this->refreshData(getName(), mExpression);
}
