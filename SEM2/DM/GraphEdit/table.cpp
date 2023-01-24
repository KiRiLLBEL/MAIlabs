#include "table.h"
#include "ui_table.h"
#include "matrix.h"
#include "item.h"
#include <QStandardItemModel>
table::table(paintScene * _scene, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::table),
    scene(_scene)
{
    ui->setupUi(this);
    connect(scene, &paintScene::signalFromScene, this, &table::slotChangeModel);
    connect(ui->generateButton, SIGNAL(clicked()), this, SLOT(slotGenerateModel()));
    connect(ui->allButton, SIGNAL(clicked()), this, SLOT(slotAll()));
    connect(ui->dallButton, SIGNAL(clicked()), this, SLOT(slotDAll()));
    connect(ui->rowButton, SIGNAL(clicked()), this, SLOT(slotRow()));
    connect(ui->drowButton, SIGNAL(clicked()), this, SLOT(slotDRow()));
    connect(ui->colomnButton, SIGNAL(clicked()), this, SLOT(slotColomn()));
    connect(ui->dcolomnButton, SIGNAL(clicked()), this, SLOT(slotDColomn()));
    connect(ui->funcButton, SIGNAL(clicked()), this, SLOT(slotFunc()));
    connect(ui->funcDelButton, SIGNAL(clicked()), this, SLOT(slotDelFunc()));
    connect(scene, &paintScene::signalFunc, this, &table::slotFunc);
    connect(scene, &paintScene::signalDelFunc, this, &table::slotDelFunc);
}

table::~table()
{
    delete ui;
}
void table::slotChangeModel(QMap <int, QMap <int, vertex *>> * _matrixOfVertex) {
    matrixOfVertex = _matrixOfVertex;
//    QStringList labels;
//    for (int i = 0; i != matrixOfVertex.size() ; ++i) {
//        labels << "V" + QString::number(i + 1);
//    }
    matrix *myModel = new matrix(matrixOfVertex, scene);
    //myModel->setHorizontalHeaderLabels(labels);
    ui->tableView->setModel(myModel);
    ui->tableView->setItemDelegate(new item(ui->tableView));
    for (int i = 0; i != matrixOfVertex->size(); i++)
    {
       ui->tableView->setColumnWidth(i, 10);
    }
    for (int i = 0; i != matrixOfVertex->size(); i++)
    {
       ui->tableView->setRowHeight(i, 10);
    }
}
void table::slotGenerateModel() {
    emit scene->generate();
    int size = 1;
    for (int i = 1; i < 1000; ++i) {
        if (ui->heightSpin->value() <= i*i) {
            //qDebug () << ui->heightSpin->value() << i*i;
            size = i;
            break;
        }
    }
    int heightCount = (ui->heightSpin->value() % 2 == 0 || ui->heightSpin->value() == 1) ? ui->heightSpin->value() / size : ui->heightSpin->value() / size + 1;
    int heightSize = (scene->height() - 200) / size;
    int widthSize = (scene->width() - 200) / size;
    if(heightSize < 70) {
        scene->setSceneRect(0,0, 25*ui->heightSpin->value(), 25*ui->heightSpin->value());
        //qDebug() << scene->sceneRect();
    }
    heightSize = (scene->height() - 200) / size;
    widthSize = (scene->width() - 200) / size;
    //qDebug () << heightCount << size;
    QPointF startPos(100, 100);
    for (int i = 0; i != size; ++i) {
        if (scene->getCount() == ui->heightSpin->value()) {
            break;
        }
        for (int j = 0; j != size; ++j) {
            if (scene->getCount() == ui->heightSpin->value()) {
                break;
            }
            scene->setCount(scene->getCount() + 1);
            vertex * v = new vertex(startPos, scene->getCount());
            QMap <int, vertex *> m;
            m.insert(scene->getCount() - 1, v);
            (*matrixOfVertex).insert(scene->getCount() - 1, m);
            scene->getAllVertex()->push_back(v);
            scene->addItem(v);
            v->setPos(QPointF(startPos.x(), startPos.y()));
            startPos.setX(startPos.x() + widthSize);
        }
        startPos.setY(startPos.y() + heightSize);
        startPos.setX(100);
    }
    emit scene->signalFromScene(matrixOfVertex);
}
void table::slotAll() {
    if (ui->tableView->model() != NULL) {
        QModelIndex startOfRow = ui->tableView->model()->index(0, 0);
        int rows = ui->tableView->model()->rowCount() - 1;
        int colomns = ui->tableView->model()->columnCount() - 1;
        QModelIndex endOfRow   = ui->tableView->model()->index(rows, colomns);
        for (int i = 0; i != ui->tableView->model()->columnCount(); ++i) {
            for (int j = 0; j != ui->tableView->model()->columnCount(); ++j) {
                ui->tableView->model()->setData(ui->tableView->model()->index(i,j), "1");
            }
        }
        emit ui->tableView->model()->dataChanged(startOfRow, endOfRow);
    }
}
void table::slotDAll() {
    if (ui->tableView->model() != NULL) {
        QModelIndex startOfRow = ui->tableView->model()->index(0, 0);
        int rows = ui->tableView->model()->rowCount() - 1;
        int colomns = ui->tableView->model()->columnCount() - 1;
        QModelIndex endOfRow   = ui->tableView->model()->index(rows, colomns);
        for (int i = 0; i != ui->tableView->model()->columnCount(); ++i) {
            for (int j = 0; j != ui->tableView->model()->columnCount(); ++j) {
                ui->tableView->model()->setData(ui->tableView->model()->index(i,j), "0");
            }
        }
        emit ui->tableView->model()->dataChanged(startOfRow, endOfRow);
    }
}
void table::slotRow() {
    if (ui->tableView->model() != NULL) {
        QModelIndexList selection = ui->tableView->selectionModel()->selectedRows();
        for(int i=0; i< selection.count(); i++)
        {
            QModelIndex index = selection.at(i);
            QModelIndex startOfRow = ui->tableView->model()->index(0, 0);
            QModelIndex endOfRow   = ui->tableView->model()->index(ui->tableView->model()->rowCount() - 1, ui->tableView->model()->columnCount() - 1);
            for(int j = 0; j != ui->tableView->model()->rowCount(); ++j) {
                ui->tableView->model()->setData(ui->tableView->model()->index(index.row(),j), "1");
            }
            emit ui->tableView->model()->dataChanged(startOfRow, endOfRow);
            //        qDebug() << index.row();
        }
    }
}
void table::slotDRow() {
    if (ui->tableView->model() != NULL){
        QModelIndexList selection = ui->tableView->selectionModel()->selectedRows();
        for(int i=0; i< selection.count(); i++)
        {
            QModelIndex index = selection.at(i);
            QModelIndex startOfRow = ui->tableView->model()->index(0, 0);
            QModelIndex endOfRow   = ui->tableView->model()->index(ui->tableView->model()->rowCount() - 1, ui->tableView->model()->columnCount() - 1);
            for(int j = 0; j != ui->tableView->model()->rowCount(); ++j) {
                ui->tableView->model()->setData(ui->tableView->model()->index(index.row(),j), "0");
            }
            emit ui->tableView->model()->dataChanged(startOfRow, endOfRow);
            //        qDebug() << index.row();
        }
    }
}
void table::slotColomn() {
    if (ui->tableView->model() != NULL) {
        QModelIndexList selection = ui->tableView->selectionModel()->selectedColumns();
        for(int i=0; i< selection.count(); i++)
        {
            QModelIndex index = selection.at(i);
            QModelIndex startOfRow = ui->tableView->model()->index(0, 0);
            QModelIndex endOfRow   = ui->tableView->model()->index(ui->tableView->model()->rowCount() - 1, ui->tableView->model()->columnCount() - 1);
            for(int j = 0; j != ui->tableView->model()->columnCount(); ++j) {
                ui->tableView->model()->setData(ui->tableView->model()->index(j,index.column()), "1");
            }
            emit ui->tableView->model()->dataChanged(startOfRow, endOfRow);
            //        qDebug() << index.row();
        }
    }
}
void table::slotDColomn() {
    if (ui->tableView->model() != NULL){
        QModelIndexList selection = ui->tableView->selectionModel()->selectedColumns();
        for(int i=0; i< selection.count(); i++)
        {
            QModelIndex index = selection.at(i);
            QModelIndex startOfRow = ui->tableView->model()->index(0, 0);
            QModelIndex endOfRow   = ui->tableView->model()->index(ui->tableView->model()->rowCount() - 1, ui->tableView->model()->columnCount() - 1);
            for(int j = 0; j != ui->tableView->model()->columnCount(); ++j) {
                ui->tableView->model()->setData(ui->tableView->model()->index(j,index.column()), "0");
            }
            emit ui->tableView->model()->dataChanged(startOfRow, endOfRow);
            //        qDebug() << index.row();
        }
    }
}
void table::dfs (int v) {
    used[v] = true;
    comp.push_back (v);
    for (int i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if (! used[to])
            dfs (to);
    }
}

