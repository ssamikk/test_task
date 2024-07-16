#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include <QGraphicsItem>
#include "api_generated.h"

class DataObject
{
public:
    DataObject();
    virtual ~DataObject();
    enum Type{
        Unknow,
        Rect,
        Ellipse,
        Triangle,
        Line
    };
    virtual Type getType() const;
    virtual QGraphicsItem *item() const = 0;
    virtual QString position() const = 0;
    virtual QString region() const = 0;
    virtual bool visible() const = 0;
    virtual void removeFromScen() = 0;
    virtual void setVisible(bool visible) = 0;
};

#endif // DATAOBJECT_H
