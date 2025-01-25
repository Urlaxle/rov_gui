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



class rotated_bar : public QWidget {
    Q_OBJECT

    public:
        explicit rotated_bar(QWidget *parent = nullptr);
        ~rotated_bar();
        void set_rotation(int angle); 
        void setOrientation(Qt::Orientation orientation);
        void setValue(int value);
        void setRange(int min, int max);

    private:
        int angle_;
        QProgressBar *bar_;
        QGraphicsProxyWidget *proxy_;
};

class thrusters : public QWidget {
    Q_OBJECT

    public:
        explicit thrusters(QWidget *parent = nullptr);
        ~thrusters();

    QProgressBar* get_thruster(int i) const;

    private:
        QGridLayout *thruster_layout_;
        QProgressBar*bars_[7];
        QLabel *labels_[7];
        QStringList labels_text_= {"T1", "T2", "T3", "T4", "T5", "T6", "T7"};
};

#endif