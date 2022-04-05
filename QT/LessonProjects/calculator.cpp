#include "calculator.h"

Calculator::Calculator(QWidget * pwgt) : QWidget(pwgt) {
    m_plcd = new QLCDNumber(12);
    m_plcd->setSegmentStyle(QLCDNumber::Flat);
    m_plcd->setMinimumSize(150, 50);
    QChar aButtons[4][4] = { { '7', '8', '9', '/'},
                             { '4', '5', '6', '*'},
                             { '1', '2' ,'3', '_'},
                             {'0', '*', '=', '+'}
                             };
    QGridLayout * ptopLayout = new QGridLayout;
    ptopLayout->addWidget(m_plcd, 0, 0, 1, 4);
    ptopLayout->addWidget(createButton("CE"), 1, 3);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            ptopLayout->addWidget(createButton(aButtons[i][j]), i + 2, j);
        }
    }
    setLayout(ptopLayout);
}

QPushButton * Calculator::createButton(const QString & str) {
    QPushButton * pcmd = new QPushButton(str);
    pcmd->setMinimumSize(40, 40);
    connect(pcmd, SIGNAL(clicked()), SLOT(ButtonClicked()));
    return pcmd;
}
