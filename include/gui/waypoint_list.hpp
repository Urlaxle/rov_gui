#ifndef WAYPOINT_LISTS_H_
#define WAYPOINT_LISTS_H_

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QFileDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QTableWidget>
#include <QCheckBox>


class waypoint_list : public QWidget {
    Q_OBJECT

    public:
        explicit waypoint_list(QWidget *parent = nullptr);
        ~waypoint_list();

    private:
        QVBoxLayout *main_layout_;
        QHBoxLayout *waypoint_layout_;
        QVBoxLayout *waypoint_list_layout_;
        QVBoxLayout *waypoint_button_layout_;
        QPushButton *add_waypoint_button_;
        QPushButton *remove_waypoint_button_;
        QTableWidget *waypoint_list_widget_;

        // Buttons
        QPushButton *browse_button_;
        QPushButton *send_button_;
        QPushButton *confirm_button_;
        QPushButton *clear_button_;

        // Q Line Edit
        QLineEdit *altitude_edit_;
        QLineEdit *velocity_edit_;

        // Error labels
        QLabel *error_label_;

        // Functions
        void add_waypoint(const double& x, const double& y);

    private slots:
        void browse_buttons_pressed();
        void send_button_pressed();
        void clear_button_pressed();
        void confirm_button_pressed();

    private:

        // Altitude and velocity for waypoint controller
        double altitude_ = 0.5;
        double velocity_ = 0.5;

        // Waypoint list

};

#endif