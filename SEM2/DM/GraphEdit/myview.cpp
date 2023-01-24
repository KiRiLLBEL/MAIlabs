#include "myview.h"
#include <QKeyEvent>
#include <QScrollBar>
#include <QApplication>
myview::myview(QWidget *parent) : QGraphicsView(parent)
{

}
void myview::keyPressEvent(QKeyEvent *event)
{
     switch (event->key()) {
     case Qt::Key_Plus:
         scaleView(qreal(1.2));
         break;
     case Qt::Key_Minus:
         scaleView(1 / qreal(1.2));
         break;
     default:
         QGraphicsView::keyPressEvent(event);
     }
}
void myview::scaleView(qreal scaleFactor)
{
     qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
     if (factor < 0.07 || factor > 100)
         return;

     scale(scaleFactor, scaleFactor);
}
void myview::wheelEvent(QWheelEvent *event)
{
    if (event->modifiers().testFlag(Qt::ControlModifier)) {
          scaleView(pow(2., -event->angleDelta().y() / 240.0));
     }
}
void myview::zoomIn()
{
    scaleView(qreal(1.2));
}

void myview::zoomOut()
{
    scaleView(1 / qreal(1.2));
}
void myview::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::MiddleButton)
    {
        qDebug() << "myview mouse press";
        QApplication::setOverrideCursor(Qt::ClosedHandCursor);
        middleMousePressed = true;
        _panStartX = event->x();
        _panStartY = event->y();
        event->accept();
        return;
    }
    QGraphicsView::mousePressEvent(event);
    event->ignore();
}

void myview::mouseReleaseEvent(QMouseEvent *event){
    if (event->button() == Qt::MiddleButton)
    {
        //qDebug() << "myview mouse release";
        middleMousePressed = false;
        QApplication::restoreOverrideCursor();
    }
    QGraphicsView::mouseReleaseEvent(event);
    event->ignore();
}

void myview::mouseMoveEvent(QMouseEvent *event){
    if (middleMousePressed)
    {
        //qDebug() << event->pos();
        //qDebug() << "myview mouse move";
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - (event->x() - _panStartX));
        verticalScrollBar()->setValue(verticalScrollBar()->value() - (event->y() - _panStartY));
        _panStartX = event->x();
        _panStartY = event->y();

    }
    QGraphicsView::mouseMoveEvent(event);
    event->ignore();
}
