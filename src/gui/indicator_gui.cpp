#include "gui/indicator_gui.hpp"

indicators::indicators(QWidget *parent) : QWidget(parent) {
    // Main layout
    main_layout_ = new QHBoxLayout(this);

    // Control widget
    control_widget_ = new QWidget(this);
    QVBoxLayout* control_layout = new QVBoxLayout(control_widget_);
    control_grid_ = new QGridLayout;
    

    // Title
    QLabel* control_label = new QLabel("Control Modes", control_widget_);
    control_label->setAlignment(Qt::AlignCenter);
    control_label->setStyleSheet("font-weight: bold;");
    control_layout->addWidget(control_label);

    // Control mode indicators
    QLabel *waypoint_label = new QLabel("Waypoint Control", control_widget_);
    QLabel *dynamic_label = new QLabel("Dynamic Positioning", control_widget_);
    QLabel *altitude_label = new QLabel("Altitude Hold", control_widget_);
    QLabel *depth_label = new QLabel("Depth Hold", control_widget_);

    waypoint_label->setAlignment(Qt::AlignCenter);
    dynamic_label->setAlignment(Qt::AlignCenter);
    altitude_label->setAlignment(Qt::AlignCenter);
    depth_label->setAlignment(Qt::AlignCenter);

    waypoint_label->setStyleSheet("font-weight: bold;");
    dynamic_label->setStyleSheet("font-weight: bold;");
    altitude_label->setStyleSheet("font-weight: bold;");
    depth_label->setStyleSheet("font-weight: bold;");

    waypoint_indicator_ = new QLabel(control_widget_);
    waypoint_indicator_->setFixedSize(60, 60);
    waypoint_indicator_->setStyleSheet("background-color: red; border-radius: 30px; border: 1px solid black;");
    dynamic_indicator_ = new QLabel(control_widget_);
    dynamic_indicator_->setFixedSize(60, 60);
    dynamic_indicator_->setStyleSheet("background-color: red; border-radius: 30px; border: 1px solid black;");
    altitude_indicator_ = new QLabel(control_widget_);
    altitude_indicator_->setFixedSize(60, 60);
    altitude_indicator_->setStyleSheet("background-color: red; border-radius: 30px; border: 1px solid black;");
    depth_hold_indicator_ = new QLabel(control_widget_);
    depth_hold_indicator_->setFixedSize(60, 60);
    depth_hold_indicator_->setStyleSheet("background-color: red; border-radius: 30px; border: 1px solid black;");

    control_grid_->addWidget(waypoint_label, 0, 0, Qt::AlignCenter);
    control_grid_->addWidget(waypoint_indicator_, 1, 0, Qt::AlignCenter);
    control_grid_->addWidget(dynamic_label, 0, 1, Qt::AlignCenter);
    control_grid_->addWidget(dynamic_indicator_, 1, 1, Qt::AlignCenter);
    control_grid_->addWidget(altitude_label, 2, 0, Qt::AlignCenter);
    control_grid_->addWidget(altitude_indicator_, 3, 0, Qt::AlignCenter);
    control_grid_->addWidget(depth_label, 2, 1, Qt::AlignCenter);
    control_grid_->addWidget(depth_hold_indicator_, 3, 1, Qt::AlignCenter);

    control_layout->addLayout(control_grid_);

    // Control mode color explanations
    QVBoxLayout *control_explenations = new QVBoxLayout;
    QStringList control_explenations_text = {"On", "Available", "Unavailable"}; 
    QStringList control_explenations_colors = {"blue", "green", "red"};
    for (int i = 0; i < 3; ++i) {
        QHBoxLayout *indicator_layout = new QHBoxLayout;

        QLabel *colorLight = new QLabel(parent);
        colorLight->setFixedSize(20, 20); // Smaller light size
        colorLight->setStyleSheet(QString("background-color: %1; border-radius: 10px; border: 1px solid black;")
                                      .arg(control_explenations_colors[i]));

        QLabel *colorLabel = new QLabel(control_explenations_text[i], parent);
        colorLabel->setStyleSheet("font-weight: bold;");

        indicator_layout->addWidget(colorLight);
        indicator_layout->addWidget(colorLabel);

        control_explenations->addLayout(indicator_layout);
    }
    control_layout->addLayout(control_explenations);

    // Sensor widget
    
    sensor_widget_ = new QWidget(this);
    QVBoxLayout* sensor_layout = new QVBoxLayout(sensor_widget_);
    sensor_grid_ = new QGridLayout;
    

    // Title
    QLabel* sensor_label = new QLabel("Sensor Status", sensor_widget_);
    sensor_label->setAlignment(Qt::AlignCenter);
    sensor_label->setStyleSheet("font-weight: bold;");
    sensor_layout->addWidget(sensor_label);

    // Sensor mode indicators
    QLabel *dvl_label = new QLabel("DVL", sensor_widget_);
    QLabel *imu_label = new QLabel("IMU", sensor_widget_);
    QLabel *depth_sensor_label = new QLabel("DEPTH", sensor_widget_);
    QLabel *usbl_label = new QLabel("USBL", sensor_widget_);

    dvl_label->setAlignment(Qt::AlignCenter);
    imu_label->setAlignment(Qt::AlignCenter);
    depth_sensor_label->setAlignment(Qt::AlignCenter);
    usbl_label->setAlignment(Qt::AlignCenter);

    dvl_label->setStyleSheet("font-weight: bold;");
    imu_label->setStyleSheet("font-weight: bold;");
    depth_sensor_label->setStyleSheet("font-weight: bold;");
    usbl_label->setStyleSheet("font-weight: bold;");

    dvl_indicator_ = new QLabel(sensor_widget_);
    dvl_indicator_->setFixedSize(60, 60);
    dvl_indicator_->setStyleSheet("background-color: red; border-radius: 30px; border: 1px solid black;");
    imu_indicator_ = new QLabel(sensor_widget_);
    imu_indicator_->setFixedSize(60, 60);
    imu_indicator_->setStyleSheet("background-color: red; border-radius: 30px; border: 1px solid black;");
    depth_indicator_= new QLabel(sensor_widget_);
    depth_indicator_->setFixedSize(60, 60);
    depth_indicator_->setStyleSheet("background-color: red; border-radius: 30px; border: 1px solid black;");
    usbl_indicator_ = new QLabel(sensor_widget_);
    usbl_indicator_->setFixedSize(60, 60);
    usbl_indicator_->setStyleSheet("background-color: red; border-radius: 30px; border: 1px solid black;");

    sensor_grid_->addWidget(dvl_label, 0, 0, Qt::AlignCenter);
    sensor_grid_->addWidget(dvl_indicator_, 1, 0, Qt::AlignCenter);
    sensor_grid_->addWidget(imu_label, 0, 1, Qt::AlignCenter);
    sensor_grid_->addWidget(imu_indicator_, 1, 1, Qt::AlignCenter);
    sensor_grid_->addWidget(depth_sensor_label, 2, 0, Qt::AlignCenter);
    sensor_grid_->addWidget(depth_indicator_, 3, 0, Qt::AlignCenter);
    sensor_grid_->addWidget(usbl_label, 2, 1, Qt::AlignCenter);
    sensor_grid_->addWidget(usbl_indicator_, 3, 1, Qt::AlignCenter);

    sensor_layout->addLayout(sensor_grid_);

    // Sensor mode color explanations
    QVBoxLayout *sensor_explenations = new QVBoxLayout;
    QStringList sensor_explenations_text = {"Available", "Degraded", "Unavailable"}; 
    QStringList sensor_explenations_colors = {"green", "yellow", "red"};
    for (int i = 0; i < 3; ++i) {
        QHBoxLayout *indicator_layout = new QHBoxLayout;

        QLabel *colorLight = new QLabel(parent);
        colorLight->setFixedSize(20, 20); // Smaller light size
        colorLight->setStyleSheet(QString("background-color: %1; border-radius: 10px; border: 1px solid black;")
                                      .arg(sensor_explenations_colors[i]));

        QLabel *colorLabel = new QLabel(sensor_explenations_text[i], parent);
        colorLabel->setStyleSheet("font-weight: bold;");

        indicator_layout->addWidget(colorLight);
        indicator_layout->addWidget(colorLabel);

        sensor_explenations->addLayout(indicator_layout);
    }
    sensor_layout->addLayout(sensor_explenations);
    
    main_layout_->addWidget(control_widget_);
    main_layout_->addWidget(sensor_widget_);
    }

