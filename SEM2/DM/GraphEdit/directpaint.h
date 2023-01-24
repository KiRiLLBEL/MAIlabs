#ifndef DIRECTPAINT_H
#define DIRECTPAINT_H

#include <QWidget>
#include <QGraphicsScene>
#include "directpaintscene.h"
QT_BEGIN_NAMESPACE
namespace Ui { class directPaint; }
QT_END_NAMESPACE

class directPaint : public QWidget
{
    Q_OBJECT

public:
    directPaint(QWidget *parent = nullptr);
    ~directPaint();
    directpaintScene * get_scene();
public slots:
    void changeColor();
    void clearAll();
private:
    Ui::directPaint *ui;
    directpaintScene * scene;
    bool deleteToggled = false;
};
#endif // PAINT_H
