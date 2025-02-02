#ifndef ALTITUDE_GUI_HPP_
#define ALTITUDE_GUI_HPP_

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QDoubleValidator>
#include <qcustomplot.h>
#include <QTime>
#include <QUdpSocket>

#include <deque>
#include <chrono>
#include <iostream>

class AltitudeTuning: public QWidget {
    Q_OBJECT 

    public:
        explicit AltitudeTuning(QWidget *parent = nullptr);
        ~AltitudeTuning();
        void update_altitude(double altitude);

    private:
        void turn_on();
        void increase_setpoint();
        void decrease_setpoint();
        void unlock_parameters();
        void update_plot();
        double get_current_timestamp();
        void send_udp_msg(const QString &msg);
        void update_parameters();
        void incoming_messages();
        void store_parameters();

    private:

        // Indicator to show that altitude is valid
        QLabel *altitude_valid_indicator_;
        QTimer *timer_;

        // Altitude line edit
        QLineEdit *altitude_setpoint_;
        double altitude_setpoint_value_;
        double current_altitude_value_;

        // Tuning
        QLineEdit* altitude_kp_input_;
        QLineEdit* altitude_ki_input_;
        QLineEdit* altitude_kd_input_;
        QLineEdit* constant_downforce_input_;
        QLabel* kp_label_;
        QLabel* ki_label_;
        QLabel* kd_label_;
        QLabel* constant_downforce_label_;

        // Socket
        QUdpSocket* udp_socket_;
        QUdpSocket* udp_socket_receive_;

        // Plot
        QCustomPlot *altitude_plot_;
        double window_duration_ = 60.0;
        std::deque<double> altitude_values_;
        std::deque<double> altitude_timestamps_;

        // Flags
        bool altitude_hold_on_ = false;
        bool tuning_on_ = false;
        bool altitude_valid_ = false;
        bool unlock_parameters_ = false;


};

#endif