#include "lineobject.h"
#include <QBrush>
#include <QGraphicsScene>
#include <QDebug>

LineObject::LineObject(const LineData *obj)
{
    _item = new QGraphicsLineItem(obj->x1(), obj->y1(), obj->x2(), obj->y2());
    _item->setPen(QPen(QColor(QString::fromStdString(obj->color_hex()->str()))));
}

LineObject::~LineObject()
{

}

QGraphicsItem *LineObject::item() const
{
    return _item;
}

DataObject::Type LineObject::getType() const
{
    return Line;
}

QString LineObject::position() const
{
    QPointF point = _item->boundingRect().topLeft();
    return QString("%1px, %2px").arg(point.x()).arg(point.y());
}

QString LineObject::region() const
{
    QSizeF size =_item->boundingRect().size();
    return QString("%1px, %2px").arg(size.width()).arg(size.height());
}

bool LineObject::visible() const
{
    return (_item->pen().color().alpha() != 50);
}

void LineObject::removeFromScen()
{
    if (_item->scene()){
        _item->scene()->removeItem(_item);
    }
}

void LineObject::setVisible(bool visible)
{
    QPen brush = _item->pen();
    QColor color = brush.color();
    if (visible) {
        color.setAlpha(250);
    } else {
        color.setAlpha(50);
    }
    brush.setColor(color);
    _item->setPen(brush);
}
