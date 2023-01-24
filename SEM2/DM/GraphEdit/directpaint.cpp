#include "directpaint.h"
#include "ui_directpaint.h"
#include "zoom.h"
#include "myview.h"
directPaint::directPaint(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::directPaint)
{
    ui->setupUi(this);
    myview * vi = new myview(this);
    scene = new directpaintScene(vi);
    ui->verticalLayout->addWidget(vi);
    //qDebug() << vi->height() << vi->width();
    vi->setScene(scene);
    vi->setRenderHint(QPainter::Antialiasing);
    vi->setCacheMode(QGraphicsView::CacheNone);
    vi->setOptimizationFlags(QGraphicsView::DontAdjustForAntialiasing|QGraphicsView::DontSavePainterState);
    vi->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    scene->setSceneRect(0, 0, 500, 500);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    connect(ui->deleteButton, SIGNAL(clicked()), scene, SLOT(slotChangeDeleteMode()));
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(changeColor()));
    connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(clearAll()));
    connect(scene, SIGNAL(generate()), this, SLOT(clearAll()));
    connect(ui->funcButton, &QPushButton::clicked, scene, &directpaintScene::slotFunc);
    connect(ui->delFuncButton, &QPushButton::clicked, scene, &directpaintScene::slotDelFunc);
}

directPaint::~directPaint()
{
    delete ui;
}
directpaintScene * directPaint::get_scene() {
    return scene;
}
void directPaint::changeColor() {
    if(deleteToggled) {
        ui->deleteButton->setStyleSheet("* QPushButton { background-color: white;  border: 2px solid #8f8f91; border-radius: 6px;}");
        deleteToggled = false;
    }
    else {
        ui->deleteButton->setStyleSheet("* QPushButton { background-color: red;  border: 2px solid #8f8f91; border-radius: 6px;}");
        deleteToggled = true;
    }
}
void directPaint::clearAll() {
    get_scene()->setCount(0);
    get_scene()->clear();
    get_scene()->get_matrix()->clear();
    get_scene()->getAllVertex()->clear();
    emit get_scene()->signalFromScene(get_scene()->get_matrix());
}
