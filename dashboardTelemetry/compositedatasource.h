#pragma once

#include "idatasource.h"
#include <QVector>

class CompositeDataSource : public IDataSource
{
public:
    CompositeDataSource(QVector<IDataSource *> dataSources);

public slots:
    void refreshData(QVector<float> submittedData);

public:
    void updateData(QVector<float> submittedData);
};
