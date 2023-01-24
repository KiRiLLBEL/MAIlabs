#include "directpaintscene.h"
#include "directvertex.h"
#include "directedge.h"
#include "QGraphicsView"
directpaintScene::directpaintScene(QObject * parent) : QGraphicsScene(parent)
{
    sizeOfMatrix.setHeight(0);
    sizeOfMatrix.setWidth(0);
}
void directpaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (changeDeleteMode == false) {
        QTransform tr;
        if ((itemAt(event->scenePos(), tr) == 0 ||  qgraphicsitem_cast<directedge *>(itemAt(event->scenePos(), tr))) && event->button() == Qt::LeftButton) {
            directvertex * v = new directvertex(event->scenePos(), ++count);
            QMap <int, directedge *> m;
            m.insert(count - 1, NULL);
            matrixOfVertex.insert(count - 1, m);
            emit signalFromScene(&matrixOfVertex);
            allVertex.push_back(v);
            addItem(v);
            //qDebug() << matrixOfVertex;
            v->setPos(QPointF(event->scenePos().x() - 25, event->scenePos().y() - 25));
        }
        else {
            if(event->button() == Qt::RightButton && addingEdge == false) {
                directvertex * parent = qgraphicsitem_cast<directvertex *>(itemAt(event->scenePos(), tr));
                if (parent != NULL && count > 1) {
                    directedge * e = new directedge(QPointF(parent->pos().x() + 25, parent->pos().y() + 25), event->scenePos());
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
                    directvertex * parent = qgraphicsitem_cast<directvertex *>(itemAt(event->scenePos(), tr));
                    if (parent != NULL && parent != bufV) {
                        if(matrixOfVertex[parent->getNumber() - 1][bufV->getNumber() - 1] == NULL && matrixOfVertex[bufV->getNumber() - 1][parent->getNumber() - 1] == NULL) {
                            buf->changePos(QPointF(parent->pos().x() + 25, parent->pos().y() + 25));
                            buf->setConnection();
                            buf->update();
                            buf->input = bufV;
                            buf->output = parent;
                            matrixOfVertex[bufV->getNumber() - 1].insert(parent->getNumber() - 1, buf);
//                            matrixOfVertex[parent->getNumber() - 1].insert(bufV->getNumber() - 1, bufV);
                            emit signalFromScene(&matrixOfVertex);
                            //qDebug() << matrixOfVertex;
                            bufV->Push_EdgeOut(buf);
                            parent->Push_EdgeIn(buf);
                            addingEdge = false;
                        } else {
                            if (matrixOfVertex[bufV->getNumber() - 1][parent->getNumber() - 1] != NULL) {
                                directedge * e = matrixOfVertex[bufV->getNumber() - 1][parent->getNumber() - 1];
                                if(e->output == bufV) {
                                    e->setConnectionStart(true);
                                    e->output->Push_EdgeIn(e);
                                    e->input->Push_EdgeOut(e);
                                    matrixOfVertex[parent->getNumber() - 1][bufV->getNumber() - 1] = e;
                                }
                            }
                            if (matrixOfVertex[parent->getNumber() - 1][bufV->getNumber() - 1] != NULL) {
                                directedge * e = matrixOfVertex[parent->getNumber() - 1][bufV->getNumber() - 1];
                                if(e->output == bufV) {
                                    e->setConnectionStart(true);
                                    e->output->Push_EdgeIn(e);
                                    e->input->Push_EdgeOut(e);
                                    matrixOfVertex[bufV->getNumber() - 1][parent->getNumber() - 1] = e;
                                }
                            }
                            removeItem(buf);
                            delete buf;
                            addingEdge = false;
                        }
                    }
                }
            }
        }
    }
    else {
        QTransform tr;
        if (qgraphicsitem_cast<directvertex *>(itemAt(event->scenePos(), tr)) != NULL && event->button() == Qt::LeftButton) {
            directvertex * vertexNow = qgraphicsitem_cast<directvertex *>(itemAt(event->scenePos(), tr));
            QSet <directedge *> all;
            for (int i = 0; i != count; ++i) {
                qDebug() << i + 1<<allVertex[i] << allVertex[i]->inputEdges << allVertex[i]->outputEdges;
            }
            qDebug() << "ok1";
            foreach (directedge * e, vertexNow->inputEdges) {
                e->input->outputEdges.removeOne(e);
                matrixOfVertex[e->input->getNumber() - 1].remove(vertexNow->getNumber() - 1);
                e->input->inputEdges.removeOne(e);
                matrixOfVertex[vertexNow->getNumber() - 1].remove(e->input->getNumber() - 1);
                removeItem(e);
                all.insert(e);
            }
            qDebug() << "ok2";
            foreach (directedge * e, vertexNow->outputEdges) {
                e->output->inputEdges.removeOne(e);
                matrixOfVertex[e->output->getNumber() - 1].remove(vertexNow->getNumber() - 1);
                e->output->outputEdges.removeOne(e);
                matrixOfVertex[(vertexNow->getNumber() - 1)].remove(e->output->getNumber() - 1);
                removeItem(e);
                all.insert(e);
            }
            qDebug() << "ok3";
            foreach (directedge * e, all) {
                delete e;
            }
            all.clear();
            qDebug() << "ok4";
            matrixOfVertex.remove(vertexNow->getNumber() - 1);
            int checkNumber = vertexNow->getNumber() - 1;
            for (int i = 0; i != matrixOfVertex.size() + 1; ++i) {
                if(i > checkNumber) {
                    matrixOfVertex.insert(i - 1, matrixOfVertex[i]);
                    allVertex[i]->changeNumber(i);
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
            removeItem(vertexNow);
//            for (int i = 0; i != allVertex.size(); ++i) {
//                if (i > checkNumber) {
//                    allVertex[i - 1] = allVertex[i];
//                }
//            }
            allVertex.remove(checkNumber);
            delete vertexNow;
            --count;
            qDebug() << "----------------";
            qDebug() << matrixOfVertex;
            qDebug() << "----------------";
            for (int i = 0; i != count; ++i) {
                qDebug() << i + 1<<allVertex[i] << allVertex[i]->inputEdges << allVertex[i]->outputEdges;
            }
            emit signalFromScene(&matrixOfVertex);
        }
    }
}
void directpaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
       QGraphicsScene::mouseMoveEvent(event);
       if (addingEdge) {
           buf->changePos(event->scenePos());
           buf->update();
       }

}
void directpaintScene::setCount(int _count) {
    count = _count;
}
QMap <int, QMap <int, directedge *>> * directpaintScene::get_matrix() {
    return &matrixOfVertex;
}
void directpaintScene::slotChangeDeleteMode() {
    if(changeDeleteMode) {
        changeDeleteMode = false;
    }
    else {
        changeDeleteMode = true;
    }
}
directvertex * directpaintScene::getVertex(int i) {
    return allVertex[i];
}
QVector <directvertex *> * directpaintScene::getAllVertex() {
    return &allVertex;
}
int directpaintScene::getCount() {
    return count;
}
void directpaintScene::slotFunc() {
    emit signalFunc();
}
void directpaintScene::slotDelFunc() {
    emit signalDelFunc();
}


