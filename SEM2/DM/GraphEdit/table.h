#ifndef TABLE_H
#define TABLE_H

#include <QWidget>
#include <paintscene.h>
#include <QVector>
namespace Ui {
class table;
}

class table : public QWidget
{
    Q_OBJECT

public:
    explicit table(paintScene * _scene, QWidget *parent = nullptr);
    ~table();
public slots:
    void slotChangeModel(QMap <int, QMap <int, vertex *>> * _matrixOfVertex);
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
    void find_comps();
    Ui::table *ui;
    QMap <int, QMap <int, vertex *>> * matrixOfVertex;
    paintScene * scene;
    int n;
    QVector<int> g[999];
    bool used[999];
    QVector<int> comp;
};

#endif // TABLE_H
