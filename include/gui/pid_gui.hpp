#ifndef PID_GUI_HPP_
#define PID_GUI_HPP_


#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QPushButton>
#include <QString>
#include <QInputDialog>
#include <QDialog>
#include <QTime>
#include <QUdpSocket>
#include <QHostAddress>

class key_dialog : public QDialog {
    Q_OBJECT

    public:
        explicit key_dialog(QWidget* parent = nullptr);
        ~key_dialog();

        void set_key(QString key);

        bool is_key_correct();

    private:
        void key_entered();
        void close();

    private:
        QLineEdit* key_input_;
        QLabel* error_label_;
        QPushButton* key_button_;
        QPushButton *cancel_button_;
        QString key_;
        bool password_correct_ = false;
};


class PID_GUI : public QWidget {
    Q_OBJECT

    public:
        explicit PID_GUI(QWidget* parent = nullptr);
        ~PID_GUI();


    private:
        void send_button_pressed(); 
        void send_command_button_pressed();
        void default_button_pressed();
        void low_gains_button_pressed();
        void medium_gains_button_pressed();
        void high_gains_button_pressed();
        void advanced_button_pressed();
        void set_default_gains();
        void send_udp_msg(const QString &msg);

        void enable_advanced_settings(bool enable);

    private:

        // Widgets

        // DEFAULT CONFIGURATIONS
        QPushButton* low_gains_button_;
        QPushButton* medium_gains_button_;
        QPushButton* high_gains_button_;
        QPushButton* advanced_settings_button_;

        // Socket
        QUdpSocket* udp_socket_;

        // MOVE SIDE
        QLineEdit* surge_move_;
        QLineEdit* sway_move_;
        QLineEdit* heave_move_;
        QLineEdit* yaw_move_;
        QPushButton* send_command_button_;


        // GAINS SIDE
        // Should I place these in a vector instead?
        QLineEdit* surge_kp_input_;
        QLineEdit* surge_ki_input_;
        QLineEdit* surge_kd_input_;
        QLineEdit* sway_kp_input_;
        QLineEdit* sway_ki_input_;
        QLineEdit* sway_kd_input_;
        QLineEdit* heave_kp_input_;
        QLineEdit* heave_ki_input_;
        QLineEdit* heave_kd_input_;
        QLineEdit* heave_downforce_input_;
        QLineEdit* yaw_kp_input_;
        QLineEdit* yaw_ki_input_;
        QLineEdit* yaw_kd_input_;

        QLabel* surge_label_; 
        QLabel* sway_label_;
        QLabel* heave_label_;
        QLabel* yaw_label_;
        QLabel* surge_kp_label_;
        QLabel* surge_ki_label_;
        QLabel* surge_kd_label_;
        QLabel* surge_downforce_label_;
        QLabel* sway_kp_label_;
        QLabel* sway_ki_label_;
        QLabel* sway_kd_label_;
        QLabel* sway_downforce_label_;
        QLabel* heave_kp_label_;
        QLabel* heave_ki_label_;
        QLabel* heave_kd_label_;
        QLabel* heave_downforce_label_;
        QLabel* yaw_kp_label_;
        QLabel* yaw_ki_label_;
        QLabel* yaw_kd_label_;
        QLabel* yaw_downforce_label_;

        // Buttons
        QPushButton* send_button_;
        QPushButton* default_button_;

        // Controller gains
        double surge_downforce_, surge_kp_, surge_ki_, surge_kd_;
        double sway_downforce_, sway_kp_, sway_ki_, sway_kd_;
        double heave_downforce_, heave_kp_, heave_ki_, heave_kd_;
        double yaw_downforce_, yaw_kp_, yaw_ki_, yaw_kd_;

        // 
        QString key_ = "tbs";
};









#endif