//
// Created by kiril on 14.11.2023.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class Mainwindow; }
QT_END_NAMESPACE

class Mainwindow : public QMainWindow {
Q_OBJECT

public:
    explicit Mainwindow(QWidget *parent = nullptr);
    ~Mainwindow() override;

private slots:
    void on_translateObjectX_valueChanged(double arg1);

    void on_translateObjectY_valueChanged(double arg1);

    void on_translateObjectZ_valueChanged(double arg1);

    void on_rotateObjectX_valueChanged(double arg1);

    void on_rotateObjectY_valueChanged(double arg1);

    void on_rotateObjectZ_valueChanged(double arg1);

    void on_changeSize_valueChanged(double arg1);

    void on_changeA_valueChanged(double arg1);

    void on_changeB_valueChanged(double arg1);

    void on_changeC_valueChanged(double arg1);

    void on_changeHPolygons_valueChanged(double arg1);

    void on_changeVPolygons_valueChanged(double arg1);

    void on_rotateCameraX_valueChanged(double arg1);

    void on_rotateCameraY_valueChanged(double arg1);

    void on_rotateCameraZ_valueChanged(double arg1);

    void on_translateCameraX_valueChanged(double arg1);

    void on_translateCameraY_valueChanged(double arg1);

    void on_translateCameraZ_valueChanged(double arg1);

    void on_setLightX_valueChanged(double arg1);

    void on_setLightY_valueChanged(double arg1);

    void on_setLightZ_valueChanged(double arg1);

    void on_changeAmbient_valueChanged(double arg1);

    void on_changeDiffuse_valueChanged(double arg1);

    void on_changeSpecular_valueChanged(double arg1);

    void on_changeShininess_valueChanged(double arg1);

    void on_changeAnimation_toggled(bool checked);

private:
    Ui::Mainwindow *ui;
};


#endif //MAINWINDOW_H
