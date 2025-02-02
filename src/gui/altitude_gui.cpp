#include "gui/altitude_gui.hpp"

AltitudeTuning::AltitudeTuning(QWidget *parent) : QWidget(parent) {

    // Main Layout
    QHBoxLayout* altitude_tuning_layout = new QHBoxLayout(this);
    udp_socket_ = new QUdpSocket(this);

    udp_socket_receive_ = new QUdpSocket(this);
    udp_socket_receive_->bind(QHostAddress::LocalHost, 9101);
    connect(udp_socket_receive_, &QUdpSocket::readyRead, this, &AltitudeTuning::incoming_messages);

    ///////////////////////////////////// LEFT LAYOUT /////////////////////////////////////

    // Left Layout
    QVBoxLayout* altitude_tuning_left_layout_ = new QVBoxLayout;

    // Status light widget
    QVBoxLayout *altitude_valid_layout = new QVBoxLayout;
    QWidget* altitude_valid_widget = new QWidget(this);
    QLabel* altitude_valid_label = new QLabel("Altitude Hold Availability", this);
    altitude_valid_label->setAlignment(Qt::AlignCenter);
    altitude_valid_label->setStyleSheet("font-weight: bold; font-size: 20px; color: black;");
    altitude_valid_indicator_ = new QLabel(this);
    altitude_valid_indicator_->setFixedSize(180, 180);
    altitude_valid_indicator_->setStyleSheet("background-color: red; border-radius: 90px; border: 1px solid black;");
    altitude_valid_indicator_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    altitude_valid_layout->addWidget(altitude_valid_label, 1, Qt::AlignCenter);
    altitude_valid_layout->addWidget(altitude_valid_indicator_, 1, Qt::AlignCenter);
    altitude_valid_widget->setLayout(altitude_valid_layout);

    // Setpoint widget
    QLabel* setpoint_label = new QLabel("Altitude Setpoint", this);
    setpoint_label->setAlignment(Qt::AlignCenter);
    setpoint_label->setStyleSheet("font-weight: bold; font-size: 20px; color: black;");
    QWidget *setpoint_widget = new QWidget(this);
    QVBoxLayout *setpoint_layout = new QVBoxLayout;
    QPushButton *setpoint_up_button = new QPushButton("+", this);
    setpoint_up_button->setFixedSize(120, 60);
    setpoint_up_button->setStyleSheet("font-size: 30px;");
    setpoint_up_button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    QPushButton *setpoint_down_button = new QPushButton("-", this);
    setpoint_down_button->setFixedSize(120, 60);
    setpoint_down_button->setStyleSheet("font-size: 30px;");
    setpoint_down_button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    altitude_setpoint_ = new QLineEdit(this);
    altitude_setpoint_->setFixedSize(120, 60);
    altitude_setpoint_->setStyleSheet("font-size: 30px;");
    altitude_setpoint_->setAlignment(Qt::AlignCenter);
    altitude_setpoint_->setValidator(new QDoubleValidator(0, 100, 2, this));
    altitude_setpoint_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    altitude_setpoint_->setAlignment(Qt::AlignCenter);
    setpoint_layout->addWidget(setpoint_label, 1, Qt::AlignCenter);
    setpoint_layout->addWidget(setpoint_up_button, 1, Qt::AlignCenter);
    setpoint_layout->addWidget(altitude_setpoint_, 1, Qt::AlignCenter);
    setpoint_layout->addWidget(setpoint_down_button, 1, Qt::AlignCenter);
    setpoint_layout->setSpacing(0);
    setpoint_widget->setLayout(setpoint_layout);



    // Turn On widget
    QVBoxLayout* turn_on_layout = new QVBoxLayout;
    QWidget* turn_on_widget = new QWidget(this);
    QLabel* turn_on_label = new QLabel("Altitude Hold", this);
    turn_on_label->setAlignment(Qt::AlignCenter);
    turn_on_label->setStyleSheet("font-weight: bold; font-size: 20px; color: black;");
    QPushButton *turn_on_button = new QPushButton("ON", this);
    turn_on_button->setFixedSize(240, 240);
    turn_on_button->setStyleSheet("background-color: green; color: white; font-size: 20px;");
    turn_on_button->setCheckable(true);
    turn_on_button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    connect(turn_on_button, &QPushButton::clicked, this, &AltitudeTuning::turn_on);
    connect(setpoint_up_button, &QPushButton::clicked, this, &AltitudeTuning::increase_setpoint);
    connect(setpoint_down_button, &QPushButton::clicked, this, &AltitudeTuning::decrease_setpoint);
    turn_on_layout->addWidget(turn_on_label, 1, Qt::AlignCenter);
    turn_on_layout->addWidget(turn_on_button, 1, Qt::AlignCenter);
    turn_on_widget->setLayout(turn_on_layout);

    altitude_tuning_left_layout_->addWidget(altitude_valid_widget, 10, Qt::AlignCenter);
    altitude_tuning_left_layout_->addWidget(setpoint_widget, 1, Qt::AlignCenter);
    altitude_tuning_left_layout_->addWidget(turn_on_widget, 10, Qt::AlignCenter);
    altitude_tuning_left_layout_->setAlignment(Qt::AlignCenter);
    altitude_tuning_left_layout_->setSpacing(0);
    altitude_tuning_left_layout_->addStretch();
    altitude_tuning_left_layout_->setContentsMargins(0, 0, 0, 0);


    ////////////////////////////////// MIDDLE LAYOUT //////////////////////////////////

    // Middle layout
    QVBoxLayout* altitude_tuning_middle_layout_ = new QVBoxLayout;

    // Altitude Tuning
    kp_label_ = new QLabel("KP");
    kp_label_->setAlignment(Qt::AlignCenter);
    kp_label_->setStyleSheet("font-weight: bold; font-size: 20px; color: gray;");
    ki_label_ = new QLabel("KI");
    ki_label_->setAlignment(Qt::AlignCenter);
    ki_label_->setStyleSheet("font-weight: bold; font-size: 20px; color: gray;");
    kd_label_ = new QLabel("KD");
    kd_label_->setAlignment(Qt::AlignCenter);
    kd_label_->setStyleSheet("font-weight: bold; font-size: 20px; color: gray;");
    constant_downforce_label_ = new QLabel("Downforce");
    constant_downforce_label_->setAlignment(Qt::AlignCenter);
    constant_downforce_label_->setStyleSheet("font-weight: bold; font-size: 20px; color: gray;");

    altitude_kp_input_ = new QLineEdit(this); 
    altitude_kp_input_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    altitude_kp_input_->setValidator(new QDoubleValidator(0, 100, 2, this));
    altitude_kp_input_->setAlignment(Qt::AlignCenter);
    altitude_kp_input_->setStyleSheet("font-size: 20px;");
    altitude_ki_input_ = new QLineEdit(this);
    altitude_ki_input_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    altitude_ki_input_->setValidator(new QDoubleValidator(0, 100, 2, this));
    altitude_ki_input_->setAlignment(Qt::AlignCenter);
    altitude_ki_input_->setStyleSheet("font-size: 20px;");
    altitude_kd_input_ = new QLineEdit(this);
    altitude_kd_input_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    altitude_kd_input_->setValidator(new QDoubleValidator(0, 100, 2, this));
    altitude_kd_input_->setAlignment(Qt::AlignCenter);
    altitude_kd_input_->setStyleSheet("font-size: 20px;");
    constant_downforce_input_ = new QLineEdit(this);
    constant_downforce_input_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    constant_downforce_input_->setValidator(new QDoubleValidator(0, 100, 2, this));
    constant_downforce_input_->setAlignment(Qt::AlignCenter);
    constant_downforce_input_->setStyleSheet("font-size: 20px;");

    altitude_kp_input_->setDisabled(true);
    altitude_ki_input_->setDisabled(true);
    altitude_kd_input_->setDisabled(true);
    constant_downforce_input_->setDisabled(true);

    altitude_kp_input_->setText("0.0");
    altitude_ki_input_->setText("0.0");
    altitude_kd_input_->setText("0.0");
    constant_downforce_input_->setText("0.0");

    // Unlock Button
    QPushButton *unlock_button = new QPushButton("Unlock Parameters", this);
    QPushButton *send_parameters = new QPushButton("Send Parameters", this);
    QPushButton *store_parameters = new QPushButton("Store Parameters", this);

    connect(unlock_button, &QPushButton::clicked, this, &AltitudeTuning::unlock_parameters);
    connect(send_parameters, &QPushButton::clicked, this, &AltitudeTuning::update_parameters);
    connect(store_parameters, &QPushButton::clicked, this, &AltitudeTuning::store_parameters);

    // layout
    altitude_tuning_middle_layout_->addWidget(constant_downforce_label_);
    altitude_tuning_middle_layout_->addWidget(constant_downforce_input_);
    altitude_tuning_middle_layout_->addWidget(kp_label_);
    altitude_tuning_middle_layout_->addWidget(altitude_kp_input_);
    altitude_tuning_middle_layout_->addWidget(ki_label_);
    altitude_tuning_middle_layout_->addWidget(altitude_ki_input_);
    altitude_tuning_middle_layout_->addWidget(kd_label_);
    altitude_tuning_middle_layout_->addWidget(altitude_kd_input_);
    altitude_tuning_middle_layout_->addWidget(send_parameters);
    altitude_tuning_middle_layout_->addWidget(unlock_button);
    altitude_tuning_middle_layout_->addWidget(store_parameters);
    altitude_tuning_middle_layout_->setAlignment(Qt::AlignCenter);

    // Read parameter file if it exists
    QFile file("parameters.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        QString parameters = stream.readLine();
        QStringList parameter_list = parameters.split(",");
        if (parameter_list.size() == 4) {
            altitude_kp_input_->setText(parameter_list[0]);
            altitude_ki_input_->setText(parameter_list[1]);
            altitude_kd_input_->setText(parameter_list[2]);
            constant_downforce_input_->setText(parameter_list[3]);
        }
        file.close();
    }

    ////////////////////////////////// RIGHT LAYOUT //////////////////////////////////

    QVBoxLayout *altitude_tuning_right_layout = new QVBoxLayout;

    altitude_plot_ = new QCustomPlot(this);
    altitude_plot_->addGraph();
    altitude_plot_->graph(0)->setName("Altitude");
    altitude_plot_->xAxis->setLabel("Time [s]");
    altitude_plot_->yAxis->setLabel("Altitude [m]");
    altitude_plot_->xAxis->setRange(0, window_duration_);
    altitude_plot_->yAxis->setRange(0, 10);
    altitude_plot_->graph(0)->setPen(QPen(Qt::red, 2, Qt::SolidLine));
    altitude_plot_->addGraph();
    altitude_plot_->graph(1)->setName("Setpoint");
    altitude_plot_->graph(1)->setPen(QPen(Qt::blue, 2, Qt::DashLine));

    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, &AltitudeTuning::update_plot);
    timer_->start(200); // Update every 200ms
    altitude_tuning_right_layout->addWidget(altitude_plot_);

    ////////////////////////////////// Setup-Layout //////////////////////////////////
    altitude_tuning_layout->addLayout(altitude_tuning_left_layout_, 1);
    altitude_tuning_layout->addLayout(altitude_tuning_middle_layout_,1);
    altitude_tuning_layout->addLayout(altitude_tuning_right_layout,2);

    altitude_setpoint_value_ = 2.0;
    altitude_setpoint_->setText(QString::number(altitude_setpoint_value_));

    // Set Layout
    this->setLayout(altitude_tuning_layout);
}

