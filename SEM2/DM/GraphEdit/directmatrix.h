#ifndef DIRECTMATRIX_H
#define DIRECTMATRIX_H

#include <QAbstractTableModel>
#include <QWidget>
#include <QVariant>
#include <directvertex.h>
#include <directpaintscene.h>
class directmatrix : public QAbstractTableModel
{
public:
    explicit directmatrix(QMap <int, QMap <int, directedge *>> * _matrixOfVertex, directpaintScene * _scene, QObject *parent = nullptr);
private:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    //QVariant headerData(int nSection, Qt::Orientation orientation, int nRole = Qt::DisplayRole) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role);
    directpaintScene * scene;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    void componentIn(QColor colour);
    void componentOut();
    QMap <int, QMap <int, directedge *>> * matrixOfVertex;
};

#endif // MATRIX_H
