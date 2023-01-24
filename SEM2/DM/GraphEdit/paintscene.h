#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QWidget>
#include <QObject>
#include <QGraphicsScene>
#include <vertex.h>
#include <edge.h>
#include <QSignalMapper>
#include <QGraphicsSceneMouseEvent>
class paintScene : public QGraphicsScene
{
    Q_OBJECT
public:
    paintScene(QObject * parent = 0);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    QMap <int, QMap <int, vertex *>> * get_matrix();
    void setCount(int _count);
    int getCount();
    vertex * getVertex(int i);
    QVector <vertex *> * getAllVertex();
public slots:
    void slotChangeDeleteMode();
    void slotFunc();
    void slotDelFunc();
signals:
    void signalFromScene(QMap <int, QMap <int, vertex *>> * _matrixOfVertex);
    void generate();
    void signalFunc();
    void signalDelFunc();
private:
    edge * buf;
    vertex * bufV;
    bool addingEdge = false;
    bool movingVertex = false;
    qint16 count = 0;
    QMap <int, QMap <int, vertex *>> matrixOfVertex;
    QVector <vertex *> allVertex;
    QSize sizeOfMatrix;
    bool changeDeleteMode = false;
};

#endif // PAINTSCENE_H