AltitudeTuning::~AltitudeTuning() {
}

void AltitudeTuning::turn_on() {

    altitude_hold_on_ = !altitude_hold_on_;
    if (altitude_hold_on_) {
        send_udp_msg("$ALTITUDE_HOLD,1");
        altitude_setpoint_->setText(QString::number(altitude_setpoint_value_));
        send_udp_msg("$ALTITUDE_SETPOINT," + QString::number(altitude_setpoint_value_));
    } else {
        send_udp_msg("$ALTITUDE_HOLD,0");
    }

}

void AltitudeTuning::increase_setpoint() {
    
    if (!altitude_hold_on_) {
        return;
    }

    altitude_setpoint_value_ += 0.1;
    if (altitude_setpoint_value_ > 10.0) {
        altitude_setpoint_value_ = 10.0;
    }
    else if (altitude_setpoint_value_ < 0.5) {
        altitude_setpoint_value_ = 0.5;
    }

    altitude_setpoint_->setText(QString::number(altitude_setpoint_value_));
    send_udp_msg("$ALTITUDE_SETPOINT," + QString::number(altitude_setpoint_value_));

}   

void AltitudeTuning::decrease_setpoint() {

    if (!altitude_hold_on_) {
        return;
    }

    altitude_setpoint_value_ -= 0.1;
    if (altitude_setpoint_value_ > 10.0) {
        altitude_setpoint_value_ = 10.0;
    }
    else if (altitude_setpoint_value_ < 0.5) {
        altitude_setpoint_value_ = 0.5;
    }

    altitude_setpoint_->setText(QString::number(altitude_setpoint_value_));
    send_udp_msg("$ALTITUDE_SETPOINT," + QString::number(altitude_setpoint_value_));

}

