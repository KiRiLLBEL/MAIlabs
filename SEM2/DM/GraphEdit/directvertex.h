#ifndef DIRECTVERTEX_H
#define DIRECTVERTEX_H
#include <QObject>
#include <QWidget>
#include <QGraphicsItem>
#include <QPainter>
#include <QObject>
#include <QApplication>
#include <directedge.h>
#include <QGraphicsSceneDragDropEvent>
class directvertex : public QGraphicsItem
{
public:
    enum {Type = UserType + 3};
    directvertex(QPointF pos, qint16 num);
    qint16 getNumber();
    void changeNumber(int number);
    void componentIn(QColor colour);
    void componentOut();
    void Push_EdgeIn(directedge * e);
    void Push_EdgeOut(directedge * e);
    bool getCollison();
    void setCollison(bool input);
    QList <directedge *> inputEdges;
    QList <directedge *> outputEdges;
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
    QPointF save;
    bool component = false;
    bool collision = false;
};

#endif // VERTEX_H
