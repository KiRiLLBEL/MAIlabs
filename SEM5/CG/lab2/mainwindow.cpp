#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "parser.h"
#include <QFileDialog>
#include "canvas.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget->heightStart = ui->widget->height();
    ui->widget->widthStart = ui->widget->width();
    QMenu* fileMenu = ui->menubar->addMenu(tr("&File"));
    auto* openAction = new QAction(tr("Open OBJ file"), this);
    connect(openAction, &QAction::triggered, this,[this](){
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open OBJ file"), "", tr("OBJ Files (*.obj)"));
        if(!fileName.isEmpty()) {
            this->obj = CreateObjectFromFile(fileName);
            ui->widget->addObject(this->obj);
        }
    });
    fileMenu->addAction(openAction);
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

