#pragma once

#include "idatasource.h"
#include <QVector>

class ElementaryDataSource : public IDataSource
{
public:
    ElementaryDataSource();

public:
    void readData(QVector<float> submittedData);

};

