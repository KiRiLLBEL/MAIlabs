//
// Created by kiril on 03.12.2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Mainwindow.h" resolved

#include "mainwindow.h"
#include "ui_Mainwindow.h"
#include "BezzierCurve.h"

Mainwindow::Mainwindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::Mainwindow) {
    ui->setupUi(this);
    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->View->setScene(scene);
    ui->View->setRenderHint(QPainter::Antialiasing);
    BezierCurve* curve = new BezierCurve(scene);
}

Mainwindow::~Mainwindow() {
    delete ui;
}
