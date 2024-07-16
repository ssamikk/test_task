#ifndef RECTOBJECT_H
#define RECTOBJECT_H

#include "dataobject.h"

class RectObject : public DataObject
{
public:
    RectObject(const RectData *obj);
    ~RectObject();
    virtual QGraphicsItem *item() const override;
    Type getType() const override;
    QString position() const override;
    QString region() const override;
    bool visible() const override;
    void removeFromScen() override;
    void setVisible(bool visible) override;
private:
    QGraphicsRectItem *_item;
};

#endif // RECTOBJECT_H
