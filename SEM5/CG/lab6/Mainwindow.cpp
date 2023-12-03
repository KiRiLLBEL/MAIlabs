//
// Created by kiril on 14.11.2023.
//
#include "Mainwindow.h"
#include "ui_Mainwindow.h"

Mainwindow::Mainwindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::Mainwindow) {
    ui->setupUi(this);
    ui->RenderScene->object = ui->RenderScene->ellipsoid.generate_mesh();
}

Mainwindow::~Mainwindow() {
    delete ui;
}

void Mainwindow::on_translateObjectX_valueChanged(double arg1)
{
    ui->RenderScene->rotateObjectX(arg1);
    ui->RenderScene->update();
}


void Mainwindow::on_translateObjectY_valueChanged(double arg1)
{
    ui->RenderScene->rotateObjectY(arg1);
    ui->RenderScene->update();
}


void Mainwindow::on_translateObjectZ_valueChanged(double arg1)
{
    ui->RenderScene->rotateObjectZ(arg1);
    ui->RenderScene->update();
}


void Mainwindow::on_rotateObjectX_valueChanged(double arg1)
{
    ui->RenderScene->translateObjectX(arg1);
    ui->RenderScene->update();
}


void Mainwindow::on_rotateObjectY_valueChanged(double arg1)
{
    ui->RenderScene->translateObjectY(arg1);
    ui->RenderScene->update();
}


void Mainwindow::on_rotateObjectZ_valueChanged(double arg1)
{
    ui->RenderScene->translateObjectZ(arg1);
    ui->RenderScene->update();
}


void Mainwindow::on_changeSize_valueChanged(double arg1)
{
    ui->RenderScene->scaleObject(arg1);
    ui->RenderScene->update();
}


void Mainwindow::on_changeA_valueChanged(double arg1)
{
    ui->RenderScene->ellipsoid.setA(arg1);
    ui->RenderScene->recreateObject();
    ui->RenderScene->update();
}


void Mainwindow::on_changeB_valueChanged(double arg1)
{
    ui->RenderScene->ellipsoid.setB(arg1);
    ui->RenderScene->recreateObject();
    ui->RenderScene->update();
}


void Mainwindow::on_changeC_valueChanged(double arg1)
{
    ui->RenderScene->ellipsoid.setC(arg1);
    ui->RenderScene->recreateObject();
    ui->RenderScene->update();
}


void Mainwindow::on_changeHPolygons_valueChanged(double arg1)
{
    ui->RenderScene->ellipsoid.setHResolution(arg1);
    ui->RenderScene->recreateObject();
    ui->RenderScene->update();
}


void Mainwindow::on_changeVPolygons_valueChanged(double arg1)
{
    ui->RenderScene->ellipsoid.setWResolution(arg1);
    ui->RenderScene->recreateObject();
    ui->RenderScene->update();
}




void Mainwindow::on_rotateCameraX_valueChanged(double arg1)
{
    ui->RenderScene->rotateCameraX(arg1);
    ui->RenderScene->update();
}


void Mainwindow::on_rotateCameraY_valueChanged(double arg1)
{
    ui->RenderScene->rotateCameraY(arg1);
    ui->RenderScene->update();
}


void Mainwindow::on_rotateCameraZ_valueChanged(double arg1)
{
    ui->RenderScene->rotateCameraZ(arg1);
    ui->RenderScene->update();
}


void Mainwindow::on_translateCameraX_valueChanged(double arg1)
{
    ui->RenderScene->translateCameraX(arg1);
    ui->RenderScene->update();
}


void Mainwindow::on_translateCameraY_valueChanged(double arg1)
{
    ui->RenderScene->translateCameraY(arg1);
    ui->RenderScene->update();
}


void Mainwindow::on_translateCameraZ_valueChanged(double arg1)
{
    ui->RenderScene->translateCameraZ(arg1);
    ui->RenderScene->update();
}


void Mainwindow::on_setLightX_valueChanged(double arg1)
{
    ui->RenderScene->moveLightX(arg1);
    ui->RenderScene->update();
}


void Mainwindow::on_setLightY_valueChanged(double arg1)
{
    ui->RenderScene->moveLightY(arg1);
    ui->RenderScene->update();
}


void Mainwindow::on_setLightZ_valueChanged(double arg1)
{
    ui->RenderScene->moveLightZ(arg1);
    ui->RenderScene->update();
}


void Mainwindow::on_changeAmbient_valueChanged(double arg1)
{
    ui->RenderScene->object.property.ambient = arg1;
    ui->RenderScene->update();
}


void Mainwindow::on_changeDiffuse_valueChanged(double arg1)
{
    ui->RenderScene->object.property.diffuse = arg1;
    ui->RenderScene->update();
}


void Mainwindow::on_changeSpecular_valueChanged(double arg1)
{
    ui->RenderScene->object.property.specular = arg1;
    ui->RenderScene->update();
}


void Mainwindow::on_changeShininess_valueChanged(double arg1)
{
    ui->RenderScene->object.property.shininess = arg1;
    ui->RenderScene->update();
}


void Mainwindow::on_changeAnimation_toggled(bool checked)
{
    if(checked)
        ui->RenderScene->startAnimation();
    else
        ui->RenderScene->stopAnimation();
    ui->RenderScene->update();
}