indicators::~indicators() {
}

// Status Indicator
void indicators::set_dvl_status(int status) {
    switch (status) {
        case 0:
            dvl_indicator_->setStyleSheet("background-color: red; border-radius: 30px; border: 1px solid black;");
            break;
        case 1:
            dvl_indicator_->setStyleSheet("background-color: green; border-radius: 30px; border: 1px solid black;");
            break;
        case 2:
            dvl_indicator_->setStyleSheet("background-color: yellow; border-radius: 30px; border: 1px solid black;");
            break;
    }
}

void indicators::set_imu_status(int status) {
    switch (status) {
        case 0:
            imu_indicator_->setStyleSheet("background-color: red; border-radius: 30px; border: 1px solid black;");
            break;
        case 1:
            imu_indicator_->setStyleSheet("background-color: green; border-radius: 30px; border: 1px solid black;");
            break;
        case 2:
            imu_indicator_->setStyleSheet("background-color: yellow; border-radius: 30px; border: 1px solid black;");
            break;
    }
}

void indicators::set_depth_status(int status) {
    switch (status) {
        case 0:
            depth_indicator_->setStyleSheet("background-color: red; border-radius: 30px; border: 1px solid black;");
            break;
        case 1:
            depth_indicator_->setStyleSheet("background-color: green; border-radius: 30px; border: 1px solid black;");
            break;
        case 2:
            depth_indicator_->setStyleSheet("background-color: yellow; border-radius: 30px; border: 1px solid black;");
            break;
    }
}

