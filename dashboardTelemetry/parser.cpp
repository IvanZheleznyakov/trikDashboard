#include "parser.h"
#include "elementarydatasource.h"
#include <QStringList>
#include <QVector>

Parser::Parser()
{
    connect(this, &Parser::messageIsParsed, this, &Parser::sendData);
}

void Parser::parseMessage(QString message)
{
    QStringList devices = message.split(";", QString::SkipEmptyParts);
    for (int i = 0; i != devices.count(); ++i) {
        QStringList info = devices.at(i).split(":", QString::SkipEmptyParts);
        QVector<float> values;
        QStringList data = info.at(1).split("*", QString::SkipEmptyParts);
        for (int j = 0; j != data.count(); ++j) {
            float x = data.at(j).toFloat();
            values << x;
        }

        QString const deviceName = info.at(0);

        if (!map.contains(deviceName)) {
            ElementaryDataSource *newDataSource = new ElementaryDataSource();
            addDataSource(deviceName, newDataSource);
        }

        emit messageIsParsed(deviceName, values);
    }
}

void Parser::sendData(QString deviceName, QVector<float> values)
{
    map[deviceName]->updateData(values);
}

void Parser::addDataSource(QString deviceName, IDataSource *newDataSource)
{
    map.insert(deviceName, newDataSource);
}
