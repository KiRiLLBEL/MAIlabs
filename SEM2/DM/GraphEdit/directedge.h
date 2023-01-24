#ifndef DIRECTEDGE_H
#define DIRECTEDGE_H

#include <QWidget>
#include <QGraphicsItem>
#include <QPainter>
class directvertex;

class directedge : public QGraphicsItem
{
public:
    enum {Type = UserType + 4};
    virtual int type() const {
        return Type;
    }
    directedge(QPointF pos, QPointF mousePos);
    QPointF Pos;
    QPointF mousePos;
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *ppainter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setConnection();
    void setConnectionStart(bool input);
    void setConnectionEnd(bool input);
    bool getConnectionStart();
    bool getConnectionEnd();
    void changePos(QPointF pos);
    void changeInput(QPointF pos);
    void changeOutput(QPointF pos);
    void componentIn(QColor colour);
    void componentOut();
    directvertex * input;
    directvertex * output;
    QColor componentColor;
    qreal arrowSize = 10;
    bool connection = false;
    bool connectEnd = true;
    bool connectStart = false;
    bool component = false;
};

#endif // EDGE_H

