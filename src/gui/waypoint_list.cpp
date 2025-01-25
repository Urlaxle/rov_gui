#include "gui/waypoint_list.hpp"
#include <iostream>

waypoint_list::waypoint_list(QWidget *parent) : QWidget(parent) {

    // Main Layout
    main_layout_ = new QVBoxLayout(this);
    QHBoxLayout* button_layout_1 = new QHBoxLayout(this);
    QHBoxLayout* button_layout_2 = new QHBoxLayout(this);

    // Widget title
    QLabel *title = new QLabel("Waypoint List", this);
    title->setStyleSheet("font-weight: bold; font-size: 12px;");

    // Waypoint list display
    waypoint_list_widget_ = new QTableWidget(this);
    waypoint_list_widget_->setColumnCount(3);
    waypoint_list_widget_->setHorizontalHeaderLabels(QStringList() << "Y" << "X" << "Go");
    waypoint_list_widget_->setColumnWidth(1, 104);
    waypoint_list_widget_->setColumnWidth(2, 104);
    waypoint_list_widget_->setColumnWidth(3, 104);




    main_layout_->addWidget(waypoint_list_widget_);

    // Browse button
    browse_button_ = new QPushButton("Select file", this);
    connect(browse_button_, &QPushButton::clicked, this, &waypoint_list::browse_buttons_pressed);

    // Send button
    send_button_ = new QPushButton("Send waypoints", this);
    connect(send_button_, &QPushButton::clicked, this, &waypoint_list::send_button_pressed);

    // Pause button
    confirm_button_ = new QPushButton("Confirm", this);
    connect(confirm_button_, &QPushButton::clicked, this, &waypoint_list::confirm_button_pressed);

    // Clear button
    clear_button_ = new QPushButton("Clear waypoints", this);
    connect(clear_button_, &QPushButton::clicked, this, &waypoint_list::clear_button_pressed);

    // Error label
    error_label_ = new QLabel(this);
    error_label_->setStyleSheet("color: red;");

    // Altitude and velocity widgets
    QVBoxLayout* altitude_layout = new QVBoxLayout(this);
    QLabel *altitude_label = new QLabel("Altitude (m):", this);
    altitude_label->setStyleSheet("font-weight: bold;");
    altitude_edit_ = new QLineEdit(this);
    altitude_edit_->setValidator(new QDoubleValidator(0.5, 10.0, 2, this));
    altitude_edit_->setText("0.5");
    altitude_layout->addWidget(altitude_label);
    altitude_layout->addWidget(altitude_edit_); 
    altitude_layout->setAlignment(altitude_label, Qt::AlignCenter);

    QVBoxLayout* velocity_layout = new QVBoxLayout(this);
    QLabel *velocity_label = new QLabel("Velocity (m/s):", this);
    velocity_label->setStyleSheet("font-weight: bold;");
    velocity_edit_ = new QLineEdit(this);
    velocity_edit_->setValidator(new QDoubleValidator(0.1, 1.0, 2, this));
    velocity_edit_->setText("0.5");
    velocity_layout->addWidget(velocity_label);
    velocity_layout->addWidget(velocity_edit_);
    velocity_layout->setAlignment(velocity_label, Qt::AlignCenter);

    QHBoxLayout* altitude_velocity_layout = new QHBoxLayout(this);

    // Layout stuff
    button_layout_1->addWidget(browse_button_);
    button_layout_1->addWidget(confirm_button_);
    button_layout_2->addWidget(send_button_);
    button_layout_2->addWidget(clear_button_);
    altitude_velocity_layout->addLayout(altitude_layout);
    altitude_velocity_layout->addLayout(velocity_layout);
    main_layout_->addWidget(title);
    main_layout_->addWidget(waypoint_list_widget_);
    main_layout_->addLayout(altitude_velocity_layout);
    main_layout_->addWidget(error_label_);
    main_layout_->setAlignment(error_label_, Qt::AlignCenter);
    main_layout_->addLayout(button_layout_1);
    main_layout_->addLayout(button_layout_2);
    main_layout_->setAlignment(title, Qt::AlignCenter);

}

waypoint_list::~waypoint_list() {
}

void  waypoint_list::browse_buttons_pressed() {

    // Open file dialog
    QString file_name = QFileDialog::getOpenFileName(this, "Open Waypoint File", QDir::homePath(), "Waypoint Files (*.txt)");

    // Parse file
}


void waypoint_list::send_button_pressed() {

    double x1 = 0.0;
    double y1 = 0.0;

    double x2 = 1.0;
    double y2 = 1.0;

    add_waypoint(x1, y1);
    add_waypoint(x2, y2);

}

void waypoint_list::clear_button_pressed() {

}   

// Callback to confirm velocity and altitude for the waypoint controller
void waypoint_list::confirm_button_pressed() {

    // Clear error label
    error_label_->clear();

    // Check that values are within bounds
    if (altitude_edit_->text().isEmpty() || altitude_edit_->text().toDouble() < 0.5 || altitude_edit_->text().toDouble() > 10.0) {
        altitude_edit_->setStyleSheet("border: 1px solid red;");
        error_label_->setText("Please enter a value between 0.5 and 10.0 [m]");
        return;
    } else {
        altitude_edit_->setStyleSheet("");
    }

    if (velocity_edit_->text().isEmpty() || velocity_edit_->text().toDouble() < 0.1 || velocity_edit_->text().toDouble() > 1.0) {
        velocity_edit_->setStyleSheet("border: 1px solid red;");
        error_label_->setText("Please enter a value between 0.1 and 1.0 [m/s]");
        return;
    } else {
        velocity_edit_->setStyleSheet("");
    }

    // Update altitude and velocity
    altitude_ = altitude_edit_->text().toDouble();
    velocity_ = velocity_edit_->text().toDouble();

}

void waypoint_list::add_waypoint(const double& x, const double& y) {

    // Add waypoint to list
    int row = waypoint_list_widget_->rowCount();
    waypoint_list_widget_->insertRow(row);
    waypoint_list_widget_->setItem(row, 0, new QTableWidgetItem(QString::number(y)));
    waypoint_list_widget_->setItem(row, 1, new QTableWidgetItem(QString::number(x)));

    // Add checkbox to go to waypoint 
    QCheckBox* checkbox = new QCheckBox(this);
    checkbox->setChecked(true);
    QWidget* checkbox_widget = new QWidget(this);
    QHBoxLayout* checkbox_layout = new QHBoxLayout(this);
    checkbox_layout->addWidget(checkbox);
    checkbox_layout->setAlignment(checkbox, Qt::AlignCenter);
    checkbox_layout->setContentsMargins(0,0,0,0);
    checkbox_widget->setLayout(checkbox_layout);
    waypoint_list_widget_->setCellWidget(row, 2, checkbox_widget);
}