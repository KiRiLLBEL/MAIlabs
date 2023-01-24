#include "directvertex.h"
#include "QGraphicsView"
directvertex::directvertex(QPointF pos, qint16 num) : number(num) {
    setAcceptDrops(true);
    setZValue(1);
    setAcceptHoverEvents(true);
    setCacheMode(NoCache);
//    Position.setX(pos.x() - 25);
//    Position.setY(pos.y() - 25);
    //qDebug() << Pos << pos;
}
QRectF directvertex::boundingRect() const {
    return QRectF(QPointF(0, 0), QSizeF(50, 50));
}
QPainterPath directvertex::shape() const
{
    QPainterPath path;
    path.addEllipse(0, 0, 50, 50);
    return path;
}
void directvertex::paint(QPainter *ppainter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (!component) {
        ppainter->setPen(Qt::NoPen);
        ppainter->setBrush(Qt::darkGray);
        ppainter->drawEllipse(QRectF(QPointF(0, 0), QSize(50, 50)));
        ppainter->setFont(QFont("Times", 14, QFont::Normal));
        ppainter->setPen(QPen(Qt::black, 2));
        ppainter->drawText(QRectF(0, 0, 50, 50), Qt::AlignCenter,  QString::number(number));
    }
    else {
        ppainter->setPen(Qt::NoPen);
        ppainter->setBrush(componentColor);
        ppainter->drawEllipse(QRectF(QPointF(0, 0), QSize(50, 50)));
        ppainter->setFont(QFont("Times", 14, QFont::Normal));
        ppainter->setPen(QPen(Qt::black, 2));
        ppainter->drawText(QRectF(0, 0, 50, 50), Qt::AlignCenter,  QString::number(number));
    }
}
void directvertex::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    setCursor(Qt::PointingHandCursor);
    QGraphicsItem::hoverEnterEvent(event);
}
void directvertex::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    setCursor(Qt::ArrowCursor);
    QGraphicsItem::hoverEnterEvent(event);
}
void directvertex::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    m_shiftMouseCoords = this->pos() - mapToScene(event->pos());
}
void directvertex::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsView * checkView = scene()->views().first();
        if (checkView->mapFromScene(event->scenePos()).x() >= 25
                && checkView->mapFromScene(event->scenePos()).y() >= 20
                && checkView->mapFromScene(event->scenePos()).x() <= checkView->width() - 30
                && checkView->mapFromScene(event->scenePos()).y() <= checkView->height() - 30) {
            this->setPos(mapToScene(event->pos() + m_shiftMouseCoords));
            for (directedge * v: inputEdges) {
                v->changeInput(mapToScene(event->pos() + m_shiftMouseCoords));
                v->update();
            }
            for (directedge * v: outputEdges) {
                v->changeOutput(mapToScene(event->pos() + m_shiftMouseCoords));
                v->update();
            }
        }
        else if (checkView->mapFromScene(event->scenePos()).x() > checkView->width() - 30 && checkView->mapFromScene(event->scenePos()).y() > checkView->height() - 30) {
            //qDebug() << "Stop1";
            setPos(checkView->mapToScene(QPoint(checkView->width() - 53, 0)).x(), checkView->mapToScene(QPoint(0, checkView->height() - 52)).y());
            for (directedge * v: inputEdges) {
                v->changeInput(QPointF(checkView->mapToScene(QPoint(checkView->width() - 53, 0)).x(), checkView->mapToScene(QPoint(0, checkView->height() - 52)).y()));
                v->update();
            }
            for (directedge * v: outputEdges) {
                v->changeOutput(QPointF(checkView->mapToScene(QPoint(checkView->width() - 53, 0)).x(), checkView->mapToScene(QPoint(0, checkView->height() - 52)).y()));
                v->update();
            }
        }
        else if (checkView->mapFromScene(event->scenePos()).x() < 25 && checkView->mapFromScene(event->scenePos()).y() < 25) {
            //qDebug() << "Stop2";
            setPos(checkView->mapToScene(QPoint(0, 0)).x(), checkView->mapToScene(QPoint(0, 0)).y());
            for (directedge * v: inputEdges) {
                v->changeInput(QPointF(checkView->mapToScene(QPoint(0, 0)).x(), checkView->mapToScene(QPoint(0, 0)).y()));
                v->update();
            }
            for (directedge * v: outputEdges) {
                v->changeOutput(QPointF(checkView->mapToScene(QPoint(0, 0)).x(), checkView->mapToScene(QPoint(0, 0)).y()));
                v->update();
            }
        }
        else if (checkView->mapFromScene(event->scenePos()).x() < 25 && checkView->mapFromScene(event->scenePos()).y() > checkView->height() - 30) {
            //qDebug() << "Stop0";
            setPos(checkView->mapToScene(QPoint(0, 0)).x(), checkView->mapToScene(QPoint(0, checkView->height() - 52)).y());
            for (directedge * v: inputEdges) {
                v->changeInput(QPointF(checkView->mapToScene(QPoint(0, 0)).x(), checkView->mapToScene(QPoint(0, checkView->height() - 52)).y()));
                v->update();
            }
            for (directedge * v: outputEdges) {
                v->changeOutput(QPointF(checkView->mapToScene(QPoint(0, 0)).x(), checkView->mapToScene(QPoint(0, checkView->height() - 52)).y()));
                v->update();
            }
        }
        else if (checkView->mapFromScene(event->scenePos()).x() > checkView->width() - 30 && checkView->mapFromScene(event->scenePos()).y() < 20) {
            //qDebug() << "Stop01";
            setPos(checkView->mapToScene(QPoint(checkView->width() - 53, 0)).x(), checkView->mapToScene(QPoint(0, 0)).y());
            for (directedge * v: inputEdges) {
                v->changeInput(QPointF(checkView->mapToScene(QPoint(checkView->width() - 53, 0)).x(), checkView->mapToScene(QPoint(0, 0)).y()));
                v->update();
            }
            for (directedge * v: outputEdges) {
                v->changeOutput(QPointF(checkView->mapToScene(QPoint(checkView->width() - 53, 0)).x(), checkView->mapToScene(QPoint(0, 0)).y()));
                v->update();
            }
        }
        else if (checkView->mapFromScene(event->scenePos()).x() < 25) {
            //qDebug() << "Stop3";
            setPos(checkView->mapToScene(QPoint(0, 0)).x(), mapToScene(event->pos() + m_shiftMouseCoords).y());
            for (directedge * v: inputEdges) {
                v->changeInput(QPointF(checkView->mapToScene(QPoint(0, 0)).x(), mapToScene(event->pos() + m_shiftMouseCoords).y()));
                v->update();
            }
            for (directedge * v: outputEdges) {
                v->changeOutput(QPointF(checkView->mapToScene(QPoint(0, 0)).x(), mapToScene(event->pos() + m_shiftMouseCoords).y()));
                v->update();
            }
        }
        else if (checkView->mapFromScene(event->scenePos()).y() < 20) {
            //qDebug() << "Stop4";
            setPos(mapToScene(event->pos() + m_shiftMouseCoords).x(), checkView->mapToScene(QPoint(0, 0)).y());
            for (directedge * v: inputEdges) {
                v->changeInput(QPointF(mapToScene(event->pos() + m_shiftMouseCoords).x(), checkView->mapToScene(QPoint(0, 0)).y()));
                v->update();
            }
            for (directedge * v: outputEdges) {
                v->changeOutput(QPointF(mapToScene(event->pos() + m_shiftMouseCoords).x(), checkView->mapToScene(QPoint(0, 0)).y()));
                v->update();
            }
        }
        else if (checkView->mapFromScene(event->scenePos()).x() > checkView->width() - 30) {
            //qDebug() << "Stop5";
            setPos(checkView->mapToScene(QPoint(checkView->width() - 53, 0)).x(), mapToScene(event->pos() + m_shiftMouseCoords).y());
            for (directedge * v: inputEdges) {
                v->changeInput(QPointF(checkView->mapToScene(QPoint(checkView->width() - 53, 0)).x(), mapToScene(event->pos() + m_shiftMouseCoords).y()));
                v->update();
            }
            for (directedge * v: outputEdges) {
                v->changeOutput(QPointF(checkView->mapToScene(QPoint(checkView->width() - 53, 0)).x(), mapToScene(event->pos() + m_shiftMouseCoords).y()));
                v->update();
            }
        }
        else if (checkView->mapFromScene(event->scenePos()).y() > checkView->height() - 30) {
            //qDebug() << "Stop6";
            setPos(mapToScene(event->pos() + m_shiftMouseCoords).x(), checkView->mapToScene(QPoint(0, checkView->height() - 52)).y());
            for (directedge * v: inputEdges) {
                v->changeInput(QPointF(mapToScene(event->pos() + m_shiftMouseCoords).x(), checkView->mapToScene(QPoint(0, checkView->height() - 52)).y()));
                v->update();
            }
            for (directedge * v: outputEdges) {
                v->changeOutput(QPointF(mapToScene(event->pos() + m_shiftMouseCoords).x(), checkView->mapToScene(QPoint(0, checkView->height() - 52)).y()));
                v->update();
            }
        }
