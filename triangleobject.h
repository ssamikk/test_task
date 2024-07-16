#ifndef TRIANGLEOBJECT_H
#define TRIANGLEOBJECT_H

#include "dataobject.h"

class TriangleObject : public DataObject
{
public:
    TriangleObject(const TriangleData *obj);
    ~TriangleObject();
    virtual QGraphicsItem *item() const override;
    Type getType() const override;
    QString position() const override;
    QString region() const override;
    bool visible() const override;
    void removeFromScen() override;
    void setVisible(bool visible) override;
private:
    QGraphicsPolygonItem *_item;
};

#endif // TRIANGLEOBJECT_H
