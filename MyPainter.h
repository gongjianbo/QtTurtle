#ifndef MYPAINTER_H
#define MYPAINTER_H

#include <QObject>
#include <QPainter>
#include <QTimer>
#include <QTime>

#include "MyElement.h"

/**
 * @brief 画笔
 * @author 龚建波
 * @date 2021-1-2
 * @details
 * 用于绘制过程，类似python的turtle海龟绘图
 * 没想到一个好的类名
 */
class MyPainter : public QObject
{
    Q_OBJECT
public:
    explicit MyPainter(QObject *parent = nullptr);

    //在paintEvent中调用，参数参照QPainter，可以直接填widget的this
    void draw(QPaintDevice *device);
    //开始绘制动画
    void start();

    //以某点作为起点
    void begin(const QPointF &pos=QPointF(0,0));
    //绘制结束
    void end();

    //直线
    void lineTo(const QPointF &pos);

signals:
    //请求刷新
    void update();

private:
    //缺一个状态枚举，用来启停重复等
    //缺一个速度控制

    //动画
    QTimer *timer=nullptr;
    int timerInterval=30;
    //当前计算的点
    QPointF currentPos;
    //记录绘制进度
    qint64 drawLength=0;
    //记录起始时间
    QTime startTime;
    //ms步进值
    //double pxPerMs=0.1;

    //数据链
    QList<MyElement> dataList;
    //数据总长度
    qint64 dataLength=0;
};

#endif // MYPAINTER_H
