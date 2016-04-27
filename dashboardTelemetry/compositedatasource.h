#pragma once

#include "idatasource.h"
#include <QVector>

class CompositeDataSource : public IDataSource
{
    Q_OBJECT

public:
    CompositeDataSource(QString name, QString expression, QVector<IDataSource *> dataSources);

signals:
    void refreshData(QString name, QString expression);

public slots:
    void requestToRefreshData(QVector<float> submittedData);

public:
    void updateData(QVector<float> submittedData);

    QString expression() const;
    void setExpression(const QString &expression);

private:
    QString mExpression;
};
