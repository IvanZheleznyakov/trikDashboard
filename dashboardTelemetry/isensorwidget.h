#pragma once

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
    explicit ISensorWidget(int axis, QString title, int timerInterval, QWidget *parent = 0);

protected:
    QVector<QColor> getColors() const;
    void setColors(const QVector<QColor> &value);

    QVector<float> getData() const;
    void setData(const QVector<float> &value);

    QGridLayout *getLayout() const;
    void setLayout(QGridLayout *value);

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
    virtual void startPaint() = 0;
    virtual void stopPaint() = 0;
    virtual void updateData(QVector <float> updates) = 0;
    virtual void setInterval(int interval) = 0;
    virtual void paintWidget() = 0;
    virtual void init() = 0;

private:
    QVector<QColor> colors;
    QVector<float> data;
    QGridLayout *layout;
    QLabel *titleLabel;
    QMenu *widgetMenu;
    QTimer *paintTimer;
    QString title;
    int axis;
    int timerInterval;
};
