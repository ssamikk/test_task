#ifndef LINEOBJECT_H
#define LINEOBJECT_H

#include "dataobject.h"

class LineObject : public DataObject
{
public:
    LineObject(const LineData *obj);
    ~LineObject();
    virtual QGraphicsItem *item() const override;
    Type getType() const override;
    QString position() const override;
    QString region() const override;
    bool visible() const override;
    void removeFromScen() override;
    void setVisible(bool visible) override;
private:
    QGraphicsLineItem *_item;
};

#endif // LINEOBJECT_H
