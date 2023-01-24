#include "matrix.h"
matrix::matrix(QMap <int, QMap <int, vertex *>> * _matrixOfVertex, paintScene * _scene, QObject *parent)
    : QAbstractTableModel{parent}, scene(_scene), matrixOfVertex(_matrixOfVertex)
{

}
int matrix::rowCount(const QModelIndex &parent) const {
    return matrixOfVertex->size();
}
int matrix::columnCount(const QModelIndex &parent) const {
    return matrixOfVertex->size();
}
QVariant matrix::data(const QModelIndex &index, int role) const {
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
bool matrix::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (index.isValid() && role == Qt::EditRole && index.column() != index.row()) {
        if (value == "1" && this->index(index.row(), index.column()).data().toString() != "1") {
            (*matrixOfVertex)[index.row()].remove(index.column());
            (*matrixOfVertex)[index.column()].remove(index.row());
            (*matrixOfVertex)[index.row()][index.column()] = scene->getVertex(index.column());
            (*matrixOfVertex)[index.column()][index.row()] = scene->getVertex(index.row());
            edge * e = new edge(QPointF(scene->getVertex(index.row())->pos().x() + 25, scene->getVertex(index.row())->pos().y() + 25), QPointF(scene->getVertex(index.column())->pos().x() + 25, scene->getVertex(index.column())->pos().y() + 25));
            e->input = scene->getVertex(index.row());
            e->output = scene->getVertex(index.column());
            scene->getVertex(index.row())->Push_EdgeOut(e);
            scene->getVertex(index.column())->Push_EdgeIn(e);
            scene->addItem(e);
            return true;
        }
        else if (value == "0" && this->index(index.row(), index.column()).data().toString() != "0") {
            (*matrixOfVertex)[index.row()].remove(index.column());
            (*matrixOfVertex)[index.column()].remove(index.row());
            edge * buf = NULL;
            //qDebug() << buf;
            //qDebug() << scene->getVertex(index.row());
            for (int i = 0; i != scene->getVertex(index.row())->inputEdges.size(); ++i) {
                if (scene->getVertex(index.row())->inputEdges[i]->input == scene->getVertex(index.column())) {
                    buf = scene->getVertex(index.row())->inputEdges[i];
                }
            }
            for (int i = 0; i != scene->getVertex(index.row())->outputEdges.size(); ++i) {
                if (scene->getVertex(index.row())->outputEdges[i]->output == scene->getVertex(index.column())) {
                    buf = scene->getVertex(index.row())->outputEdges[i];
                }
            }
            buf->input->outputEdges.removeOne(buf);
            buf->output->inputEdges.removeOne(buf);
            scene->removeItem(buf);
            delete buf;
            return true;
        }
    }
    return false;
}
Qt::ItemFlags matrix::flags(const QModelIndex &index) const{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    return index.isValid() ? (flags | Qt::ItemIsEditable) : flags;
}
//QVariant headerData(int nSection, Qt::Orientation orientation, int nRole = Qt::DisplayRole) {
//    return ;
//}

