#include "paintscene.h"
#include "vertex.h"
#include "edge.h"
#include "QGraphicsView"
paintScene::paintScene(QObject * parent) : QGraphicsScene(parent)
{
    sizeOfMatrix.setHeight(0);
    sizeOfMatrix.setWidth(0);
}
void paintScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (changeDeleteMode == false) {
        QTransform tr;
        if ((itemAt(event->scenePos(), tr) == 0 ||  qgraphicsitem_cast<edge *>(itemAt(event->scenePos(), tr))) && event->button() == Qt::LeftButton) {
            vertex * v = new vertex(event->scenePos(), ++count);
            QMap <int, vertex *> m;
            m.insert(count - 1, v);
            matrixOfVertex.insert(count - 1, m);
            emit signalFromScene(&matrixOfVertex);
            allVertex.push_back(v);
            addItem(v);
            //qDebug() << matrixOfVertex;
            v->setPos(QPointF(event->scenePos().x() - 25, event->scenePos().y() - 25));
        }
        else {
            if(event->button() == Qt::RightButton && addingEdge == false) {
                vertex * parent = qgraphicsitem_cast<vertex *>(itemAt(event->scenePos(), tr));
                if (parent != NULL && count > 1) {
                    edge * e = new edge(QPointF(parent->pos().x() + 25, parent->pos().y() + 25), event->scenePos());
                    buf = e;
                    bufV = parent;
                    addingEdge = true;
                    addItem(e);
                }
            }
            else if(event->button() == Qt::LeftButton && !addingEdge) {
                QGraphicsScene::mousePressEvent(event);
            }
            else if(event->button() == Qt::RightButton && addingEdge) {
                removeItem(buf);
                delete buf;
                addingEdge = false;
            }
            else {
                if (addingEdge && event->button() == Qt::LeftButton) {
                    vertex * parent = qgraphicsitem_cast<vertex *>(itemAt(event->scenePos(), tr));
                    if (parent != NULL && parent != bufV) {
                        if(matrixOfVertex[bufV->getNumber() - 1][parent->getNumber() - 1] == NULL) {
                            buf->changePos(QPointF(parent->pos().x() + 25, parent->pos().y() + 25));
                            buf->update();
                            buf->input = bufV;
                            buf->output = parent;
                            matrixOfVertex[bufV->getNumber() - 1].insert(parent->getNumber() - 1, parent);
                            matrixOfVertex[parent->getNumber() - 1].insert(bufV->getNumber() - 1, bufV);
                            emit signalFromScene(&matrixOfVertex);
                            //qDebug() << matrixOfVertex;
                            bufV->Push_EdgeOut(buf);
                            parent->Push_EdgeIn(buf);
                            addingEdge = false;
                        }
                    }
                }
            }
        }
    }
    else {
        QTransform tr;
        if (qgraphicsitem_cast<vertex *>(itemAt(event->scenePos(), tr)) != NULL && event->button() == Qt::LeftButton) {
//            addRect(QRectF(0, 0, 50, 50), Qt::NoPen, Qt::black);
            vertex * vertexNow = qgraphicsitem_cast<vertex *>(itemAt(event->scenePos(), tr));
            foreach (edge * e, vertexNow->inputEdges) {
                e->input->outputEdges.removeOne(e);
                matrixOfVertex[e->input->getNumber() - 1].remove(vertexNow->getNumber() - 1);
                //qDebug() << "IN"<< e->input->outputEdges << e->input->getNumber();
                removeItem(e);
                delete e;
            }
            foreach (edge * e, vertexNow->outputEdges) {
                e->output->inputEdges.removeOne(e);
                matrixOfVertex[e->output->getNumber() - 1].remove(vertexNow->getNumber() - 1);
                //qDebug() << "OUT"<< e->output->inputEdges << e->output->getNumber();
                removeItem(e);
                delete e;
            }
            //make O(n)
            matrixOfVertex.remove(vertexNow->getNumber() - 1);
            int checkNumber = vertexNow->getNumber() - 1;
            //qDebug() << "OK";
            for (int i = 0; i != matrixOfVertex.size() + 1; ++i) {
                if(i > checkNumber) {
                    matrixOfVertex.insert(i - 1, matrixOfVertex[i]);
                    matrixOfVertex[i - 1][i]->changeNumber(i);
                    matrixOfVertex.remove(i);
                }
            }
            //qDebug() << "OK1";
            for (int i = 0; i != matrixOfVertex.size(); ++i) {
                for (int j = 0; j != matrixOfVertex.size() + 1; ++j) {
                    if (matrixOfVertex[i][j] != NULL && j > checkNumber) {
                        matrixOfVertex[i].insert(j - 1, matrixOfVertex[i][j]);
                        matrixOfVertex[i].remove(j);
                    }
                }
            }
            //qDebug() << vertexNow->inputEdges << vertexNow->outputEdges;
            removeItem(vertexNow);
            for (int i = 0; i != allVertex.size(); ++i) {
                if (i > checkNumber) {
                    allVertex[i - 1] = allVertex[i];
                }
            }
            allVertex.remove(checkNumber);
            delete vertexNow;
            --count;
            emit signalFromScene(&matrixOfVertex);
            //qDebug() << matrixOfVertex;
        }
    }
}
void paintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
       QGraphicsScene::mouseMoveEvent(event);
       if (addingEdge) {
           buf->changePos(event->scenePos());
           buf->update();
       }

}
void paintScene::setCount(int _count) {
    count = _count;
}
QMap <int, QMap <int, vertex *>> * paintScene::get_matrix() {
    return &matrixOfVertex;
}
void paintScene::slotChangeDeleteMode() {
    if(changeDeleteMode) {
        changeDeleteMode = false;
    }
    else {
        changeDeleteMode = true;
    }
}
vertex * paintScene::getVertex(int i) {
    return allVertex[i];
}
QVector <vertex *> * paintScene::getAllVertex() {
    return &allVertex;
}
int paintScene::getCount() {
    return count;
}
void paintScene::slotFunc() {
    emit signalFunc();
}
void paintScene::slotDelFunc() {
    emit signalDelFunc();
}


