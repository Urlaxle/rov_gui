#ifndef COMPASS_GUI_H_
#define COMPASS_GUI_H_

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QTimer>

#include <iostream>

// Compass View
class compass : public QWidget {
public:
    explicit compass(QWidget *parent = nullptr);
    ~compass();

    void set_heading(const int& heading, const int& heading_hold);

    protected:
        void paintEvent(QPaintEvent *event) override;

    private:
        QPixmap robot_image;
        qreal heading_angle;
        qreal heading_setpoint;
        bool show_setpoint = false;

    private:
        void update_heading();
};

#endif