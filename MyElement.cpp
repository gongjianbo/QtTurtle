#include "MyElement.h"

#include <QDebug>

PenColorElement::PenColorElement(const QColor &color)
    : AbstractElement(1),elementColor(color)
{
}

void PenColorElement::draw(QPainter *painter, float )
{
    QPen pen=painter->pen();
    pen.setColor(elementColor);
    painter->setPen(pen);
}

PenWidthElement::PenWidthElement(int width)
    : AbstractElement(2),elementWidth(width)
{
}

void PenWidthElement::draw(QPainter *painter, float )
{
    QPen pen=painter->pen();
    pen.setWidth(elementWidth);
    painter->setPen(pen);
}

BeginFillElement::BeginFillElement(int index, const QColor &color)
    : AbstractElement(3),elementIndex(index),elementColor(color)
{
}

void BeginFillElement::draw(QPainter *painter, float )
{
    painter->fillPath(elementPath,elementColor);
}

void BeginFillElement::setFillPath(const QPainterPath &path)
{
    elementPath=path;
}

EndFillElement::EndFillElement(int index)
    : AbstractElement(4),elementIndex(index)
{
}

void EndFillElement::draw(QPainter *, float )
{

}

LineElement::LineElement(const QLineF &line)
    : AbstractElement(100),elementLine(line)
{
    len=line.length();
}

void LineElement::draw(QPainter *painter, float progress)
{
    QLineF line=elementLine;
    line.setP2(line.pointAt(progress));
    painter->drawLine(line);
}

