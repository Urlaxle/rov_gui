#include "gui/gui.hpp"

GUI::GUI(QWidget *parent) : QWidget(parent) {

    setWindowTitle("MINERVA II CONTROL SYSTEM");
    setFixedSize(1920, 1080);
    setStyleSheet("background-color: white");

    // main layout
    QVBoxLayout *main_layout = new QVBoxLayout(this);
    this->setLayout(main_layout);

    // We want tabs
    QTabWidget *tab_widget = new QTabWidget();

    ////////////////////////////////////////////////////////////// TAB 1 ///////////////////////////////////////////////////////////
    // TAB1 widget
    QWidget *tab1 = new QWidget();
    //tab1->setStyleSheet("background-color: white");

    // Main Layout
    QHBoxLayout *tab1_layout= new QHBoxLayout(this);

    // Layouts
    left_layout_ = new QVBoxLayout;
    right_layout_ = new QVBoxLayout;
    stop_layout_ = new QVBoxLayout;

    // Buttons widget
    buttons_widget_ = new buttons(this);
    connect(buttons_widget_, &buttons::start_button_pressed, this, &GUI::on_start_button);
    connect(buttons_widget_, &buttons::config_button_pressed, this, &GUI::on_config_button);
    connect(buttons_widget_, &buttons::sniffer_button_pressed, this, &GUI::on_sniffer_button);
    connect(buttons_widget_, &buttons::exit_button_pressed, this, &GUI::on_exit_button);

    // Compass widget
    compass_widget_ = new compass;
    compass_widget_->setFixedSize(500, 500);

    // Thruster Widget
    thrusters_widget_ = new thrusters(this);

    // Title widget
    QLabel *title = new QLabel("Minerva II Control System", this);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-weight: bold; font-size: 20px;");

    // Indicator light widget
    status_light_widget_ = new indicators(this);

    // Stop button widget
    stop_button_ = new QPushButton("EMERGENCY\n STOP", this);
    stop_button_->setCheckable(true);
    stop_button_->setStyleSheet("background-color: darkred; color: white; font-size: 20px; ");
    stop_button_->setFixedSize(200, 200);
    connect(stop_button_, &QPushButton::clicked, this, &GUI::on_stop_button);

    // Waypoint list widget
    waypoint_list_widget_ = new waypoint_list(this);

    // Display numbers
    number_display_widget_ = new number_display(this);

    // Depth and Altitude Plot
    depth_plot_ = new DepthPlotWidget(60.0);


    // Add widgets to layouts
    left_layout_->addWidget(buttons_widget_);  // Left: Buttons
    left_layout_->addWidget(compass_widget_, 16);  // Left: Compass
    //left_layout_->addWidget(depth_plot_, 1);  // Left: Numbers
    left_layout_->addWidget(thrusters_widget_, 1);  // Left: Numbers
    right_layout_->addWidget(title);
    right_layout_->addWidget(status_light_widget_,2); 
    right_layout_->addWidget(depth_plot_, 3); // Right: Status + Terminal
    //right_layout_->addWidget(thrusters_widget_, 2); // Right: Status + Terminal
    stop_layout_->addWidget(stop_button_, 1);
    stop_layout_->addWidget(waypoint_list_widget_, 3);
    stop_layout_->setAlignment(stop_button_, Qt::AlignCenter);
    tab1_layout->addLayout(left_layout_, 1);  // Left: Buttons
    tab1_layout->addLayout(right_layout_, 3); // Right: Status + Terminal
    tab1_layout->addLayout(stop_layout_, 1);  // Stop Button

    tab1->setLayout(tab1_layout);

    ////////////////////////////////////////////////////////////// TAB 2 - WAYPOINT CONTROLLER ///////////////////////////////////////////////////////////
    // TAB2 widget
    QWidget *tab2 = new QWidget();









    ////////////////////////////////////////////////////////////// TAB 3 - DP CONTROLLER /////////////////////////////////////////////////////////////////
    QWidget *tab3 = new QWidget();





    ////////////////////////////////////////////////////////////// TAB 4 - Parameter Tuning ////////////////////////////////////////////////////////////
    QWidget *tab4 = new QWidget();

    QHBoxLayout *tab4_layout= new QHBoxLayout(this);

    // PID GAINS
    PID_GUI *pid_widget = new PID_GUI(this);

    tab4_layout->addWidget(pid_widget);

    tab4->setLayout(tab4_layout);


    ////////////////////////////////////////////////////////////// TAB 5 - System Log ///////////////////////////////////////////////////////////
    QWidget *tab5 = new QWidget();
    QVBoxLayout *tab5_layout = new QVBoxLayout(this);
    // Terminal widget
    terminal_ = new QTextEdit(this);
    terminal_->setReadOnly(true); // Make it read-only
    terminal_->setStyleSheet("background-color: black; color: white; font-family: monospace; border: 5px solid gray; border-radius: 5px;");
    write_to_terminal(QString("Welcome to the MINERVA II Control System"));
    tab5_layout->addWidget(terminal_);
    tab5->setLayout(tab5_layout);

    ////////////////////////////////////////////////////////////// TAB 6 - Altitude Tuning ///////////////////////////////////////////////////////////
    QWidget *tab6 = new QWidget();
    QVBoxLayout *tab6_layout = new QVBoxLayout(this);
    altitude_tuning_widget_ = new AltitudeTuning(this);
    tab6_layout->addWidget(altitude_tuning_widget_);
    tab6->setLayout(tab6_layout);

    ////////////////////////////////////////////////////////////// Setup GUI ///////////////////////////////////////////////////////////

    // Add tabs
    tab_widget->addTab(tab1, "Control System");
    tab_widget->addTab(tab2, "Waypoint Controller");
    tab_widget->addTab(tab3, "DP Controller");
    tab_widget->addTab(tab4, "Parameter Tuning");
    tab_widget->addTab(tab5, "System Log");
    tab_widget->addTab(tab6, "Altitude Tuning");
    main_layout->addWidget(tab_widget);

    // Setup socket
    control_socket_ = new QUdpSocket(this);

    // Show widgets
    this->show();
}

