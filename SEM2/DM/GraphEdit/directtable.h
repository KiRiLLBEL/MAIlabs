#ifndef DIRECTTABLE_H
#define DIRECTTABLE_H

#include <QWidget>
#include <directpaintscene.h>
#include <QVector>
namespace Ui {
class directtable;
}

class directtable : public QWidget
{
    Q_OBJECT

public:
    explicit directtable(directpaintScene * _scene, QWidget *parent = nullptr);
    ~directtable();
public slots:
    void slotChangeModel(QMap <int, QMap <int, directedge *>> * _matrixOfVertex);
    void slotGenerateModel();
    void slotAll();
    void slotDAll();
    void slotRow();
    void slotDRow();
    void slotColomn();
    void slotDColomn();
    void slotFunc();
    void slotDelFunc();
private:
    void dfs(int n);
    void dfs1(int n);
    void dfs2(int n);
    void find_comps();
    Ui::directtable *ui;
    QMap <int, QMap <int, directedge *>> * matrixOfVertex;
    directpaintScene * scene;
    int n;
    QVector < QVector<int> > g, gr;
    QVector<bool> used;
    QVector<int> order, component;
};

#endif // TABLE_H
