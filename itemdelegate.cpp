#include "delegate.h"
#include "infomodel.h"
#include "itemdelegate.h"

#include <QDebug>
#include <QPainter>

ItemDelegate::ItemDelegate(QObject *parent): QItemDelegate(parent)
{
}

ItemDelegate::~ItemDelegate()
{
}

void ItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == InfoModel::CVisible){
        QImage img(index.data().toBool() ? ":/img/visible.png" : ":/img/unvisible.png");
        painter->drawImage(option.rect, img, img.rect());
        return;
    }
    QItemDelegate::paint(painter, option, index);
}

QWidget *ItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    if (index.isValid() && index.column() == InfoModel::CVisible) {
        Delegate *delegate = new Delegate(parent);
        return delegate;
    }
    return nullptr;
}

void ItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (index.isValid() && index.column() == InfoModel::CVisible) {
        Delegate *button = qobject_cast<Delegate*>(editor);
        if (button){
            button->setValue(index.data(Qt::DisplayRole).toBool());
        }
    }
}

void ItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (index.isValid() && index.column() == InfoModel::CVisible) {
        Delegate *button = qobject_cast<Delegate*>(editor);
        if (button){
            model->setData(index, button->getValue(), Qt::EditRole);
        }
    }
}

void ItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (qobject_cast<Delegate*>(editor)){
        editor->setGeometry(option.rect);
        return;
    }
    QItemDelegate::updateEditorGeometry(editor, option, index);
}
