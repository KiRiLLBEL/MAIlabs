#include "choice.h"
#include "ui_choice.h"
#include "paint.h"
#include "directpaint.h"
#include "directtable.h"
#include "table.h"
#include "QTabWidget"
choice::choice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::choice)
{
    ui->setupUi(this);
    connect(ui->directButton, SIGNAL(clicked()), this, SLOT(slotOpenDirect()));
    connect(ui->nonDirectButton, SIGNAL(clicked()), this, SLOT(slotOpenNonDirect()));
}

choice::~choice()
{
    delete ui;
}
void choice::slotOpenDirect() {
    tab = new QTabWidget;
    directPaint * w = new directPaint(tab);
    directtable * t = new directtable(w->get_scene(), tab);
    tab->addTab(w, "Graph");
    tab->addTab(t, "Table");
    tab->setWindowState(Qt::WindowMaximized);
    close();
    tab->show();
}
void choice::slotOpenNonDirect() {
    tab = new QTabWidget;
    Paint * w = new Paint(tab);
    table * t = new table(w->get_scene(), tab);
    tab->addTab(w, "Graph");
    tab->addTab(t, "Table");
    tab->setWindowState(Qt::WindowMaximized);
    close();
    tab->show();
}