void table::find_comps() {
    for (int i = 0; i < n; ++i)
        used[i] = false;
    for (int i = 0; i < n; ++i)
        if (!used[i]) {
            comp.clear();
            dfs (i);

            qDebug() << "Component:";
            QColor colour(rand()%255, rand()%255, rand()%255);
            colour.setHsv(rand()%359, 255, 255);
            for (int j = 0; j < comp.size(); ++j) {
                scene->getAllVertex()->at(comp[j])->componentIn(colour);
//                for(int k = 0; k != comp.size(); ++k) {
//                    if ((*matrixOfVertex)[comp[j]][comp[k]] != NULL) {
//                        qDebug() << "ok";
//                        (*matrixOfVertex)[comp[j]][comp[k]]->componentIn(colour);
//                    }
//                }
            }
            qDebug() << "----------";
        }
}
void table::slotFunc() {
    slotDelFunc();
    if (ui->tableView->model() != NULL) {
        for (int i = 0; i != 1000; ++i) {
            g[i].clear();
        }
        g->clear();
        for (int i = 0; i != ui->tableView->model()->rowCount(); ++i) {
            for (int j = 0; j != ui->tableView->model()->columnCount(); ++j) {
                QVariant in = ui->tableView->model()->data(ui->tableView->model()->index(i, j));
                if(in == "1") {
                    g[i].push_back(j);
                }
            }
        }
        n = ui->tableView->model()->rowCount();
        find_comps();
    }
}

void table::slotDelFunc() {
    for(int i = 0; i!= scene->getCount(); ++i) {
        (*scene->getAllVertex())[i]->componentOut();
    }
    for (int i = 0; i!= scene->getCount(); ++i) {
        for (int j = 0; j!= scene->getCount(); ++j) {
            if ((*matrixOfVertex)[i][j] != NULL)
                (*matrixOfVertex)[i][j]->componentOut();
        }
    }
}
