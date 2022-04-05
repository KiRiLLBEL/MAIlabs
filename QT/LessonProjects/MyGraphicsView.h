#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QTimer>

class MyGraphicsView : public QGraphicsView {
public:
    explicit MyGraphicsView(QWidget *parent = 0);
    ~MyGraphicsView();
signals:
private slots:
    void slotAlarmTimer();
private:
    QGraphicsScene *scene;
    QGraphicsItemGroup *group_1;
    QGraphicsItemGroup *group_2;
    QTimer *timer;
private:
    void resizeEvent(QResizeEvent *event);
    void deleteItemsGroupFrom(QGraphicsItemGroup *group_1);
};

#endif // MYGRAPHICSVIEW_H
