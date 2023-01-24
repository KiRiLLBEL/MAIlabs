#include "directitem.h"
#include <QLineEdit>
#include <QIntValidator>

directitem::directitem(QObject *parent) :
    QItemDelegate(parent)
{
}

QWidget *directitem::createEditor(QWidget *parent,
                                    const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);
    editor->setValidator( new QRegularExpressionValidator( QRegularExpression( "[0-1]" ) ) );;
    return editor;
}


void directitem::setEditorData(QWidget *editor,
                                 const QModelIndex &index) const
{
    QString value =index.model()->data(index, Qt::EditRole).toString();
        QLineEdit *line = static_cast<QLineEdit*>(editor);
        line->setText(value);
}


void directitem::setModelData(QWidget *editor,
                                QAbstractItemModel *model,
                                const QModelIndex &index) const
{
    QLineEdit *line = static_cast<QLineEdit*>(editor);
    QString value = line->text();
    model->setData(index, value);
}


void directitem::updateEditorGeometry(QWidget *editor,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
