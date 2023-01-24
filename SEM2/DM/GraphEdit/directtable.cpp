#include "directtable.h"
#include "ui_directtable.h"
#include "directmatrix.h"
#include "item.h"
#include <QStandardItemModel>
directtable::directtable(directpaintScene * _scene, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::directtable),
    scene(_scene)
{
    ui->setupUi(this);
    connect(scene, &directpaintScene::signalFromScene, this, &directtable::slotChangeModel);
    connect(ui->generateButton, SIGNAL(clicked()), this, SLOT(slotGenerateModel()));
    connect(ui->allButton, SIGNAL(clicked()), this, SLOT(slotAll()));
    connect(ui->dallButton, SIGNAL(clicked()), this, SLOT(slotDAll()));
    connect(ui->rowButton, SIGNAL(clicked()), this, SLOT(slotRow()));
    connect(ui->drowButton, SIGNAL(clicked()), this, SLOT(slotDRow()));
    connect(ui->colomnButton, SIGNAL(clicked()), this, SLOT(slotColomn()));
    connect(ui->dcolomnButton, SIGNAL(clicked()), this, SLOT(slotDColomn()));
    connect(ui->funcButton, SIGNAL(clicked()), this, SLOT(slotFunc()));
    connect(ui->funcDelButton, SIGNAL(clicked()), this, SLOT(slotDelFunc()));
    connect(scene, &directpaintScene::signalFunc, this, &directtable::slotFunc);
    connect(scene, &directpaintScene::signalDelFunc, this, &directtable::slotDelFunc);
}

directtable::~directtable()
{
    delete ui;
}
void directtable::slotChangeModel(QMap <int, QMap <int, directedge *>> * _matrixOfVertex) {
    matrixOfVertex = _matrixOfVertex;
//    QStringList labels;
//    for (int i = 0; i != matrixOfVertex.size() ; ++i) {
//        labels << "V" + QString::number(i + 1);
//    }
    directmatrix *myModel = new directmatrix(matrixOfVertex, scene);
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
void directtable::slotGenerateModel() {
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
            directvertex * v = new directvertex(startPos, scene->getCount());
            QMap <int, directedge *> m;
            m.insert(scene->getCount() - 1, NULL);
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
void directtable::slotAll() {
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
void directtable::slotDAll() {
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
void directtable::slotRow() {
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
void directtable::slotDRow() {
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
void directtable::slotColomn() {
    if (ui->tableView->model() != NULL) {
        QModelIndexList selection = ui->tableView->selectionModel()->selectedColumns();
        for(int i=0; i< selection.count(); i++)
        {
            QModelIndex index = selection.at(i);
            QModelIndex startOfRow = ui->tableView->model()->index(0, 0);
            QModelIndex endOfRow   = ui->tableView->model()->index(ui->tableView->model()->rowCount() - 1, ui->tableView->model()->columnCount() - 1);
            for(int j = 0; j != ui->tableView->model()->columnCount(); ++j) {
                ui->tableView->model()->setData(ui->tableView->model()->index(j,index.column()), "1");
                qDebug() << j << index.column();
            }
            emit ui->tableView->model()->dataChanged(startOfRow, endOfRow);
            //        qDebug() << index.row();
        }
    }
}
void directtable::slotDColomn() {
    if (ui->tableView->model() != NULL){
        QModelIndexList selection = ui->tableView->selectionModel()->selectedColumns();
        for(int i=0; i< selection.count(); i++)
        {
            QModelIndex index = selection.at(i);
            QModelIndex startOfRow = ui->tableView->model()->index(0, 0);
            QModelIndex endOfRow   = ui->tableView->model()->index(ui->tableView->model()->rowCount() - 1, ui->tableView->model()->columnCount() - 1);
            for(int j = 0; j != ui->tableView->model()->columnCount(); ++j) {
                ui->tableView->model()->setData(ui->tableView->model()->index(j,index.column()), "0");
                qDebug() << j << index.column();
            }
            emit ui->tableView->model()->dataChanged(startOfRow, endOfRow);
            //        qDebug() << index.row();
        }
    }
}
//void directtable::dfs (int v) {
//    used[v] = true;
//    comp.push_back (v);
//    for (int i = 0; i < g[v].size(); ++i) {
//        int to = g[v][i];
//        if (! used[to])
//            dfs (to);
//    }
//}
void directtable::dfs1 (int v) {
    used[v] = true;
    for (size_t i=0; i < g[v].size(); ++i)
        if (!used[g[v][i]]) {
            dfs1(g[v][i]);
            qDebug() << g[v][i];
        }
    order.push_back(v);
}

void directtable::dfs2 (int v) {
    used[v] = true;
    component.push_back (v);
    for (size_t i=0; i<gr[v].size(); ++i)
        if (!used[ gr[v][i] ])
            dfs2 (gr[v][i]);
}
//void directtable::find_comps() {
//    for (int i = 0; i < n; ++i)
//        used[i] = false;
//    for (int i = 0; i < n; ++i)
//        if (!used[i]) {
//            comp.clear();
//            dfs (i);
//            qDebug() << "Component";
//            QColor colour(rand()%255, rand()%255, rand()%255);
//            colour.setHsv(rand()%359, 255, 255);
//            for (int j = 0; j < comp.size(); ++j) {
//                scene->getAllVertex()->at(comp[j])->componentIn(colour);
//                qDebug() << comp[j] + 1;
//                for(int k = 0; k < comp.size(); ++k) {
//                    if ((*matrixOfVertex)[comp[j]][comp[k]] != NULL) {
//                        (*matrixOfVertex)[comp[j]][comp[k]]->componentIn(colour);
//                    }
//                }
//            }
//            qDebug() << "----------";
//        }
//}
void directtable::slotFunc() {
    slotDelFunc();
    n = scene->getCount();
    if (ui->tableView->model() != NULL) {
        g.clear();
        g.resize(n);
        gr.clear();
        gr.resize(n);
        component.clear();
        order.clear();
        used.clear();
        for (int i = 0; i != ui->tableView->model()->rowCount(); ++i) {
            for (int j = 0; j != ui->tableView->model()->columnCount(); ++j) {
                QVariant in = ui->tableView->model()->data(ui->tableView->model()->index(i, j));
                if(in == "1") {
                    g[i].push_back(j);
                    gr[j].push_back(i);
                }
            }
        }
        used.fill(false, n);
        for (int i=0; i<n; ++i)
            if (!used[i])
                dfs1 (i);
        used.fill(false, n);
        for (int i=0; i < n; ++i) {
            int v = order[n-1-i];
            if (!used[v]) {
                dfs2 (v);
                QColor colour(rand()%255, rand()%255, rand()%255);
                colour.setHsv(rand()%359, 255, 255);
                qDebug() << "component";
                for (int j = 0; j < component.size(); ++j) {
                    scene->getAllVertex()->at(component[j])->componentIn(colour);
                    qDebug() << component[j] + 1;
                    for(int k = 0; k < component.size(); ++k) {
                        if ((*matrixOfVertex)[component[j]][component[k]] != NULL) {
                            (*matrixOfVertex)[component[j]][component[k]]->componentIn(colour);
                        }
                    }
                }
                component.clear();
            }
        }
//        find_comps();
    }
}

void directtable::slotDelFunc() {
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
