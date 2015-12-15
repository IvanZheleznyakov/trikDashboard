#pragma once

#include "idatasource.h"

#include "widgetslib_global.h"
#include <QWidget>
#include <QVector>
#include <QTimer>
#include <QGridLayout>
#include <QMenu>
#include <QLabel>

class WIDGETSLIBSHARED_EXPORT ISensorWidget : public QWidget
{

public:
    explicit ISensorWidget(int mAxis, QString mTitle, int mTimerInterval, QWidget *parent = 0);

    IDataSource *getDataSource() const;

protected:
    void setDataSource(IDataSource *dataSource);

    QVector<QColor> getColors() const;
    void setColors(const QVector<QColor> &value);

    QGridLayout *getLayout() const;
    void setMLayout(QGridLayout *value);

    QLabel *getTitleLabel() const;
    void setTitleLabel(QLabel *value);

    QMenu *getWidgetMenu() const;
    void setWidgetMenu(QMenu *value);

    QTimer *getPaintTimer() const;
    void setPaintTimer(QTimer *value);

    QString getTitle() const;
    void setTitle(const QString &value);

    int getAxis() const;
    void setAxis(int value);

    int getTimerInterval() const;
    void setTimerInterval(int value);

public slots:
     void startPaint();
     void stopPaint();
     void updateData(QVector <float> updates);
     void setInterval(int interval);
     void subscribeToDataSource(IDataSource *dataSource);
    virtual void paintWidget() = 0;
    virtual void init() = 0;

private:
    IDataSource *mDataSource;
    QVector<QColor> mColors;
    QGridLayout *mLayout;
    QLabel *mTitleLabel;
    QMenu *mWidgetMenu;
    QTimer *mPaintTimer;
    QString mTitle;
    int mAxis;
    int mTimerInterval;
};
