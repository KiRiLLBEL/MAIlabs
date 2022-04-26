#ifndef PAINT_H
#define PAINT_H

#include <QWidget>
#include <QTimer>
#include <QResizeEvent>

#include <paintscene.h>

namespace Ui {
    class Paint;
}
class Paint : QWidget
{
    Q_OBJECT
public:
    Paint(QWidget *parent = 0);
    ~Paint();
private:
    Ui::Paint *ui;
    QTimer *timer;
    paintScene *scene;
    void resizeEvent(QResizeEvent * event);
private slots:
    void slotTimer();
};

#endif // PAINT_H
