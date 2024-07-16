#ifndef ELLIPSEOBJECT_H
#define ELLIPSEOBJECT_H

#include "dataobject.h"

class EllipseObject : public DataObject
{
public:
    EllipseObject(const EllipseData *obj);
    ~EllipseObject();
    virtual QGraphicsItem *item() const override;
    Type getType() const override;
    QString position() const override;
    QString region() const override;
    bool visible() const override;
    void removeFromScen() override;
    void setVisible(bool visible) override;
private:
    QGraphicsEllipseItem *_item;
};

#endif // ELLIPSEOBJECT_H
