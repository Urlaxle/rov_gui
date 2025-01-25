#ifndef THRUSTERS_GUI_H_
#define THRUSTERS_GUI_H_

#include <QWidget>
#include <QGridLayout>
#include <QProgressBar>
#include <QLabel>
#include <QStringList>
#include <QTransform>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QGraphicsView>





class rotated_bar : public QGraphicsView {
    Q_OBJECT

    public:
        explicit rotated_bar(QWidget *parent = nullptr);
        ~rotated_bar();
        void set_rotation(int angle); 
        void set_inverted(bool inverted);
        void setOrientation(Qt::Orientation orientation);
        void setValue(int value);
        void setRange(int min, int max);

    private:
        QProgressBar *bar_;
        qreal angle_;
        QGraphicsScene *scene_;
        QGraphicsProxyWidget *proxy_;

};

class thrusters : public QWidget {
    Q_OBJECT

    public:
        explicit thrusters(QWidget *parent = nullptr);
        ~thrusters();

    //QProgressBar* get_thruster(int i) const;
    rotated_bar* get_thruster(int i) const;

    private:
        QHBoxLayout *thruster_layout_;
        rotated_bar *rotated_bars_[4];
        //QProgressBar *bars_[3];
        QProgressBar *bars_[3];
        QLabel *labels_[7];
        QStringList labels_text_= {"VFR", "VFL", "HFR", "HRR", "HFL", "HRL", "VCR"};
};

#endif