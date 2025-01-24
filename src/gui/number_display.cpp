#include "gui/number_display.hpp"

number_display::number_display(QWidget *parent) : QWidget(parent) {
    altitude_label = new QLabel("Altitude [m]: 0.0", this);
    altitude_label->setStyleSheet("font-size: 30px; font-weight: bold;");
    velocity_label = new QLabel("Velocity [m/s]: 0.0", this);
    velocity_label->setStyleSheet("font-size: 30px; font-weight: bold;");
    depth_label = new QLabel("Depth [m]: 0.0", this);
    depth_label->setStyleSheet("font-size: 30px; font-weight: bold;");

    QVBoxLayout *main_layout = new QVBoxLayout(this);
    main_layout->addWidget(altitude_label);
    main_layout->addWidget(velocity_label);
    main_layout->addWidget(depth_label);

    main_layout->setAlignment(altitude_label, Qt::AlignCenter);
    main_layout->setAlignment(depth_label, Qt::AlignCenter);
    main_layout->setAlignment(velocity_label, Qt::AlignCenter);

}

number_display::~number_display() {
    delete altitude_label;
    delete velocity_label;
    delete depth_label;
}

void number_display::set_altitude(const float& altitude) {
    altitude_label->setText("Altitude: " + QString::number(altitude) + " [m]");
}

void number_display::set_velocity(const float& velocity) {
    velocity_label->setText("Velocity: " + QString::number(velocity) + " [m/s]");
}

void number_display::set_depth(const float& depth) {
    depth_label->setText("Depth: " + QString::number(depth) + " [m]");
}