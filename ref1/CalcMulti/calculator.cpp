#include "calculator.h"
#include "ui_calculator.h"
#include <QtUiTools>
#include <QtCore>
#include <QLineEdit>
#include <QtGui>
#include <QPushButton>

bool NowOp = false;
Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    ui_le_in = findChild<QLineEdit*>("le_in");
    ui_lbl_Res = findChild<QLabel*>("lbl_Res");
    connect(this, SIGNAL(btn_1_clicked()), this, SLOT(add_1()));
    connect(this, SIGNAL(btn_2_clicked()), this, SLOT(add_2()));
    connect(this, SIGNAL(btn_3_clicked()), this, SLOT(add_3()));
    connect(this, SIGNAL(btn_4_clicked()), this, SLOT(add_4()));
    connect(this, SIGNAL(btn_5_clicked()), this, SLOT(add_5()));
    connect(this, SIGNAL(btn_6_clicked()), this, SLOT(add_6()));
    connect(this, SIGNAL(btn_7_clicked()), this, SLOT(add_7()));
    connect(this, SIGNAL(btn_8_clicked()), this, SLOT(add_8()));
    connect(this, SIGNAL(btn_9_clicked()), this, SLOT(add_9()));
    connect(this, SIGNAL(btn_0_clicked()), this, SLOT(add_0()));
    connect(this, SIGNAL(btn_del_clicked()), this, SLOT(DelDisplay()));
    connect(this, SIGNAL(btn_delall_clicked()), this, SLOT(DelDisplayALL()));
    connect(this, SIGNAL(btn_plus_clicked()), this, SLOT(PlusOperation()));
    connect(this, SIGNAL(btn_minus_clicked()), this, SLOT(MinusOperation()));
    connect(this, SIGNAL(btn_equal_clicked()), this, SLOT(Equal()));
    connect(this, SIGNAL(btn_multi_clicked()), this, SLOT(MultiOperation()));
    connect(this, SIGNAL(btn_div_clicked()), this, SLOT(DivOperation()));
    connect(this, SIGNAL(btn_changeSign_clicked()), this, SLOT(ChangeSign()));
    connect(this, SIGNAL(btn_point_clicked()), this, SLOT(PointChange()));
    connect(this, SIGNAL(btn_rem_clicked()), this, SLOT(Remove()));

}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::on_btn_0_clicked()
{
    emit btn_0_clicked();
}


void Calculator::on_btn_1_clicked()
{
    emit btn_1_clicked();
}


void Calculator::on_btn_2_clicked()
{
    emit btn_2_clicked();
}


void Calculator::on_btn_3_clicked()
{
    emit btn_3_clicked();
}


void Calculator::on_btn_4_clicked()
{
    emit btn_4_clicked();
}


void Calculator::on_btn_5_clicked()
{
    emit btn_5_clicked();
}


void Calculator::on_btn_6_clicked()
{
    emit btn_6_clicked();
}


void Calculator::on_btn_7_clicked()
{
    emit btn_7_clicked();
}


void Calculator::on_btn_8_clicked()
{
    emit btn_8_clicked();
}


void Calculator::on_btn_9_clicked()
{
    emit btn_9_clicked();
}


void Calculator::on_btn_del_clicked()
{
    emit btn_del_clicked();
}


void Calculator::on_btn_div_clicked()
{
    emit btn_div_clicked();
}


void Calculator::on_btn_equal_clicked()
{
    emit btn_equal_clicked();
}


void Calculator::on_btn_minus_clicked()
{
    emit btn_minus_clicked();
}


void Calculator::on_btn_multi_clicked()
{
    emit btn_multi_clicked();
}


void Calculator::on_btn_plus_clicked()
{
    emit btn_plus_clicked();
}


void Calculator::on_btn_point_clicked()
{
    emit btn_point_clicked();
}


void Calculator::on_btn_rem_clicked()
{
    emit btn_rem_clicked();
}


void Calculator::on_btn_changeSign_clicked()
{
    emit btn_changeSign_clicked();
}

void Calculator::on_btn_delall_clicked()
{
    emit btn_delall_clicked();
}


