#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QAbstractButton>
#include <QKeyEvent>
#include <QLabel>
#include <QTimer>
#include <QTime>

class Widget : public QWidget
{
    Q_OBJECT
private:
    //QPushButton *digitButtons;
    double num_first, num_second, labelNumber;
    int step;
    QLabel *label;
    QLabel *time;
    QTimer *timer;
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    int on_pushButton_equal_clicked();
    void digits_numbers();
    void operations();
    void slotTimerAlarm();

protected:
    //void keyPressEvent(QKeyEvent *e);
};
#endif // WIDGET_H
