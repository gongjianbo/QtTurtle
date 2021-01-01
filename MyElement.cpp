#include "MyElement.h"


MyElement::MyElement(const QVariant &data, MyElement::Type type)
    : data(data),type(type)
{
    switch (type) {
    case Type::Line:
        len=data.toLineF().length();
        break;
    case Type::Arc:
        break;
    default:
        break;
    }
}

void MyElement::draw(QPainter *painter, float progress)
{
    switch (type) {
    case Type::Line:
    {
        QLineF line=data.toLineF();
        line.setP2(line.pointAt(progress));
        painter->drawLine(line);
    }
        break;
    case Type::Arc:
        break;
    default:
        break;
    }
}