void Calculator::add_1() {
    if (ui_le_in->text() == "0" || ui_le_in->text() == "Error") {
       ui_le_in->setText("1");
       EqualDo = false;
    }
    else {
        if (EqualDo) {
            ui_le_in->setText("0");
            EqualDo = false;
        } else {
            ui_le_in->setText(ui_le_in->text() + "1");
        }
    }

}

void Calculator::add_2() {
    if (ui_le_in->text() == "0" || ui_le_in->text() == "Error") {
       ui_le_in->setText("2");
       EqualDo = false;
    }
    else {
        if (EqualDo) {
            ui_le_in->setText("0");
            EqualDo = false;
        } else {
            ui_le_in->setText(ui_le_in->text() + "2");
        }
    }

}

void Calculator::add_3() {
    if (ui_le_in->text() == "0" || ui_le_in->text() == "Error") {
       ui_le_in->setText("3");
       EqualDo = false;
    }
    else {
        if (EqualDo) {
            ui_le_in->setText("0");
            EqualDo = false;
        } else {
            ui_le_in->setText(ui_le_in->text() + "3");
        }
    }

}

void Calculator::add_4() {
    if (ui_le_in->text() == "0" || ui_le_in->text() == "Error") {
       ui_le_in->setText("4");
       EqualDo = false;
    }
    else {
        if (EqualDo) {
            ui_le_in->setText("0");
            EqualDo = false;
        } else {
            ui_le_in->setText(ui_le_in->text() + "4");
        }
    }

}

void Calculator::add_5() {
    if (ui_le_in->text() == "0" || ui_le_in->text() == "Error") {
       ui_le_in->setText("5");
       EqualDo = false;
    }
    else {
        if (EqualDo) {
            ui_le_in->setText("0");
            EqualDo = false;
        } else {
            ui_le_in->setText(ui_le_in->text() + "5");
        }
    }

}

void Calculator::add_6() {
    if (ui_le_in->text() == "0" || ui_le_in->text() == "Error") {
       ui_le_in->setText("6");
       EqualDo = false;
    }
    else {
        if (EqualDo) {
            ui_le_in->setText("0");
            EqualDo = false;
        } else {
            ui_le_in->setText(ui_le_in->text() + "6");
        }
    }

}

void Calculator::add_7() {
    if (ui_le_in->text() == "0" || ui_le_in->text() == "Error") {
       ui_le_in->setText("7");
       EqualDo = false;
    }
    else {
        if (EqualDo) {
            ui_le_in->setText("0");
            EqualDo = false;
        } else {
            ui_le_in->setText(ui_le_in->text() + "7");
        }
    }

}

void Calculator::add_8() {
    if (ui_le_in->text() == "0" || ui_le_in->text() == "Error") {
       ui_le_in->setText("8");
       EqualDo = false;
    }
    else {
        if (EqualDo) {
            ui_le_in->setText("0");
            EqualDo = false;
        } else {
            ui_le_in->setText(ui_le_in->text() + "8");
        }
    }

}

void Calculator::add_9() {
    if (ui_le_in->text() == "0" || ui_le_in->text() == "Error") {
       ui_le_in->setText("9");
       EqualDo = false;
    }
    else {
        if (EqualDo) {
            ui_le_in->setText("0");
            EqualDo = false;
        } else {
            ui_le_in->setText(ui_le_in->text() + "9");
        }
    }

}
void Calculator::add_0() {
    if (ui_le_in->text() == "0") {
        EqualDo = false;
    }
    else {
       if (EqualDo) {
           ui_le_in->setText("0");
           EqualDo = false;
       } else {
           ui_le_in->setText(ui_le_in->text() + "0");
       }
    }

}

void Calculator::DelDisplay() {
    EqualDo = false;
    ui_le_in->setText("0");
}

void Calculator::DelDisplayALL() {
    EqualDo = false;
    ui_le_in->setText("0");
    ui_lbl_Res->clear();
}

void Calculator::PlusOperation() {
        EqualDo = false;
        ui_lbl_Res->setText(ui_le_in->text() + "+");
        First_Number = ui_le_in->text();
        DelDisplay();
}

