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
#include <QString>

#define PI 3.14159265

Widget::Widget(QWidget *parent) : QWidget(parent){
    QVBoxLayout *grid1 = new QVBoxLayout(this);
    QGridLayout *grid = new QGridLayout(this);
    label = new QLabel("0", this);
    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    label->setStyleSheet("background-color: white");
    time = new QLabel(this);
    time->setAlignment(Qt::AlignCenter);
    time->setStyleSheet("background-color: white");
    time->setFixedSize(50, 20);
    label->setMaximumHeight(50);
    grid1->addWidget(time);
    grid1->addWidget(label);
    grid1->addLayout(grid);
    grid1->setSpacing(2);
    int columns = 5;
    QList<QString> values(
                { "C", "Del", "(", ")", "",
                  "!", "^X", "ln", "logn", "sqrt",
                  "1", "2", "3", "+", "ctg",
                  "4", "5", "6", "-", "tg",
                  "7", "8", "9", "*", "cos",
                  ".", "0", "=", "/", "sin"
                });
    QList<QString> numbers({ "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"});

    QPushButton *digitButtons[values.length()];
    int a = 0, n = 0;
    for (int i=0; i<values.length(); i++){
        digitButtons[i] = new QPushButton();
        digitButtons[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        digitButtons[i]->setMinimumWidth(40);
        digitButtons[i]->setText(values[i]);
        if (numbers.contains(digitButtons[i]->text())){
            digitButtons[i]->setStyleSheet("background-color: white");
            connect(digitButtons[i],SIGNAL(clicked()),this, SLOT(digits_numbers()));
            a++;
        }
        else{
            if (digitButtons[i]->text() == "C")
                    digitButtons[i]->setStyleSheet("background-color: red");
            else if (digitButtons[i]->text() == "=")
                    digitButtons[i]->setStyleSheet("background-color: lightblue");
            else    digitButtons[i]->setStyleSheet("background-color: lightgrey");
            connect(digitButtons[i],SIGNAL(clicked()),this, SLOT(operations()));
            n++;
        }
    }

    int pos = 0;

    for (int i=0; i<(values.length()/columns); i++) {
        for (int j=0; j<columns; j++) {
            grid->addWidget(digitButtons[pos], i, j);
            pos++;
        }
    }

    setLayout(grid1);
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
    timer->start(1000); // И запустим таймер
}

void Widget::slotTimerAlarm() {
    time->setText(QTime::currentTime().toString("hh:mm:ss"));
}

void Widget::digits_numbers(){
    QPushButton *button = (QPushButton *)sender();
    double all_numbers;
    QString new_label;
    if(label->text().contains(".") && button->text() == "0"){
        new_label = label->text() + button->text();
    }else {
        all_numbers = (label->text() + button->text()).toDouble();
        new_label = QString::number(all_numbers, 'g', 15);
    }

    label->setText(new_label);
}

void Widget::operations(){
    num_first = label->text().toDouble();
    label->setText("");
    if (on_pushButton_equal_clicked())
        on_pushButton_equal_clicked();
}

double fact(int N){
    if(N < 0)
        return 0;
    if (N == 0)
        return 1;
    else
        return N * fact(N - 1);
}

int Widget::on_pushButton_equal_clicked(){
    QPushButton *pushButton = (QPushButton *)sender();
    QString new_label;
    num_second = label->text().toDouble();
    if(pushButton->text() == "+"){
        labelNumber = num_first + num_second;
        new_label = QString::number(labelNumber, 'g', 15);
        label->setText(new_label);
        return 1;
    }
    else if(pushButton->text() == "-"){
        labelNumber = num_first - num_second;
        new_label = QString::number(labelNumber, 'g', 15);
        label->setText(new_label);
        return 1;
    }
    else if(pushButton->text() == "*"){
        labelNumber = num_first * num_second;
        new_label = QString::number(labelNumber, 'g', 15);
        label->setText(new_label);
        return 1;
    }
    else if(pushButton->text() == "/"){
        if(num_second == 0)
            label->setText("0");
        else{
            labelNumber = num_first / num_second;
            new_label = QString::number(labelNumber, 'g', 15);
            label->setText(new_label);
        }
        return 1;
    }
    else if(pushButton->text() == "sqrt"){
        labelNumber = sqrt(num_first);
        new_label = QString::number(labelNumber, 'g', 15);
        label->setText(new_label);
        return 0;
    }
    else if(pushButton->text() == "^X"){
        labelNumber = pow(num_first, step);
        new_label = QString::number(labelNumber, 'g', 15);
        label->setText(new_label);
        return 1;
    }
    else if(pushButton->text() == "cos"){
        labelNumber = cos(num_first*PI/180);
        new_label = QString::number(labelNumber, 'g', 15);
        label->setText(new_label);
        return 0;
    }
    else if(pushButton->text() == "sin"){
        labelNumber = sin(num_first*PI/180);
        new_label = QString::number(labelNumber, 'g', 15);
        label->setText(new_label);
        return 0;
    }
    else if(pushButton->text() == "ld"){
        labelNumber = log(num_first);
        new_label = QString::number(labelNumber, 'g', 15);
        label->setText(new_label);
        return 0;
    }
    else if(pushButton->text() == "tg"){
        labelNumber = tan(num_first*PI/180);
        new_label = QString::number(labelNumber, 'g', 15);
        label->setText(new_label);
        return 0;
    }
    else if(pushButton->text() == "ctg"){
        labelNumber = 1/tan(num_first*PI/180);
        new_label = QString::number(labelNumber, 'g', 15);
        label->setText(new_label);
        return 0;
    }
    else if(pushButton->text() == "!"){
        labelNumber = fact(num_first);
        new_label = QString::number(labelNumber, 'g', 15);
        label->setText(new_label);
        return 0;
    }
    else if(pushButton->text() == "log"){
        labelNumber = log(num_first)/log(num_second);
        new_label = QString::number(labelNumber, 'g', 15);
        label->setText(new_label);
        return 1;
    }
}

Widget::~Widget()
{
}
