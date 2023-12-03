//
// Created by kiril on 03.12.2023.
//

#ifndef BEZZIERCURVE_H
#define BEZZIERCURVE_H

#include <QPainterPath>
#include "MovablePoint.h"

class BezierCurve : public QObject {
    Q_OBJECT

public:
    BezierCurve(QGraphicsScene* scene);

    public slots:
        void updatePath();

private:
    QGraphicsScene* m_scene;
    MovablePoint* m_points[3];
    QGraphicsPathItem* m_pathItem;
    QGraphicsLineItem* m_dashedLine1;
    QGraphicsLineItem* m_dashedLine2;
};


#endif //BEZZIERCURVE_H
