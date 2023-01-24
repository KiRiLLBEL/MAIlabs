#ifndef DIRECTITEMDELEGATE_H
#define DIRECTITEMDELEGATE_H

#include <QItemDelegate>

class directitem : public QItemDelegate
{
    Q_OBJECT
public:
    explicit directitem(QObject *parent = 0);

protected:
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget * editor, const QModelIndex & index) const;
    void setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const;
    void updateEditorGeometry(QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index) const;

signals:

public slots:

};

#endif // ITEMDELEGATE_H