//    else if (x() > 481)
//        setPos(481, y());

//    if (y() < 0)
//        setPos(x(), 0);
//    else if (y() > 270)
//        setPos(x(), 270);
}
void directvertex::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsView * checkView = scene()->views().first();
    if (checkView->mapFromScene(event->scenePos()).x() >= 25
            && checkView->mapFromScene(event->scenePos()).y() >= 20
            && checkView->mapFromScene(event->scenePos()).x() <= checkView->width() - 30
            && checkView->mapFromScene(event->scenePos()).y() <= checkView->height() - 30) {
        this->setPos(mapToScene(event->pos() + m_shiftMouseCoords));
        for (directedge * v: inputEdges) {
            v->changeInput(mapToScene(event->pos() + m_shiftMouseCoords));
            v->update();
        }
        for (directedge * v: outputEdges) {
            v->changeOutput(mapToScene(event->pos() + m_shiftMouseCoords));
            v->update();
        }
    }
    else if (checkView->mapFromScene(event->scenePos()).x() > checkView->width() - 30 && checkView->mapFromScene(event->scenePos()).y() > checkView->height() - 30) {
        //qDebug() << "Stop1";
        setPos(checkView->mapToScene(QPoint(checkView->width() - 53, 0)).x(), checkView->mapToScene(QPoint(0, checkView->height() - 52)).y());
        for (directedge * v: inputEdges) {
            v->changeInput(QPointF(checkView->mapToScene(QPoint(checkView->width() - 53, 0)).x(), checkView->mapToScene(QPoint(0, checkView->height() - 52)).y()));
            v->update();
        }
        for (directedge * v: outputEdges) {
            v->changeOutput(QPointF(checkView->mapToScene(QPoint(checkView->width() - 53, 0)).x(), checkView->mapToScene(QPoint(0, checkView->height() - 52)).y()));
            v->update();
        }
    }
    else if (checkView->mapFromScene(event->scenePos()).x() < 25 && checkView->mapFromScene(event->scenePos()).y() < 25) {
        //qDebug() << "Stop2";
        setPos(checkView->mapToScene(QPoint(0, 0)).x(), checkView->mapToScene(QPoint(0, 0)).y());
        for (directedge * v: inputEdges) {
            v->changeInput(QPointF(checkView->mapToScene(QPoint(0, 0)).x(), checkView->mapToScene(QPoint(0, 0)).y()));
            v->update();
        }
        for (directedge * v: outputEdges) {
            v->changeOutput(QPointF(checkView->mapToScene(QPoint(0, 0)).x(), checkView->mapToScene(QPoint(0, 0)).y()));
            v->update();
        }
    }
    else if (checkView->mapFromScene(event->scenePos()).x() < 25 && checkView->mapFromScene(event->scenePos()).y() > checkView->height() - 30) {
        //qDebug() << "Stop0";
        setPos(checkView->mapToScene(QPoint(0, 0)).x(), checkView->mapToScene(QPoint(0, checkView->height() - 52)).y());
        for (directedge * v: inputEdges) {
            v->changeInput(QPointF(checkView->mapToScene(QPoint(0, 0)).x(), checkView->mapToScene(QPoint(0, checkView->height() - 52)).y()));
            v->update();
        }
        for (directedge * v: outputEdges) {
            v->changeOutput(QPointF(checkView->mapToScene(QPoint(0, 0)).x(), checkView->mapToScene(QPoint(0, checkView->height() - 52)).y()));
            v->update();
        }
    }
    else if (checkView->mapFromScene(event->scenePos()).x() > checkView->width() - 30 && checkView->mapFromScene(event->scenePos()).y() < 20) {
        //qDebug() << "Stop01";
        setPos(checkView->mapToScene(QPoint(checkView->width() - 53, 0)).x(), checkView->mapToScene(QPoint(0, 0)).y());
        for (directedge * v: inputEdges) {
            v->changeInput(QPointF(checkView->mapToScene(QPoint(checkView->width() - 53, 0)).x(), checkView->mapToScene(QPoint(0, 0)).y()));
            v->update();
        }
        for (directedge * v: outputEdges) {
            v->changeOutput(QPointF(checkView->mapToScene(QPoint(checkView->width() - 53, 0)).x(), checkView->mapToScene(QPoint(0, 0)).y()));
            v->update();
        }
    }
    else if (checkView->mapFromScene(event->scenePos()).x() < 25) {
        //qDebug() << "Stop3";
        setPos(checkView->mapToScene(QPoint(0, 0)).x(), mapToScene(event->pos() + m_shiftMouseCoords).y());
        for (directedge * v: inputEdges) {
            v->changeInput(QPointF(checkView->mapToScene(QPoint(0, 0)).x(), mapToScene(event->pos() + m_shiftMouseCoords).y()));
            v->update();
        }
        for (directedge * v: outputEdges) {
            v->changeOutput(QPointF(checkView->mapToScene(QPoint(0, 0)).x(), mapToScene(event->pos() + m_shiftMouseCoords).y()));
            v->update();
        }
    }
    else if (checkView->mapFromScene(event->scenePos()).y() < 20) {
        //qDebug() << "Stop4";
        setPos(mapToScene(event->pos() + m_shiftMouseCoords).x(), checkView->mapToScene(QPoint(0, 0)).y());
        for (directedge * v: inputEdges) {
            v->changeInput(QPointF(mapToScene(event->pos() + m_shiftMouseCoords).x(), checkView->mapToScene(QPoint(0, 0)).y()));
            v->update();
        }
        for (directedge * v: outputEdges) {
            v->changeOutput(QPointF(mapToScene(event->pos() + m_shiftMouseCoords).x(), checkView->mapToScene(QPoint(0, 0)).y()));
            v->update();
        }
    }
    else if (checkView->mapFromScene(event->scenePos()).x() > checkView->width() - 30) {
        //qDebug() << "Stop5";
        setPos(checkView->mapToScene(QPoint(checkView->width() - 53, 0)).x(), mapToScene(event->pos() + m_shiftMouseCoords).y());
        for (directedge * v: inputEdges) {
            v->changeInput(QPointF(checkView->mapToScene(QPoint(checkView->width() - 53, 0)).x(), mapToScene(event->pos() + m_shiftMouseCoords).y()));
            v->update();
        }
        for (directedge * v: outputEdges) {
            v->changeOutput(QPointF(checkView->mapToScene(QPoint(checkView->width() - 53, 0)).x(), mapToScene(event->pos() + m_shiftMouseCoords).y()));
            v->update();
        }
    }
    else if (checkView->mapFromScene(event->scenePos()).y() > checkView->height() - 30) {
        //qDebug() << "Stop6";
        setPos(mapToScene(event->pos() + m_shiftMouseCoords).x(), checkView->mapToScene(QPoint(0, checkView->height() - 52)).y());
        for (directedge * v: inputEdges) {
            v->changeInput(QPointF(mapToScene(event->pos() + m_shiftMouseCoords).x(), checkView->mapToScene(QPoint(0, checkView->height() - 52)).y()));
            v->update();
        }
        for (directedge * v: outputEdges) {
            v->changeOutput(QPointF(mapToScene(event->pos() + m_shiftMouseCoords).x(), checkView->mapToScene(QPoint(0, checkView->height() - 52)).y()));
            v->update();
        }
    }
}
void directvertex::Push_EdgeIn(directedge * e) {
    inputEdges.push_back(e);
}
void directvertex::Push_EdgeOut(directedge * e) {
    outputEdges.push_back(e);
}
qint16 directvertex::getNumber() {
    return number;
}
void directvertex::changeNumber(int number) {
    this->number = number;
    update();
}
void directvertex::componentIn(QColor colour) {
    if(!component) {
        component = true;
        componentColor = colour;
        update();
    }
}
void directvertex::componentOut() {
    component = false;
    update();
}
bool directvertex::getCollison() {
    return collision;
}
void directvertex::setCollison(bool input) {
    collision = input;
}
