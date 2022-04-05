#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QRegularExpressionValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myPicture = new MyGraphicsView();
    ui->graphicLayout->addWidget(myPicture);

}

MainWindow::~MainWindow()
{
    delete ui;
}