GUI::~GUI() {
}

void GUI::on_start_button() {

    // Fetch buttons
    QPushButton *start_button = buttons_widget_->get_start_button();
    QPushButton *config_button = buttons_widget_->get_configuration_button();
    QPushButton *sniffer_button = buttons_widget_->get_sniffer_button();

    // Send message to control PC that the system should start
    if (start_button->text() == "RUNNING") {
        start_button->setText("START");
        start_button->setStyleSheet("");
        start_button->setDown(false);
        config_button->setEnabled(true);
        sniffer_button->setEnabled(true);
        write_to_terminal(QString("Control System stopped"));
        toogle_listening();
    } 
    // Sends message to control PC that the system should stop 
    else {
        start_button->setStyleSheet("background-color: green; color: white;");
        start_button->setText("RUNNING");
        start_button->setDown(true);
        config_button->setDisabled(true);
        sniffer_button->setDisabled(true);

        write_to_terminal(QString("Control System started"));
        toogle_listening();
    }
}

// Configure button pressed
void GUI::on_config_button() {

    // Fetch buttons
    QPushButton *config_button = buttons_widget_->get_configuration_button();

    // Open configuration dialog
    configuration *config_dialog = new configuration(ip_address_, control_system_port_, system_status_port_, mission_status_port_, this);
    connect(config_dialog, &configuration::update_configuration, this, &GUI::update_config);
    config_dialog->exec();
    config_button->setChecked(false);
}

// UDP Sniffer button pressed
void GUI::on_sniffer_button() {

    // Fetch buttons
    QPushButton *sniffer_button = buttons_widget_->get_sniffer_button();

    // Open sniffer dialog
    udp_sniffer *sniffer = new udp_sniffer(this);
    sniffer->exec();
    sniffer_button->setChecked(false);
}

// Exit button pressed
void GUI::on_exit_button() {
    // Cleanup

    // Exit program
    QCoreApplication::quit();
}

void GUI::update_config(const QString &ip, int port1, int port2, int port3) {
    // Fetch new parameters
    ip_address_ = ip;
    control_system_port_ = port1;
    system_status_port_ = port2;
    mission_status_port_ = port3;

    // Write current parameters to terminal
    QString log_msg = QString("Configuration updated: IP = %1, Port1 = %2, Port2 = %3, Port3 = %4")
                             .arg(ip)
                             .arg(port1)
                             .arg(port2)
                             .arg(port3);
    write_to_terminal(log_msg);
}

// Writes message to terminal and scrolls to bottom
void GUI::write_to_terminal(const QString &msg) {
    QString timeStamp = QTime::currentTime().toString("hh:mm:ss");
    QString formatted_msg = QString("[%1] %2").arg(timeStamp).arg(msg);
    terminal_->append(formatted_msg);
    terminal_->moveCursor(QTextCursor::End);
}

