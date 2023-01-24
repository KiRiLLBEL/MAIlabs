#ifndef PAINT_H
#define PAINT_H

#include <QWidget>
#include <QGraphicsScene>
#include "paintscene.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Paint; }
QT_END_NAMESPACE

class Paint : public QWidget
{
    Q_OBJECT

public:
    Paint(QWidget *parent = nullptr);
    ~Paint();
    paintScene * get_scene();
public slots:
    void changeColor();
    void clearAll();
private:
    Ui::Paint *ui;
    paintScene * scene;
    bool deleteToggled = false;
};
#endif // PAINT_H
