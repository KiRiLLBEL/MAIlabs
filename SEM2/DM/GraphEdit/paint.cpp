#include "paint.h"
#include "ui_paint.h"
#include "zoom.h"
#include "myview.h"
Paint::Paint(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Paint)
{
    ui->setupUi(this);
    myview * vi = new myview(this);
    scene = new paintScene(vi);
    ui->verticalLayout->addWidget(vi);
    //qDebug() << vi->height() << vi->width();
    vi->setScene(scene);
    vi->setRenderHint(QPainter::Antialiasing);
    vi->setCacheMode(QGraphicsView::CacheNone);
    vi->setOptimizationFlags(QGraphicsView::DontAdjustForAntialiasing|QGraphicsView::DontSavePainterState);
    vi->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
//    ui->graphicsView->setScene(scene);
//    Graphics_view_zoom* z = new Graphics_view_zoom(ui->graphicsView);
//    z->set_modifiers(Qt::NoModifier);
//    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
//    ui->graphicsView->horizontalScrollBar();
//    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
//    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    scene->setSceneRect(0, 0, 500, 500);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    connect(ui->deleteButton, SIGNAL(clicked()), scene, SLOT(slotChangeDeleteMode()));
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(changeColor()));
    connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(clearAll()));
    connect(scene, SIGNAL(generate()), this, SLOT(clearAll()));
    connect(ui->funcButton, &QPushButton::clicked, scene, &paintScene::slotFunc);
    connect(ui->delFuncButton, &QPushButton::clicked, scene, &paintScene::slotDelFunc);
}

Paint::~Paint()
{
    delete ui;
}
paintScene * Paint::get_scene() {
    return scene;
}
void Paint::changeColor() {
    if(deleteToggled) {
        ui->deleteButton->setStyleSheet("* QPushButton { background-color: white;  border: 2px solid #8f8f91; border-radius: 6px;}");
        deleteToggled = false;
    }
    else {
        ui->deleteButton->setStyleSheet("* QPushButton { background-color: red;  border: 2px solid #8f8f91; border-radius: 6px;}");
        deleteToggled = true;
    }
}
void Paint::clearAll() {
    get_scene()->setCount(0);
    get_scene()->clear();
    get_scene()->get_matrix()->clear();
    get_scene()->getAllVertex()->clear();
    emit get_scene()->signalFromScene(get_scene()->get_matrix());
}
