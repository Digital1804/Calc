#include "widget.h"
#include <QTextEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QListWidget>
#include <QGridLayout>
#include <QToolButton>
#include <QLineEdit>
#include <QButtonGroup>

Widget::Widget(QWidget *parent) : QWidget(parent){
    QVBoxLayout *grid1 = new QVBoxLayout(this);
    QGridLayout *grid = new QGridLayout(this);
    QLineEdit *label;
    label = new QLineEdit;
    label->setReadOnly(true);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    grid1->addWidget(label);
    grid1->addLayout(grid);
    grid1->setSpacing(2);
    QList<QString> values(
                { "C", "Del", "(", ")",
                  "sin", "cos", "tg", "ctg",
                  "!", "^X", "ld", "logn",
                  "1", "2", "3", "+",
                  "4", "5", "6", "-",
                  "7", "8", "9", "*",
                  ".", "0", "=", "/"
                });
    QList<QString> numbers({ "1", "2", "3", "4", "5", "6", "7", "8", "9", "0"});
    QList<QString> actions({ "C", "Del", "(", ")",
                             "sin", "cos", "tg", "ctg",
                             "!", "^X", "ld", "logn",
                             "+", "-", "*", ".", "=", "/"
                           });


    QButtonGroup *actionGroup = new QButtonGroup(this);
    QButtonGroup *numberGroup = new QButtonGroup(this);
    QToolButton *digitButtons[values.length()];
    int a = 0, n = 0;
    for (int i=0; i<values.length(); i++){
        digitButtons[i] = new QToolButton();
        digitButtons[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        digitButtons[i]->setText(values[i]);
        if (digitButtons[i]->text() == "C")
                digitButtons[i]->setStyleSheet("background-color: red");
        else if (digitButtons[i]->text() == "=")
                digitButtons[i]->setStyleSheet("background-color: lightblue");
        else digitButtons[i]->setStyleSheet("background-color: lightgray");
        if (numbers.contains(digitButtons[i]->text())){
            numberGroup->addButton(digitButtons[i], a);
            a++;
        }
        else{
            actionGroup->addButton(digitButtons[i], n);
            n++;
        }
    }

    int pos = 0;

    for (int i=0; i<(values.length()/4); i++) {
        for (int j=0; j<4; j++) {
            digitButtons[pos]->setFixedSize(50, 40); // Добавление каждой кнопки в ячейки матрицы GridLayout
            grid->addWidget(digitButtons[pos], i, j);
            pos++;
        }
    }
    connect(buttons, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),[=](QAbstractButton *actionGroup) {/*.....*/});
    setLayout(grid1);
}

Widget::~Widget()
{
}
