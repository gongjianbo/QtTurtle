#include "MyPainter.h"

#include <QtMath>
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

MyPainter::~MyPainter()
{
    qDeleteAll(dataList);
    dataList.clear();
}

void MyPainter::draw(QPaintDevice *device)
{
    if(drawLength<=0)
        return;
    QPainter painter(device);

    qint64 progress_temp=0;
    for(int i=0;i<dataList.count()&&progress_temp<drawLength;i++)
    {
        double len=drawLength-progress_temp;
        AbstractElement* item=dataList[i];
        //判断begin和end fill，执行到endfill才开始填充begin中的路径
        switch (item->type()) {
        case 3:
        {
            const int ele_index=static_cast<BeginFillElement*>(item)->index();
            if(drawEndIndex>=ele_index){
                item->draw(&painter,0);
            }
        }
            break;
        case 4:
            drawEndIndex=static_cast<EndFillElement*>(item)->index();
            break;
        default:
            item->draw(&painter,len>item->length()?1:len/item->length());
            break;
        }

        //len不够就是还没画完，后面的就不画了
        if(len<item->length())
            break;
        progress_temp+=item->length();
    }
}

void MyPainter::start()
{
    timer->start(timerInterval);
    drawLength=0;
    drawEndIndex=-1;
    startTime=QTime::currentTime();
}

void MyPainter::begin(const QPointF &pos)
{
    //begin为路径规划开始，状态复位
    currentPos=pos;
    dataLength=0;
    dataList.clear();
}

void MyPainter::end()
{
    //end暂无操作
}

void MyPainter::setPenColor(const QColor &color)
{
    PenColorElement *ele=new PenColorElement(color);
    dataList.push_back(ele);
}

void MyPainter::setPenWidth(int width)
{
    PenWidthElement *ele=new PenWidthElement(width);
    dataList.push_back(ele);
}

void MyPainter::beginFill(const QColor &color)
{
    //开始填充后，beginElement!=null，path在别的函数判断中就能追加路径
    fillBeginIndex++;
    fillBeginPath=QPainterPath();
    fillBeginPath.moveTo(currentPos);
    fillBeginElement=new BeginFillElement(fillBeginIndex,color);
    dataList.push_back(fillBeginElement);
}

void MyPainter::endFill()
{
    if(fillBeginElement){
        //end后路径就完成了
        fillBeginElement->setFillPath(fillBeginPath);
        EndFillElement *ele=new EndFillElement(fillBeginIndex);
        dataList.push_back(ele);

        fillBeginElement=nullptr;
    }
}

void MyPainter::moveTo(const QPointF &pos)
{
    if(fillBeginElement){
        fillBeginPath.moveTo(pos);
    }
    currentPos=pos;
}

void MyPainter::lineTo(const QPointF &pos)
{
    if(fillBeginElement){
        fillBeginPath.lineTo(pos);
    }
    LineElement *ele=new LineElement(QLineF(currentPos,pos));
    dataList.push_back(ele);
    dataLength+=ele->length();
    currentPos=pos;
}

void MyPainter::arc(const QPointF &center, int radius, int startAngle, int spanAngle)
{
    QRectF ele_rect=QRectF(center.x()-radius,center.y()-radius,
                           radius*2,radius*2);
    if(fillBeginElement){
        //const int len=std::ceil(std::abs(spanAngle)*M_PI*radius/180.0);
        fillBeginPath.arcTo(ele_rect,startAngle,spanAngle);
    }
    ArcElement *ele=new ArcElement(ele_rect,startAngle,spanAngle);
    dataList.push_back(ele);
    dataLength+=ele->length();
    //currentPos=stop;
}
