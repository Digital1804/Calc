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
                  "!", "^X", "ld", "logn", "",
                  "1", "2", "3", "+", "ctg",
                  "4", "5", "6", "-", "tg",
                  "7", "8", "9", "*", "cos",
                  ".", "0", "=", "/", "sin"
                });
    QList<QString> numbers({ "1", "2", "3", "4", "5", "6", "7", "8", "9", "0"});


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

    for (int i=0; i<(values.length()/columns); i++) {
        for (int j=0; j<columns; j++) {
            grid->addWidget(digitButtons[pos], i, j);
            pos++;
        }
    }
    numberGroup->connect(numberGroup,SIGNAL(buttonClicked(QAbstractButton*)),this, SLOT(numberGroup_clicked(QAbstractButton*)));
    actionGroup->connect(actionGroup,SIGNAL(buttonClicked(QAbstractButton*)),this, SLOT(actionGroup_clicked(QAbstractButton*)));

    operatorClicked = false;
    hasStoredNumber = false;
    setLayout(grid1);
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
    timer->start(1000); // И запустим таймер
}

void Widget::slotTimerAlarm() {
    time->setText(QTime::currentTime().toString("hh:mm:ss"));
}

void Widget::numberGroup_clicked(QAbstractButton* button){
    QString displayLabel = label->text();
    if (operatorClicked || label->text()=="0") {// && label->text().toDouble() !=storedNumber
        displayLabel.clear();
        operatorClicked = false;
    }
    if (displayLabel.length() >= DIGIT_LIMIT) {
        return;
    }
    displayLabel.append(button->text());
    label->setText(displayLabel);
}

void Widget::actionGroup_clicked(QAbstractButton* button){
    if (operatorClicked) {
        storedOperator = button->text();
    }
    else {
        if (hasStoredNumber) {
            calculate_result();
        }
        else {
            hasStoredNumber = true;
            QString displayLabel = label->text();
        }
        operatorClicked = true;
        storedOperator = button->text();
    }
}

void Widget::on_actionClear_clicked(){
    label->setText(" ");
    operatorClicked = false;
    hasStoredNumber = false;
}

void Widget::on_actionDel_clicked(){
    QString displayLabel = label->text();
    if (displayLabel.length() == 0) {
        return;
    }
    displayLabel.QString::chop(1);
    label->setText(displayLabel);
}

void Widget::on_actionCalc_clicked(){
    QString displayLabel = label->text();
    if (!hasStoredNumber || displayLabel.length() < 1 || operatorClicked) {
        return;
    }
    calculate_result();
    hasStoredNumber = false;
}

void Widget::on_comma_clicked(){
    QString displayLabel = label->text();
    if (displayLabel.length() >= (DIGIT_LIMIT - 1) ||
        displayLabel.contains('.', Qt::CaseSensitive)) {
        return;
    }
    if (displayLabel.length() == 0) {
        displayLabel = "0";
    }
    displayLabel.append('.');
    label->setText(displayLabel);
}

void Widget::on_actionPercent_clicked(){
    QString displayLabel = label->text();
    double percentage = displayLabel.toDouble();
    percentage *= 0.01;
    displayLabel = QString::number(percentage,'g', DIGIT_LIMIT);
    label->setText(displayLabel);
}

void Widget::on_actionSign_clicked(){
    QString displayLabel = label->text();
    double percentage = displayLabel.toDouble();
    percentage *= -1;
    displayLabel = QString::number(percentage,'g', DIGIT_LIMIT);
    label->setText(displayLabel);
}

void Widget::calculate_result() {
    QString displayLabel = label->text();
     if (displayLabel.endsWith('.',Qt::CaseSensitive)) {
         displayLabel.QString::chop(1);
     }
     if (storedOperator == "+") {
         storedNumber += displayLabel.toDouble();
     }
     else if (storedOperator == "-") {
         storedNumber -= displayLabel.toDouble();
     }
     else if (storedOperator == "*") {
         storedNumber *= displayLabel.toDouble();
     }
     else if (storedOperator == "/") {
         storedNumber /= displayLabel.toDouble();
     }
    // else if (storedOperator == "=") {
         displayLabel = QString::number(storedNumber,'g', DIGIT_LIMIT);
     //}
     label->setText(displayLabel);
}

Widget::~Widget()
{
}
