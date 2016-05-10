#pragma once

#include "idatasource.h"
#include <QVector>

class ElementaryDataSource : public IDataSource
{
    Q_OBJECT

public:
    ElementaryDataSource(QString name);

public:
    void updateData(QVector<float> submittedData);
};

