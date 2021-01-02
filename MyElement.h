#ifndef MYELEMENT_H
#define MYELEMENT_H

#include <QObject>
#include <QVariant>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QPainterPath>

/**
 * @brief 待绘制的元素父类
 * @author 龚建波
 * @date 2021-1-2
 * @details
 * 可以是直线，圆弧等图元
 * 也可以是setPen setColor等操作
 */
class AbstractElement
{
protected:
    explicit AbstractElement(int type)
        : elementType(type) { }
public:
    //绘制该图元
    //progress为百分比进度[0-1]
    virtual void draw(QPainter *painter,float progress)=0;

    //数据的总长度，对于线条类型有效
    virtual int length() const { return 0; }

    //元素类型，暂时不定义枚举列表
    int type() const { return elementType; }
private:
    //元素类型
    int elementType=0;
};

//画笔颜色，type=1
class PenColorElement : public AbstractElement
{
public:
    explicit PenColorElement(const QColor &color);
    //绘制
    void draw(QPainter *painter,float progress) override;
private:
    QColor elementColor;
};

//画笔宽度，type=2
class PenWidthElement : public AbstractElement
{
public:
    explicit PenWidthElement(int width);
    //绘制
    void draw(QPainter *painter,float progress) override;
private:
    int elementWidth;
};

//begin填充元素,type=3
class BeginFillElement : public AbstractElement
{
public:
    explicit BeginFillElement(int index,const QColor &color);
    //绘制
    void draw(QPainter *painter,float progress) override;
    //begin绘制到end时才填充路径
    int index() const { return elementIndex; }
    //路径设置
    void setFillPath(const QPainterPath &path);
private:
    int elementIndex=0;
    QPainterPath elementPath;
    QColor elementColor;
};

//end填充元素,type=4
class EndFillElement : public AbstractElement
{
public:
    explicit EndFillElement(int index);
    //绘制
    void draw(QPainter *painter,float progress) override;
    //begin绘制到end时才填充路径
    int index() const { return elementIndex; }
private:
    int elementIndex=0;
};

//直线元素,type=100
class LineElement : public AbstractElement
{
public:
    explicit LineElement(const QLineF &line);
    //绘制
    void draw(QPainter *painter,float progress) override;

    int length() const override { return len; }
private:
    QLineF elementLine;
    int len=0;
};



#endif // MYELEMENT_H
