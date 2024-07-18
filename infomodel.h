#ifndef INFOMODEL_H
#define INFOMODEL_H

#include <QAbstractTableModel>

class DataObject;

class InfoModel : public QAbstractTableModel
{
public:
    InfoModel(QObject *parent = nullptr);
    ~InfoModel();
    enum Column{
        CId,
        CType,
        CPosition,
        CRegion,
        CVisible,
        CRemove,
        CTotalColumn
    };
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    void addObj(DataObject *obj);
private:
    QList<DataObject*> dataObj;
};

#endif // INFOMODEL_H
