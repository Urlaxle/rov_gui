#ifndef CRAZYFLIE_GUI_H_
#define CRAZYFLIE_GUI_H_

#include <QMainWindow>
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGroupBox>

class GUI : public QMainWindow {
    Q_OBJECT

public:
    GUI(QWidget *parent = nullptr);
    ~GUI();

private:
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QGroupBox *groupBox;
    QVBoxLayout *layout;
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
};

#endif