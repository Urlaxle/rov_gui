#ifndef INDICATOR_GUI_H_
#define INDICATOR_GUI_H_

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGridLayout>
#include <QLabel>


class indicators : public QWidget {
    Q_OBJECT

    public:
        explicit indicators(QWidget *parent = nullptr);
        ~indicators();

        // Sensor status
        void set_dvl_status(int status);
        void set_imu_status(int status);
        void set_depth_status(int status);
        void set_usbl_status(int status);

        // Controller status
        void set_waypoint_status(int status);
        void set_dynamic_status(int status);
        void set_altitude_status(int status);
        void set_depth_hold_status(int status);

    private:
        
        // GUI elements
        QHBoxLayout *main_layout_;
        QWidget *control_widget_;
        QWidget *sensor_widget_;
        QGridLayout *control_grid_;
        QGridLayout *sensor_grid_;

        // The different status lights
        QLabel *dvl_indicator_;
        QLabel *imu_indicator_;
        QLabel *depth_indicator_;
        QLabel *usbl_indicator_;
        QLabel *waypoint_indicator_;
        QLabel *dynamic_indicator_;
        QLabel *altitude_indicator_;
        QLabel *depth_hold_indicator_;

};

#endif