void AltitudeTuning::unlock_parameters() {

    unlock_parameters_ = !unlock_parameters_;

    if (unlock_parameters_) {
        kp_label_->setStyleSheet("font-weight: bold; font-size: 20px; color: black;");
        ki_label_->setStyleSheet("font-weight: bold; font-size: 20px; color: black;");
        kd_label_->setStyleSheet("font-weight: bold; font-size: 20px; color: black;");
        constant_downforce_label_->setStyleSheet("font-weight: bold; font-size: 20px; color: black;");
        altitude_kp_input_->setDisabled(false);
        altitude_ki_input_->setDisabled(false);
        altitude_kd_input_->setDisabled(false);
        constant_downforce_input_->setDisabled(false);

    } else {       
        kp_label_->setStyleSheet("font-weight: bold; font-size: 20px; color: gray;");
        ki_label_->setStyleSheet("font-weight: bold; font-size: 20px; color: gray;");
        kd_label_->setStyleSheet("font-weight: bold; font-size: 20px; color: gray;");
        constant_downforce_label_->setStyleSheet("font-weight: bold; font-size: 20px; color: gray;");
        altitude_kp_input_->setDisabled(true);
        altitude_ki_input_->setDisabled(true);
        altitude_kd_input_->setDisabled(true);
        constant_downforce_input_->setDisabled(true);
    }

}

