#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QWidget>
#include <QLineEdit>
#include <QObject>
#include <QLabel>
#include <QPushButton>
QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void on_btn_0_clicked();

    void on_btn_1_clicked();

    void on_btn_2_clicked();

    void on_btn_3_clicked();

    void on_btn_4_clicked();

    void on_btn_5_clicked();

    void on_btn_6_clicked();

    void on_btn_7_clicked();

    void on_btn_8_clicked();

    void on_btn_9_clicked();

    void on_btn_del_clicked();

    void on_btn_div_clicked();

    void on_btn_equal_clicked();

    void on_btn_minus_clicked();

    void on_btn_multi_clicked();

    void on_btn_plus_clicked();

    void on_btn_point_clicked();

    void on_btn_rem_clicked();

    void on_btn_changeSign_clicked();

    void on_btn_delall_clicked();

    void add_1();

    void add_2();

    void add_3();

    void add_4();

    void add_5();

    void add_6();

    void add_7();

    void add_8();

    void add_9();

    void add_0();

    void DelDisplay();

    void DelDisplayALL();

    void PlusOperation();

    void MinusOperation();

    void MultiOperation();

    void DivOperation();

    void Equal();

    void ChangeSign();

    void PointChange();

    void Remove();

signals:
    void btn_0_clicked();

    void btn_1_clicked();

    void btn_2_clicked();

    void btn_3_clicked();

    void btn_4_clicked();

    void btn_5_clicked();

    void btn_6_clicked();

    void btn_7_clicked();

    void btn_8_clicked();

    void btn_9_clicked();

    void btn_del_clicked();

    void btn_delall_clicked();

    void btn_plus_clicked();

    void btn_minus_clicked();

    void btn_equal_clicked();

    void btn_multi_clicked();

    void btn_div_clicked();

    void btn_changeSign_clicked();

    void btn_point_clicked();

    void btn_rem_clicked();
private:
    Ui::Calculator *ui;
    QLineEdit *ui_le_in;
    QLabel *ui_lbl_Res;
    QString First_Number;
    QString Second_Number;
    double Result;
    double LLFNumber;
    double LLSNumber;
    bool EqualDo = false;
};
#endif // CALCULATOR_H