// STOP button pressed
void GUI::on_stop_button() {

    if (stop_button_->text() == "EMERGENCY\n STOP") {
        stop_button_->setText("SYSTEM\n STOPPED");
        stop_button_->setStyleSheet("background-color: darkred; color: black; font-size: 20px;");
        stop_button_->setCheckable(true);
        write_to_terminal(QString("Emergency Stop Initiated"));
    }

}

// UDP Parser
void GUI::toogle_listening() {

    // If we are not listening, start to listen
    if (!control_is_listening_) {

        // Binds port and starts to listen
        if (control_socket_->bind(QHostAddress::Any, control_port_)) {
            control_is_listening_ = true;

            // Capturing incoming messages
            connect(control_socket_, &QUdpSocket::readyRead, this, [this](){
                while (control_socket_->hasPendingDatagrams()) {
                    QByteArray datagram;
                    datagram.resize(control_socket_->pendingDatagramSize());
                    QHostAddress sender;
                    quint16 sender_port;
                    control_socket_->readDatagram(datagram.data(), datagram.size(), &sender, &sender_port);

                    // Split the message into parts
                    std::string message = datagram.toStdString();
                    size_t start = 0;
                    size_t end;
                    std::vector<std::string> data; // Use std::string for consistency
                    while ((end = message.find(",", start)) != std::string::npos) {
                        data.push_back(message.substr(start, end - start));
                        start = end + 1;
                    }
                    data.push_back(message.substr(start));

                    // Take action based on arrived message
                    if (data.at(0) == "$STATUS") { // Format $STATUS,DVL,IMU,DEPTH,USBL,WAYPOINT,DYNAMIC,ALTITUDE,DEPTH_HOLD
                        // Update Indicators
                        status_light_widget_->set_dvl_status(std::stoi(data.at(1)));
                        status_light_widget_->set_imu_status(std::stoi(data.at(2)));
                        status_light_widget_->set_depth_status(std::stoi(data.at(3)));
                        status_light_widget_->set_usbl_status(std::stoi(data.at(4)));
                        status_light_widget_->set_waypoint_status(std::stoi(data.at(5)));
                        status_light_widget_->set_dynamic_status(std::stoi(data.at(6)));
                        status_light_widget_->set_altitude_status(std::stoi(data.at(7)));
                        status_light_widget_->set_depth_hold_status(std::stoi(data.at(8)));
                    }

                    // Update thruster values
                    if (data.at(0) == "$THR") {
                        // Update thruster values
                        thrusters_widget_->set_thruster_value(0, std::stoi(data.at(1)));
                        thrusters_widget_->set_thruster_value(1, std::stoi(data.at(2)));
                        thrusters_widget_->set_thruster_value(2, std::stoi(data.at(3)));
                        thrusters_widget_->set_thruster_value(3, std::stoi(data.at(4)));
                        thrusters_widget_->set_thruster_value(4, std::stoi(data.at(5)));
                        thrusters_widget_->set_thruster_value(5, std::stoi(data.at(6)));
                        thrusters_widget_->set_thruster_value(6, std::stoi(data.at(7)));
                    }

                    // Update Compass Rose
                    if (data.at(0) == "$COMPASS") {
                        compass_widget_->set_heading(std::stod(data.at(1)), std::stod(data.at(2)));
                    }

                    // Update depth and altitude
                    if (data.at(0) == "$DEPTH") {
                        depth_plot_->addDepthData(std::stod(data.at(1)));
                        if (std::stod(data.at(2)) > 0 ) {
                            depth_plot_->setDepthHold(std::stod(data.at(2)));
                        } else {
                            depth_plot_->clearDepthHold();
                        }
                        depth_plot_->addAltitudeData(std::stod(data.at(3)));
                        if (std::stod(data.at(4)) > 0 ) {
                            depth_plot_->setAltitudeHold(std::stod(data.at(4)));
                        } else {
                            depth_plot_->clearAltitudeHold();
                        }
                    }

                    if (data.at(0) == "$ALTITUDE") {
                        altitude_tuning_widget_->update_altitude(std::stod(data.at(1)));
                    }
                }

            });
        }
    } else {
        // Stop listening
        control_socket_->close();
        control_is_listening_ = false;
    }

}

void GUI::close() {
    control_socket_->close();
}