#ifndef VERTEX_H
#define VERTEX_H
#include <QObject>
#include <QWidget>
#include <QGraphicsItem>
#include <QPainter>
#include <QObject>
#include <QApplication>
#include <edge.h>
#include <QGraphicsSceneDragDropEvent>
class vertex : public QGraphicsItem
{
public:
    enum {Type = UserType + 1};
    vertex(QPointF pos, qint16 num);
    qint16 getNumber();
    void changeNumber(int number);
    void componentIn(QColor colour);
    void componentOut();
    void Push_EdgeIn(edge * e);
    void Push_EdgeOut(edge * e);
    QList <edge *> inputEdges;
    QList <edge *> outputEdges;
private:
    virtual int type() const {
        return Type;
    }
    virtual QRectF boundingRect() const;
    virtual QPainterPath shape() const;
    virtual void paint(QPainter *ppainter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    QPointF m_shiftMouseCoords;
    QColor componentColor;
    qint16 number;
    bool component = false;
};

#endif // VERTEX_H
