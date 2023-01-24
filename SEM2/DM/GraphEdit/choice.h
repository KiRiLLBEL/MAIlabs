#ifndef CHOICE_H
#define CHOICE_H

#include <QDialog>
#include <QTabWidget>
namespace Ui {
class choice;
}

class choice : public QDialog
{
    Q_OBJECT

public:
    explicit choice(QWidget *parent = nullptr);
    ~choice();
public slots:
    void slotOpenDirect();
    void slotOpenNonDirect();
private:
    Ui::choice *ui;
    QTabWidget * tab;
};

#endif // CHOICE_H
