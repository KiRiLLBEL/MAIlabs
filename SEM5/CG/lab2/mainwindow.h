#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "object.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_Xrotate_valueChanged(double arg1);

    void on_Yrotate_valueChanged(double arg1);

    void on_Zrotate_valueChanged(double arg1);

    void on_Scale_valueChanged(double arg1);

    void on_checkBox_stateChanged(int arg1);

    void on_MXrotate_valueChanged(double arg1);

    void on_MZrotate_valueChanged(double arg1);

    void on_MYrotate_valueChanged(double arg1);

    void on_moveX_valueChanged(double arg1);

    void on_moveY_valueChanged(double arg1);

    void on_moveZ_valueChanged(double arg1);

    void on_MMoveX_valueChanged(double arg1);

    void on_MMoveY_valueChanged(double arg1);

    void on_MMoveZ_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
    Object obj;
};
#endif // MAINWINDOW_H
