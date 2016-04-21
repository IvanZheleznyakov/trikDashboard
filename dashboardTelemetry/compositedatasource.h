#pragma once

#include "idatasource.h"
#include <QVector>

class CompositeDataSource : public IDataSource
{
public:
    CompositeDataSource(QVector<IDataSource *> dataSources);

public:
    void updateData(QVector<float> submittedData);
};
