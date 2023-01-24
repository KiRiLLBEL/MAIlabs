#ifndef MATRIX_H
#define MATRIX_H

#include <QAbstractTableModel>
#include <QWidget>
#include <QVariant>
#include <vertex.h>
#include <paintscene.h>
class matrix : public QAbstractTableModel
{
public:
    explicit matrix(QMap <int, QMap <int, vertex *>> * _matrixOfVertex, paintScene * _scene, QObject *parent = nullptr);
private:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    //QVariant headerData(int nSection, Qt::Orientation orientation, int nRole = Qt::DisplayRole) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role);
    paintScene * scene;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QMap <int, QMap <int, vertex *>> * matrixOfVertex;
};

#endif // MATRIX_H
