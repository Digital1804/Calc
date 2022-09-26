#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QAbstractButton>
#include <QKeyEvent>
#include <QLabel>

class Widget : public QWidget
{
    Q_OBJECT
private:
    QLabel *label;
    int m_value;
    const int DIGIT_LIMIT = 16;
    bool operatorClicked;
    QString storedOperator;
    bool hasStoredNumber;
    double storedNumber;
    void calculate_result();
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void numberGroup_clicked(QAbstractButton*);
    void actionGroup_clicked(QAbstractButton*);
    void on_actionDel_clicked();
    void on_actionCalc_clicked();
    void on_comma_clicked();
    void on_actionClear_clicked();
    void on_actionPercent_clicked();
    void on_actionSign_clicked();

protected:
    //void keyPressEvent(QKeyEvent *e);
};
#endif // WIDGET_H
