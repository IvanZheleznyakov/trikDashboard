#pragma once

#include "idatasource.h"
#include <QVector>

class ElementaryDataSource : public IDataSource
{
public:
    ElementaryDataSource();

public slots:
    void refreshData(QVector<float> submittedData);

public:
    void updateData(QVector<float> submittedData);
};

