#include "directmatrix.h"
directmatrix::directmatrix(QMap <int, QMap <int, directedge *>> * _matrixOfVertex, directpaintScene * _scene, QObject *parent)
    : QAbstractTableModel{parent}, scene(_scene), matrixOfVertex(_matrixOfVertex)
{

}
int directmatrix::rowCount(const QModelIndex &parent) const {
    return matrixOfVertex->size();
}
int directmatrix::columnCount(const QModelIndex &parent) const {
    return matrixOfVertex->size();
}
QVariant directmatrix::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
            if(/*matrixOfVertex[index.row()][index.column()]*/ (*matrixOfVertex)[index.row()][index.column()] != NULL && index.row() != index.column()) {
                int num = 1;
                return QVariant(num);
            }
            else {
                int num = 0;
                return QVariant(num);
            }
    }
    return QVariant();
}
bool directmatrix::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (index.isValid() && role == Qt::EditRole && index.column() != index.row()) {
        if (value == "1" && this->index(index.row(), index.column()).data().toString() != "1") {
            if((*matrixOfVertex)[index.row()][index.column()] == NULL && (*matrixOfVertex)[index.column()][index.row()] == NULL) {
                directedge * e = new directedge(QPointF(scene->getVertex(index.row())->pos().x() + 25, scene->getVertex(index.row())->pos().y() + 25), QPointF(scene->getVertex(index.column())->pos().x() + 25, scene->getVertex(index.column())->pos().y() + 25));
                e->input = scene->getVertex(index.row());
                e->output = scene->getVertex(index.column());
                e->setConnection();
                (*matrixOfVertex)[index.row()][index.column()] = e;
                scene->getVertex(index.row())->Push_EdgeOut(e);
                scene->getVertex(index.column())->Push_EdgeIn(e);
                scene->addItem(e);
                return true;
            }
            else {
                if ((*matrixOfVertex)[index.row()][index.column()] != NULL) {
                    qDebug() << "This1";
                    directedge * e = (*matrixOfVertex)[index.row()][index.column()];
                    e->setConnectionStart(true);
                    e->output->Push_EdgeIn(e);
                    e->input->Push_EdgeOut(e);
                    (*matrixOfVertex)[index.column()][index.row()] = e;
                    return true;
                }
                if ((*matrixOfVertex)[index.column()][index.row()] != NULL) {
                    qDebug() << "This2";
                    directedge * e = (*matrixOfVertex)[index.column()][index.row()];
                    e->setConnectionStart(true);
                    e->output->Push_EdgeIn(e);
                    e->input->Push_EdgeOut(e);
                    (*matrixOfVertex)[index.row()][index.column()] = e;
                    return true;
                }
            }
        }
        else if (value == "0" && this->index(index.row(), index.column()).data().toString() != "0") {
            directedge * buf = (*matrixOfVertex)[index.row()][index.column()];
            if(buf->getConnectionEnd() && buf->getConnectionStart()) {
                if(buf->input->getNumber() - 1 == index.row()) {
                    buf->setConnectionEnd(false);
                    (*matrixOfVertex)[index.row()].remove(index.column());
                    buf->input->outputEdges.removeOne(buf);
                    buf->output->inputEdges.removeOne(buf);
                    return true;
                }
                else {
                    buf->setConnectionStart(false);
                    (*matrixOfVertex)[index.row()].remove(index.column());
                    buf->input->outputEdges.removeOne(buf);
                    buf->output->inputEdges.removeOne(buf);
                    return true;
                }
                return true;
            }
            else {
                (*matrixOfVertex)[index.row()].remove(index.column());
                buf->input->outputEdges.removeOne(buf);
                buf->output->inputEdges.removeOne(buf);
                scene->removeItem(buf);
                delete buf;
                return true;
            }
            return true;
        }
    }
    return false;
}
Qt::ItemFlags directmatrix::flags(const QModelIndex &index) const{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    return index.isValid() ? (flags | Qt::ItemIsEditable) : flags;
}
//QVariant headerData(int nSection, Qt::Orientation orientation, int nRole = Qt::DisplayRole) {
//    return ;
//}

