#ifndef THRUSTERS_GUI_H_
#define THRUSTERS_GUI_H_

#include <QWidget>
#include <QGridLayout>
#include <QProgressBar>
#include <QLabel>
#include <QStringList>

class thrusters : public QWidget {
    Q_OBJECT

    public:
        explicit thrusters(QWidget *parent = nullptr);
        ~thrusters();

    QProgressBar* get_thruster(int i) const;

    private:
        QGridLayout *thruster_layout_;
        QProgressBar *bars_[7];
        QLabel *labels_[7];
        QStringList labels_text_= {"T1", "T2", "T3", "T4", "T5", "T6", "T7"};
};

#endif