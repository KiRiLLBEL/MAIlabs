#ifndef EDGE_H
#define EDGE_H

#include <QWidget>
#include <QGraphicsItem>
#include <QPainter>
class vertex;

class edge : public QGraphicsItem
{
public:
    enum {Type = UserType + 2};
    virtual int type() const {
        return Type;
    }
    edge(QPointF pos, QPointF mousePos);
    QPointF Pos;
    QPointF mousePos;
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *ppainter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void changePos(QPointF pos);
    void changeInput(QPointF pos);
    void changeOutput(QPointF pos);
    vertex * input;
    vertex * output;
    bool component = false;
    QColor componentColor;
};

#endif // EDGE_H
