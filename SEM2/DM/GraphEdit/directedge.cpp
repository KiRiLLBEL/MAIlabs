#include "directedge.h"
#include "vertex.h"
directedge::directedge(QPointF pos, QPointF MousePos) {
    setAcceptHoverEvents(true);
    Pos.setX(pos.x());
    Pos.setY(pos.y());
    setZValue(0);
    mousePos = MousePos;
    setCacheMode(NoCache);
}
QRectF directedge::boundingRect() const {
    qreal penWidth = 3;
    qreal extra = (penWidth + arrowSize) / 2.0;
    return QRectF(Pos, QSizeF(mousePos.x()  - Pos.x(), mousePos.y() - Pos.y())).normalized().adjusted(-extra, -extra, extra, extra);
}
void directedge::paint(QPainter *ppainter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (!connection){
        if (!component) {
            ppainter->setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        } else {
            ppainter->setPen(QPen(componentColor, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        }
        ppainter->setBrush(Qt::black);
        QLineF line(Pos, mousePos);
        if (qFuzzyCompare(line.length(), qreal(0.)))
            return;
        double angle = std::atan2(-line.dy(), line.dx());
        QLineF newLine = QLineF::fromPolar(line.length() - 25, line.angle());
        newLine.translate(line.x2() - newLine.x2(), line.y2() - newLine.y2());
        QPointF destArrowP1 = line.p2() + QPointF(sin(angle - M_PI / 3) * arrowSize,                                              cos(angle - M_PI / 3) * arrowSize);
        QPointF destArrowP2 = line.p2() + QPointF(sin(angle - M_PI + M_PI / 3) * arrowSize,
                                                  cos(angle - M_PI + M_PI / 3) * arrowSize);
        if (!component) {
            ppainter->setBrush(Qt::black);
        }
        else {
            ppainter->setBrush(componentColor);
        }
        ppainter->drawLine(line);
        ppainter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
    }else {
        if (!component) {
            ppainter->setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        } else {
            ppainter->setPen(QPen(componentColor, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        }
        ppainter->setBrush(Qt::black);
        QLineF line(Pos, mousePos);
        if (qFuzzyCompare(line.length(), qreal(0.)))
            return;
        if (line.length() < 50)
            return;
        double angle = std::atan2(-line.dy(), line.dx());
        QLineF newLine = QLineF::fromPolar(line.length() - 50, line.angle());
        newLine.translate(line.center().x() - newLine.center().x(), line.center().y() - newLine.center().y());
        line = newLine;
        QPointF sourceArrowP1;
        QPointF sourceArrowP2;
        if(connectStart){
            sourceArrowP1 = line.p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                                        cos(angle + M_PI / 3) * arrowSize);
            sourceArrowP2 = line.p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                                        cos(angle + M_PI - M_PI / 3) * arrowSize);
        }
        QPointF destArrowP1;
        QPointF destArrowP2;
        if(connectEnd) {
            destArrowP1 = line.p2() + QPointF(sin(angle - M_PI / 3) * arrowSize,                                              cos(angle - M_PI / 3) * arrowSize);
            destArrowP2 = line.p2() + QPointF(sin(angle - M_PI + M_PI / 3) * arrowSize,
                                                     cos(angle - M_PI + M_PI / 3) * arrowSize);
        }
        if (!component) {
            ppainter->setBrush(Qt::black);
        }
        else {
            ppainter->setBrush(componentColor);
        }
        ppainter->drawLine(line);
        if(connectStart){
            ppainter->drawPolygon(QPolygonF() << line.p1() << sourceArrowP1 << sourceArrowP2);
        }
        if(connectEnd){
            ppainter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
        }
}
}
void directedge::changePos(QPointF pos) {
    prepareGeometryChange();
    mousePos.setX(pos.x());
    mousePos.setY(pos.y());
}
void directedge::changeInput(QPointF pos) {
    prepareGeometryChange();
    mousePos.setX(pos.x() + 25);
    mousePos.setY(pos.y() + 25);
}
void directedge::changeOutput(QPointF pos) {
    prepareGeometryChange();
    Pos.setX(pos.x() + 25);
    Pos.setY(pos.y() + 25);
}
void directedge::setConnection() {
    connection = true;
    update();
}
void directedge::setConnectionStart(bool input) {
    connectStart = input;
    update();
}
void directedge::setConnectionEnd(bool input) {
    connectEnd = input;
    update();
}
bool directedge::getConnectionStart() {
    return connectStart;
}
bool directedge::getConnectionEnd() {
    return connectEnd;
}
void directedge::componentIn(QColor colour) {
    if(!component) {
        component = true;
        componentColor = colour;
        update();
    }
}
void directedge::componentOut() {
    component = false;
    update();
}
