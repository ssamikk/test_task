#include "rectobject.h"
#include <QBrush>
#include <QGraphicsScene>
#include <QDebug>

RectObject::RectObject(const RectData *obj)
{
    _item = new QGraphicsRectItem(QRectF(obj->x(), obj->y(), obj->width(), obj->height()));
    _item->setBrush(QBrush(QColor(QString::fromStdString(obj->color_hex()->str()))));
}

RectObject::~RectObject()
{

}

QGraphicsItem *RectObject::item() const
{
    return _item;
}

DataObject::Type RectObject::getType() const
{
    return Rect;
}

QString RectObject::position() const
{
    QPointF point = _item->boundingRect().topLeft();
    return QString("%1px, %2px").arg(point.x()).arg(point.y());
}

QString RectObject::region() const
{
    QSizeF size =_item->boundingRect().size();
    return QString("%1px, %2px").arg(size.width()).arg(size.height());
}

bool RectObject::visible() const
{
    return (_item->brush().color().alpha() != 50);
}

void RectObject::removeFromScen()
{
    if (_item->scene()){
        _item->scene()->removeItem(_item);
    }
}

void RectObject::setVisible(bool visible)
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