void indicators::set_usbl_status(int status) {
    switch (status) {
        case 0:
            usbl_indicator_->setStyleSheet("background-color: red; border-radius: 30px; border: 1px solid black;");
            break;
        case 1:
            usbl_indicator_->setStyleSheet("background-color: green; border-radius: 30px; border: 1px solid black;");
            break;
        case 2:
            usbl_indicator_->setStyleSheet("background-color: yellow; border-radius: 30px; border: 1px solid black;");
            break;
    }
}

void indicators::set_waypoint_status(int status) {
    switch (status) {
        case 0:
            waypoint_indicator_->setStyleSheet("background-color: red; border-radius: 30px; border: 1px solid black;");
            break;
        case 1:
            waypoint_indicator_->setStyleSheet("background-color: green; border-radius: 30px; border: 1px solid black;");
            break;
        case 2:
            waypoint_indicator_->setStyleSheet("background-color: blue; border-radius: 30px; border: 1px solid black;");
            break;
    }
}

void indicators::set_dynamic_status(int status) {
    switch (status) {
        case 0:
            dynamic_indicator_->setStyleSheet("background-color: red; border-radius: 30px; border: 1px solid black;");
            break;
        case 1:
            dynamic_indicator_->setStyleSheet("background-color: green; border-radius: 30px; border: 1px solid black;");
            break;
        case 2:
            dynamic_indicator_->setStyleSheet("background-color: blue; border-radius: 30px; border: 1px solid black;");
            break;
    }
}

void indicators::set_altitude_status(int status) {
    switch (status) {
        case 0:
            altitude_indicator_->setStyleSheet("background-color: red; border-radius: 30px; border: 1px solid black;");
            break;
        case 1:
            altitude_indicator_->setStyleSheet("background-color: green; border-radius: 30px; border: 1px solid black;");
            break;
        case 2:
            altitude_indicator_->setStyleSheet("background-color: blue; border-radius: 30px; border: 1px solid black;");
            break;
    }
}

void indicators::set_depth_hold_status(int status) {
    switch (status) {
        case 0:
            depth_hold_indicator_->setStyleSheet("background-color: red; border-radius: 30px; border: 1px solid black;");
            break;
        case 1:
            depth_hold_indicator_->setStyleSheet("background-color: green; border-radius: 30px; border: 1px solid black;");
            break;
        case 2:
            depth_hold_indicator_->setStyleSheet("background-color: blue; border-radius: 30px; border: 1px solid black;");
            break;
    }
}   