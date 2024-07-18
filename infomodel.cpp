#include "dataobject.h"
#include "infomodel.h"

#include <QIcon>
#include <QDebug>

InfoModel::InfoModel(QObject *parent): QAbstractTableModel(parent)
{

}

InfoModel::~InfoModel()
{
    qDeleteAll(dataObj);
}

int InfoModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return dataObj.size();
}

int InfoModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return CTotalColumn;
}

QVariant InfoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() && index.row() >= dataObj.size()){
        return QVariant();
    }
    DataObject *obj = dataObj.at(index.row());
    if (role == Qt::DisplayRole){
        switch (index.column()) {
        case CId:
            return index.row();
        case CType:
            switch (obj->getType()) {
            case DataObject::Rect:
                return "Rect";
            case DataObject::Ellipse:
                return "Ellipse";
            case DataObject::Triangle:
                return "Triangle";
            case DataObject::Line:
                return "Line";
            default:
                break;
            }
            return obj->getType();
        case CPosition:
            return obj->position();
        case CRegion:
            return obj->region();
        case CVisible:
            return obj->visible();
        default:
            break;
        }
    }
    return QVariant();
}

QVariant InfoModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole){
        switch (section) {
        case CId:
            return "ID";
        case CType:
            return "Type";
        case CPosition:
            return "Position(X,Y)";
        case CRegion:
            return "Region(Width, Height)";
        case CVisible:
            return "Visible";
        case CRemove:
            return "Remove";
        default:
            break;
        }
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}

bool InfoModel::removeRows(int row, int count, const QModelIndex &parent)
{
    bool flag = false;
    beginRemoveRows(parent, row, row + count -1);
    for (int i = 0; i<count; i++){
        if (row < dataObj.size()){
            DataObject *obj = dataObj.takeAt(row);
            obj->removeFromScen();
            delete obj;
            flag = true;
        } else {
            break;
        }
    }
    endRemoveRows();
    return flag;
}

bool InfoModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && index.row()< dataObj.size() && index.column() == CVisible && role == Qt::EditRole){
        DataObject *obj = dataObj.at(index.row());
        obj->setVisible(value.toBool());
        return true;
    }
    return false;
}

Qt::ItemFlags InfoModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flag = Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    if (index.column() == CVisible) {
        flag |= Qt::ItemIsEditable | Qt::ItemIsUserCheckable;
    }
    return flag;
}

void InfoModel::addObj(DataObject *obj)
{
    int row = dataObj.size();
    beginInsertRows(QModelIndex(), row, row);
    dataObj.append(obj);
    endInsertRows();
}
