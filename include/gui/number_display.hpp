#ifndef NUMBER_DISPLAY_HPP_
#define NUMBER_DISPLAY_HPP_

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class number_display : public QWidget {
    Q_OBJECT

    public:
        number_display(QWidget *parent = nullptr);
        ~number_display();

        void set_altitude(const float& altitude);
        void set_velocity(const float& velocity);
        void set_depth(const float& depth);

    private:

        QLabel *altitude_label;
        QLabel *velocity_label;
        QLabel *depth_label;

};
#endif 