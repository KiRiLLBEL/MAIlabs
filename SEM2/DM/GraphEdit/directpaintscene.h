#ifndef DIRECTPAINTSCENE_H
#define DIRECTPAINTSCENE_H

#include <QWidget>
#include <QObject>
#include <QGraphicsScene>
#include <directvertex.h>
#include <directedge.h>
#include <QSignalMapper>
#include <QGraphicsSceneMouseEvent>
class directpaintScene : public QGraphicsScene
{
    Q_OBJECT
public:
    directpaintScene(QObject * parent = 0);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    QMap <int, QMap <int, directedge *>> * get_matrix();
    void setCount(int _count);
    int getCount();
    directvertex * getVertex(int i);
    QVector <directvertex *> * getAllVertex();
public slots:
    void slotChangeDeleteMode();
    void slotFunc();
    void slotDelFunc();
signals:
    void signalFromScene(QMap <int, QMap <int, directedge *>> * _matrixOfVertex);
    void generate();
    void signalFunc();
    void signalDelFunc();
private:
    directedge * buf;
    directvertex * bufV;
    bool addingEdge = false;
    bool movingVertex = false;
    qint16 count = 0;
    QMap <int, QMap <int, directedge *>> matrixOfVertex;
    QVector <directvertex *> allVertex;
    QSize sizeOfMatrix;
    bool changeDeleteMode = false;
};

#endif // PAINTSCENE_H