void AltitudeTuning::update_plot() {

    if (altitude_timestamps_.empty()) {
        return;
    }

    // Append altitude to the plot
    QVector<double> xAltitude, yAltitude;
    if (!altitude_timestamps_.empty()) {
        double relativeStartTime = altitude_timestamps_.front();
        for (size_t i = 0; i < altitude_timestamps_.size(); ++i) {
            xAltitude.append(altitude_timestamps_[i] - relativeStartTime);
            yAltitude.append(altitude_values_[i]);
        }
    }

    altitude_plot_->graph(0)->setData(xAltitude, yAltitude);

    // Dynamically adjust altitude y-axis range
    if (!altitude_values_.empty()) {
        double minAltitude = *std::min_element(altitude_values_.begin(), altitude_values_.end());
        double maxAltitude = *std::max_element(altitude_values_.begin(), altitude_values_.end());
        double altitudePadding = (maxAltitude - minAltitude) * 0.1; // 10% padding
        if (altitudePadding == 0) altitudePadding = 1.0; // Ensure non-zero padding for constant values
        altitude_plot_->axisRect()->axis(QCPAxis::atRight)->setRange(minAltitude - altitudePadding, maxAltitude + altitudePadding);
    }

    // If altitude hold is on
    if (altitude_hold_on_) {
        QVector<double> xSetpoint, ySetpoint;

        // Get the current X-axis range
        double xMin = altitude_plot_->xAxis->range().lower;
        double xMax = altitude_plot_->xAxis->range().upper;

        // Create a straight horizontal line at setpoint value
        xSetpoint.append(xMin);
        ySetpoint.append(altitude_setpoint_value_);

        xSetpoint.append(xMax);
        ySetpoint.append(altitude_setpoint_value_);

        altitude_plot_->graph(1)->setData(xSetpoint, ySetpoint);
    } else {
        // Clear the setpoint line if altitude hold is off
        altitude_plot_->graph(1)->setData(QVector<double>(), QVector<double>());
    }

    altitude_plot_->replot();

}

