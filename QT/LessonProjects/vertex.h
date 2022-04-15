#ifndef VERTEX_H
#define VERTEX_H

#include <QtWidgets>
class vertex : public QGraphicsItem {
private:
    enum {nPenWidth = 3};
public:
    virtual QRectF boundingRect() const {
        QPointF ptPosition(-10 - nPenWidth, -10 -nPenWidth);
        QSizeF size(20 + nPenWidth * 2, 20 + nPenWidth * 2);
        return QRectF(ptPosition, size);
    }
    virtual void paint(QPainter* ppainter, const QStyleOptionGraphicsItem*, QWidget*) {
        ppainter->save();
        ppainter->setPen(QPen(Qt::blue, nPenWidth));
        ppainter->drawEllipse(-10, -10, 20, 20);
        ppainter->restore();
    }
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* pe) {
        QApplication::setOverrideCursor(Qt::PointingHandCursor);
        QGraphicsItem::mousePressEvent(pe);
    }
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* pe) {
        QApplication::restoreOverrideCursor();
        QGraphicsItem::mouseReleaseEvent(pe);
    }
};

#endif // VERTEX_H
