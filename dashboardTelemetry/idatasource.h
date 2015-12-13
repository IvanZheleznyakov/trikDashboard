#pragma once

#include <QObject>
#include <QVector>

class IDataSource : public QObject
{
    Q_OBJECT

protected:
    QVector<double> data;
};
