#include "ellipseobject.h"
#include <QBrush>
#include <QGraphicsScene>
#include <QDebug>

EllipseObject::EllipseObject(const EllipseData *obj)
{
    _item = new QGraphicsEllipseItem(obj->x(), obj->y(), obj->r1(), obj->r2());
    _item->setBrush(QBrush(QColor(QString::fromStdString(obj->color_hex()->str()))));
}

EllipseObject::~EllipseObject()
{

}

QGraphicsItem *EllipseObject::item() const
{
    return _item;
}

DataObject::Type EllipseObject::getType() const
{
    return Ellipse;
}

QString EllipseObject::position() const
{
    QPointF point = _item->boundingRect().topLeft();
    return QString("%1px, %2px").arg(point.x()).arg(point.y());
}

QString EllipseObject::region() const
{
    QSizeF size =_item->boundingRect().size();
    return QString("%1px, %2px").arg(size.width()).arg(size.height());
}

bool EllipseObject::visible() const
{
    return (_item->brush().color().alpha() != 50);
}

void EllipseObject::removeFromScen()
{
    if (_item->scene()){
        _item->scene()->removeItem(_item);
    }
}

void EllipseObject::setVisible(bool visible)
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
