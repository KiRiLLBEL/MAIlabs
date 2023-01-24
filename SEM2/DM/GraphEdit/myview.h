#ifndef MYVIEW_H
#define MYVIEW_H

#include <QGraphicsView>
class myview : public QGraphicsView
{
    Q_OBJECT

    public:
        myview(QWidget *parent = nullptr);

    public slots:
        void zoomIn();
        void zoomOut();

    protected:
        void keyPressEvent(QKeyEvent *event) override;
        void wheelEvent(QWheelEvent *event) override;
        void scaleView(qreal scaleFactor);
        void mousePressEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;
    private:
        bool middleMousePressed = false;
        int _panStartX;
        int _panStartY;
};

#endif // MYVIEW_H
