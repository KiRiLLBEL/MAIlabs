//
// Created by kiril on 03.12.2023.
//

#include "BezzierCurve.h"

BezierCurve::BezierCurve(QGraphicsScene* scene) : QObject(scene), m_scene(scene) {

    m_pathItem = new QGraphicsPathItem();
    m_pathItem->setPen(QPen(Qt::white, 3));
    m_scene->addItem(m_pathItem);

    m_dashedLine1 = new QGraphicsLineItem();
    m_dashedLine1->setPen(QPen(Qt::white, 1, Qt::DashLine));
    m_scene->addItem(m_dashedLine1);

    m_dashedLine2 = new QGraphicsLineItem();
    m_dashedLine2->setPen(QPen(Qt::white, 1, Qt::DashLine));
    m_scene->addItem(m_dashedLine2);
    for (int i = 0; i < 3; ++i) {
        m_points[i] = new MovablePoint();
        m_scene->addItem(m_points[i]);
        connect(m_points[i], &MovablePoint::positionChanged, this, &BezierCurve::updatePath);
    }

    m_points[0]->setPos(50, 50);
    m_points[1]->setPos(100, 100);
    m_points[2]->setPos(150, 50);

    updatePath();
}

void BezierCurve::updatePath() {
    QPainterPath path;
    path.moveTo(m_points[0]->pos());
    path.quadTo(m_points[1]->pos(), m_points[2]->pos());
    m_pathItem->setPath(path);

    m_dashedLine1->setLine(QLineF(m_points[0]->pos(), m_points[1]->pos()));
    m_dashedLine2->setLine(QLineF(m_points[1]->pos(), m_points[2]->pos()));
}