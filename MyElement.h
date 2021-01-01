#ifndef MYELEMENT_H
#define MYELEMENT_H

#include <QObject>
#include <QVariant>
#include <QPainter>

/**
 * @brief 待绘制的元素
 * @author 龚建波
 * @date 2021-1-2
 */
class MyElement
{
public:
    //图元类型
    enum Type{
        Line, //直线
        Arc  //圆弧
    };
public:
    explicit MyElement(const QVariant &data,MyElement::Type type);

    //绘制该图元
    //progress为百分比进度[0-1]
    void draw(QPainter *painter,float progress);

    //数据的总长度，对于线条类型有效
    int length() const { return len; }

private:
    //图元类型
    MyElement::Type type;
    //图元数据
    QVariant data;

    //线条长度
    int len=0;
};

#endif // MYELEMENT_H