void Calculator::MinusOperation() {
        EqualDo = false;
        ui_lbl_Res->setText(ui_le_in->text() + "-");
        First_Number = ui_le_in->text();
        DelDisplay();
}

void Calculator::MultiOperation() {
        EqualDo = false;
        ui_lbl_Res->setText(ui_le_in->text() + "×");
        First_Number = ui_le_in->text();
        DelDisplay();
}

void Calculator::DivOperation() {
    EqualDo = false;
    ui_lbl_Res->setText(ui_le_in->text() + "/");
    First_Number = ui_le_in->text();
    DelDisplay();
}
void Calculator::ChangeSign() {
    QString t = ui_le_in->text();
    if (t.indexOf("-", 0) == -1) {
        ui_le_in->setText("-" + ui_le_in->text());
    } else {
        t.remove(QChar('-'), Qt::CaseInsensitive);
        ui_le_in->setText(t);
    }
}

void Calculator::PointChange() {
    QString t = ui_le_in->text();
    if (t.indexOf(".", 0) == -1) {
        ui_le_in->setText(ui_le_in->text() + ".");
    }
}

void Calculator::Remove() {
    QString t = ui_le_in->text();
    if (t.size() != 1) {
        t.chop(1);
        ui_le_in->setText(t);
    } else {
        ui_le_in->setText("0");
    }
}

void Calculator::Equal() {
    QString Temp;
    Temp = ui_lbl_Res->text();
    if (Temp.indexOf("=", 0) == -1) {
        if (Temp.indexOf("+", 0) != -1) {
            ui_lbl_Res->setText(ui_lbl_Res->text() + ui_le_in->text() + "=");
            Second_Number = ui_le_in->text();
            LLFNumber = First_Number.toDouble();
            LLSNumber = Second_Number.toDouble();
            Result = LLFNumber + LLSNumber;
            ui_le_in->setText(QString::number(Result));
            EqualDo = true;
        }
        else if (Temp.indexOf("-", 0) != -1 && Temp.indexOf("+", 0) == -1) {
            ui_lbl_Res->setText(ui_lbl_Res->text() + ui_le_in->text() + "=");
            Second_Number = ui_le_in->text();
            qDebug() << Second_Number;
            LLFNumber = First_Number.toDouble();
            LLSNumber = Second_Number.toDouble();
            Result = LLFNumber - LLSNumber;
            ui_le_in->setText(QString::number(Result));
            EqualDo = true;
        }
        else if (Temp.indexOf("-", 0) != -1 && Temp.indexOf("+", 0) != -1) {
            ui_lbl_Res->setText(ui_lbl_Res->text() + ui_le_in->text() + "=");
            Second_Number = ui_le_in->text();
            LLFNumber = First_Number.toDouble();
            LLSNumber = Second_Number.toDouble();
            Result = LLFNumber + LLSNumber;
            ui_le_in->setText(QString::number(Result));
            EqualDo = true;
        }
        else if (Temp.indexOf("×", 0) != -1) {
            ui_lbl_Res->setText(ui_lbl_Res->text() + ui_le_in->text() + "=");
            Second_Number = ui_le_in->text();\
            qDebug() << Second_Number;
            LLFNumber = First_Number.toDouble();
            LLSNumber = Second_Number.toDouble();
            Result = LLFNumber * LLSNumber;
            ui_le_in->setText(QString::number(Result));
            EqualDo = true;
        }
        else if (Temp.indexOf("/", 0) != -1) {
            ui_lbl_Res->setText(ui_lbl_Res->text() + ui_le_in->text() + "=");
            Second_Number = ui_le_in->text();
            qDebug() << Second_Number;
            LLFNumber = First_Number.toDouble();
            LLSNumber = Second_Number.toDouble();
            if (LLSNumber == 0) {
                ui_le_in->setText("Error");
            } else {
                Result = LLFNumber / LLSNumber;
                ui_le_in->setText(QString::number(Result));
            }
            EqualDo = true;
        }
    }
}







