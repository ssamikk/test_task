#include "triangleobject.h"
#include <QBrush>
#include <QGraphicsScene>
#include <QVector>
#include <QPolygonF>

TriangleObject::TriangleObject(const TriangleData *obj)
{
    _item = new QGraphicsPolygonItem(QPolygonF(QVector<QPoint>()<<QPoint(obj->x1(), obj->y1())<<QPoint(obj->x2(), obj->y2())<<QPoint(obj->x3(), obj->y3())));
    _item->setBrush(QBrush(QColor(QString::fromStdString(obj->color_hex()->str()))));
}

TriangleObject::~TriangleObject()
{

}

QGraphicsItem *TriangleObject::item() const
{
    return _item;
}

DataObject::Type TriangleObject::getType() const
{
    return Triangle;
}

QString TriangleObject::position() const
{
    QPointF point = _item->boundingRect().topLeft();
    return QString("%1px, %2px").arg(point.x()).arg(point.y());
}

QString TriangleObject::region() const
{
    QSizeF size =_item->boundingRect().size();
    return QString("%1px, %2px").arg(size.width()).arg(size.height());
}

bool TriangleObject::visible() const
{
    return (_item->brush().color().alpha() != 50);
}

void TriangleObject::removeFromScen()
{
    if (_item->scene()){
        _item->scene()->removeItem(_item);
    }
}

void TriangleObject::setVisible(bool visible)
{
    QBrush brush = _item->brush();
    QColor color = brush.color();
    if (visible) {
        color.setAlpha(250);
    } else {
        color.setAlpha(50);
    }
    brush.setColor(color);
    _item->setBrush(brush);
}
