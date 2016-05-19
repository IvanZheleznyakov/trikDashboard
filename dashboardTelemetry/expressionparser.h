#pragma once

#include <QObject>
#include "idatasource.h"

class ExpressionParser : public QObject
{
    Q_OBJECT
public:
    ExpressionParser();
    QVector<float> parseExpression(QMap<QString, IDataSource *> map, QString expression);
};
