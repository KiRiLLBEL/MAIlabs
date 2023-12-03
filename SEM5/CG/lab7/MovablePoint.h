//
// Created by kiril on 03.12.2023.
//

#ifndef MOVABLEPOINT_H
#define MOVABLEPOINT_H

#include <QGraphicsScene>
#include <QGraphicsPathItem>
#include <QPainterPath>


class MovablePoint : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
public:
    MovablePoint(QGraphicsItem* parent = nullptr);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    signals:
    void positionChanged();
};




#endif //MOVABLEPOINT_H