double AltitudeTuning::get_current_timestamp() {
    auto now = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    return duration.count() / 1000.0;
}

void AltitudeTuning::update_altitude(double altitude) {

    // Update altitude
    current_altitude_value_ = altitude;

    // Update timestamp
    double timestamp = get_current_timestamp();

    // Append to altitude values
    altitude_values_.push_back(current_altitude_value_);
    altitude_timestamps_.push_back(timestamp);

    // Remove old values
    while (altitude_timestamps_.front() < timestamp - window_duration_) {
        altitude_values_.pop_front();
        altitude_timestamps_.pop_front();
    }

}

void AltitudeTuning::send_udp_msg(const QString &msg) {

    // Send UDP message
    QHostAddress target_address = QHostAddress("127.0.0.1");
    quint16 target_port = 9100;
    udp_socket_->writeDatagram(msg.toUtf8(), target_address, target_port);

}

void AltitudeTuning::update_parameters() {

    if (!unlock_parameters_) {
        return;
    }

    // Send updated parameters to control system
    QString kp = altitude_kp_input_->text();
    QString ki = altitude_ki_input_->text();
    QString kd = altitude_kd_input_->text();
    QString downforce = constant_downforce_input_->text();
    send_udp_msg("$ALTITUDE_PARAMETERS," + kp + "," + ki + "," + kd + "," + downforce);
}

void AltitudeTuning::store_parameters() {

    if (!unlock_parameters_) {
        return;
    }

    // Store parameters to file
    QString kp = altitude_kp_input_->text();
    QString ki = altitude_ki_input_->text();
    QString kd = altitude_kd_input_->text();
    QString downforce = constant_downforce_input_->text();
    QString parameters = kp + "," + ki + "," + kd + "," + downforce;
    QFile file("parameters.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << parameters;
        file.close();
    }

}

void AltitudeTuning::incoming_messages() {

    while (udp_socket_receive_->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udp_socket_receive_->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        udp_socket_receive_->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        QString message = QString::fromUtf8(datagram);

        if (message.startsWith("$ALTITUDE,")) {
            QStringList message_parts = message.split(",");
            if (message_parts.size() == 2) {
                double altitude = message_parts[1].toDouble();
                update_altitude(altitude);
                if (!altitude_hold_on_) {
                    altitude_setpoint_value_ = altitude;
                    altitude_setpoint_->setText(QString::number(altitude_setpoint_value_));
                }
            }
        }
        if (message.startsWith("$ALTITUDE_VALID,")) {
            QStringList message_parts = message.split(",");
            if (message_parts.size() == 2) {
                bool valid = message_parts[1].toInt();
                altitude_valid_ = valid;
                if (valid) {
                    altitude_valid_indicator_->setStyleSheet("background-color: green; border-radius: 90px; border: 1px solid black;");
                } else {
                    altitude_valid_indicator_->setStyleSheet("background-color: red; border-radius: 90px; border: 1px solid black;");
                }
            }
        }
    }

}
