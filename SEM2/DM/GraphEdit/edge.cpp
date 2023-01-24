#include "edge.h"
#include "vertex.h"
edge::edge(QPointF pos, QPointF MousePos) {
    setAcceptHoverEvents(true);
    Pos.setX(pos.x());
    Pos.setY(pos.y());
    setZValue(0);
    mousePos = MousePos;
    setCacheMode(NoCache);
}
QRectF edge::boundingRect() const {
    return QRectF(Pos, QSizeF(mousePos.x()  - Pos.x(), mousePos.y() - Pos.y())).normalized().adjusted(-1, -1, 1, 1);
}
void edge::paint(QPainter *ppainter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if(!component){
        ppainter->setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        ppainter->setBrush(Qt::black);
    }
    else {
        ppainter->setPen(QPen(componentColor, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        ppainter->setBrush(componentColor);
    }
    ppainter->drawLine(Pos, mousePos);
}
void edge::changePos(QPointF pos) {
    prepareGeometryChange();
    mousePos.setX(pos.x());
    mousePos.setY(pos.y());
}
void edge::changeInput(QPointF pos) {
    prepareGeometryChange();
    mousePos.setX(pos.x() + 25);
    mousePos.setY(pos.y() + 25);
}
void edge::changeOutput(QPointF pos) {
    prepareGeometryChange();
    Pos.setX(pos.x() + 25);
    Pos.setY(pos.y() + 25);
}
