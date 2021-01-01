#include "MyPainter.h"

#include <QDebug>

MyPainter::MyPainter(QObject *parent) : QObject(parent)
{
    timer=new QTimer(this);
    connect(timer,&QTimer::timeout,this,[=]{
        drawLength+=10;
        update();

        //时长超过表示线条绘制完了
        if(drawLength>=dataLength)
            timer->stop();
    });
}

void MyPainter::draw(QPaintDevice *device)
{
    if(drawLength<=0)
        return;
    QPainter painter(device);

    qint64 progress_temp=0;
    for(int i=0;i<dataList.count()&&progress_temp<drawLength;i++)
    {
        MyElement &item=dataList[i];
        double len=drawLength-progress_temp;
        item.draw(&painter,len>item.length()?1:len/item.length());
        progress_temp+=item.length();
    }
}

void MyPainter::start()
{
    timer->start(timerInterval);
    drawLength=0;
    startTime=QTime::currentTime();
}

void MyPainter::begin(const QPointF &pos)
{
    currentPos=pos;
    dataLength=0;
    dataList.clear();
}

void MyPainter::end()
{

}

void MyPainter::lineTo(const QPointF &pos)
{
    MyElement new_data(QLineF(currentPos,pos),MyElement::Line);
    dataList.push_back(new_data);
    dataLength+=new_data.length();
    currentPos=pos;
}
