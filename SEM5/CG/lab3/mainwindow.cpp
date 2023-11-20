#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "parser.h"
#include <QFileDialog>
#include <QDebug>
#include "canvas.h"
#include "ellipsoid.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget->heightStart = ui->widget->height();
    ui->widget->widthStart = ui->widget->width();
    this->obj = this->ellipsiod.generate_mesh();
    ui->widget->point_light = {0, 0, 0};
    ui->widget->addObject(this->obj);
    for(const Vertex& vertex: this->obj.vertices) {
        qDebug() << "Vertex: " << vertex.x << " " << vertex.y << " " << vertex.z << "\n";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Xrotate_valueChanged(double arg1)
{
    this->ui->widget->rotateXObjects(arg1 / 180 * M_PI);
    ui->widget->update();
}


void MainWindow::on_Yrotate_valueChanged(double arg1)
{
    this->ui->widget->rotateYObjects(arg1 / 180 * M_PI);
    ui->widget->update();
}


void MainWindow::on_Zrotate_valueChanged(double arg1)
{
    this->ui->widget->rotateZObjects(arg1 / 180 * M_PI);
    ui->widget->update();
}


void MainWindow::on_Scale_valueChanged(double arg1)
{
    this->ui->widget->scaleObjects(arg1);
    ui->widget->update();
}


void MainWindow::on_checkBox_stateChanged(int arg1)
{
    this->ui->widget->invisibleFaces = arg1;
    ui->widget->update();
}


void MainWindow::on_MXrotate_valueChanged(double arg1)
{
    this->ui->widget->camera.angle_x = (-arg1 / 180 * M_PI);
    ui->widget->update();
}

void MainWindow::on_MYrotate_valueChanged(double arg1)
{
    this->ui->widget->camera.angle_y = (-arg1 / 180 * M_PI);
    ui->widget->update();
}

void MainWindow::on_MZrotate_valueChanged(double arg1)
{
    this->ui->widget->camera.angle_z = (-arg1 / 180 * M_PI);
    ui->widget->update();
}


void MainWindow::on_moveX_valueChanged(double arg1)
{
    this->ui->widget->shiftXObjects(arg1);
    ui->widget->update();
}


void MainWindow::on_moveY_valueChanged(double arg1)
{
    this->ui->widget->shiftYObjects(arg1);
    ui->widget->update();
}


void MainWindow::on_moveZ_valueChanged(double arg1)
{
    this->ui->widget->shiftZObjects(arg1);
    ui->widget->update();
}


void MainWindow::on_MMoveX_valueChanged(double arg1)
{
    this->ui->widget->camera.x = -arg1;
    ui->widget->update();
}


void MainWindow::on_MMoveY_valueChanged(double arg1)
{
    this->ui->widget->camera.y = -arg1;
    ui->widget->update();
}


void MainWindow::on_MMoveZ_valueChanged(double arg1)
{
    this->ui->widget->camera.z = -arg1;
    ui->widget->update();
}


void MainWindow::on_changeA_valueChanged(double arg1)
{
    this->ellipsiod.setA(arg1);
    Object tmp = this->ellipsiod.generate_mesh();
    tmp.transform = this->ui->widget->object_on_scene.transform;
    tmp.property = this->ui->widget->object_on_scene.property;
    ui->widget->addObject(tmp);
    ui->widget->update();
}


void MainWindow::on_changeB_valueChanged(double arg1)
{
    this->ellipsiod.setB(arg1);
    Object tmp = this->ellipsiod.generate_mesh();
    tmp.transform = this->ui->widget->object_on_scene.transform;
    tmp.property = this->ui->widget->object_on_scene.property;
    ui->widget->addObject(tmp);
    ui->widget->update();
}


void MainWindow::on_changeC_valueChanged(double arg1)
{
    this->ellipsiod.setC(arg1);
    Object tmp = this->ellipsiod.generate_mesh();
    tmp.transform = this->ui->widget->object_on_scene.transform;
    tmp.property = this->ui->widget->object_on_scene.property;
    ui->widget->addObject(tmp);
    ui->widget->update();
}


void MainWindow::on_changeH_valueChanged(int arg1)
{
    this->ellipsiod.setHResolution(arg1);
    Object tmp = this->ellipsiod.generate_mesh();
    tmp.transform = this->ui->widget->object_on_scene.transform;
    tmp.property = this->ui->widget->object_on_scene.property;
    ui->widget->addObject(tmp);
    ui->widget->update();
}


void MainWindow::on_changeV_valueChanged(int arg1)
{
    this->ellipsiod.setWResolution(arg1);
    Object tmp = this->ellipsiod.generate_mesh();
    tmp.transform = this->ui->widget->object_on_scene.transform;
    tmp.property = this->ui->widget->object_on_scene.property;
    ui->widget->addObject(tmp);
    ui->widget->update();
}

void MainWindow::on_Xlight_valueChanged(double arg1)
{
    ui->widget->point_light.x = arg1;
    ui->widget->update();
}


void MainWindow::on_Ylight_valueChanged(double arg1)
{
    ui->widget->point_light.y = arg1;
    ui->widget->update();
}


void MainWindow::on_Zlight_valueChanged(double arg1)
{
    ui->widget->point_light.z = arg1;
    ui->widget->update();
}


void MainWindow::on_changAmbient_valueChanged(double arg1)
{
    this->ui->widget->object_on_scene.property.ambient = arg1;
    ui->widget->update();
}


void MainWindow::on_changeDiffuse_valueChanged(double arg1)
{
    this->ui->widget->object_on_scene.property.diffuse = arg1;
    ui->widget->update();
}


void MainWindow::on_changeSpecular_valueChanged(double arg1)
{
    this->ui->widget->object_on_scene.property.specular = arg1;
    ui->widget->update();
}


void MainWindow::on_changeShininess_valueChanged(double arg1)
{
    this->ui->widget->object_on_scene.property.shininess = arg1;
    ui->widget->update();
}

