//
// Created by kiril on 03.12.2023.
//

#include "MovablePoint.h"

MovablePoint::MovablePoint(QGraphicsItem* parent)
        : QObject(), QGraphicsEllipseItem(-5, -5, 10, 10, parent) {
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setBrush(Qt::red);
}


QVariant MovablePoint::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == ItemPositionChange && scene()) {
        emit positionChanged();
    }
    return QGraphicsItem::itemChange(change, value);
}
