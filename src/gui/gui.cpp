#include "gui/gui.hpp"

GUI::GUI(QWidget *parent) : QWidget(parent) {

    setWindowTitle("MINERVA II CONTROL SYSTEM");
    setFixedSize(1920, 1080);
    // Main Layout
    QHBoxLayout *main_layout= new QHBoxLayout(this);
    this->setLayout(main_layout);

    // Layouts
    left_layout_ = new QVBoxLayout;
    right_layout_ = new QVBoxLayout;

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

    // Terminal widget
    terminal_ = new QTextEdit(this);
    terminal_->setReadOnly(true); // Make it read-only
    terminal_->setStyleSheet("background-color: black; color: white; font-family: monospace; border: 5px solid gray; border-radius: 5px;");
    write_to_terminal(QString("Welcome to the MINERVA II Control System"));

    // Indicator light widget
    status_light_widget = new QWidget(this);
    setup_status_lights();

    // Add widgets to layouts
    left_layout_->addWidget(buttons_widget_);  // Left: Buttons
    left_layout_->addWidget(compass_widget_, 16);  // Left: Compass
    left_layout_->addWidget(thrusters_widget_, 2); // Right: Thruster Indicators
    right_layout_->addWidget(title);
    right_layout_->addWidget(terminal_, 3);
    right_layout_->addWidget(status_light_widget,1); 
    main_layout->addLayout(left_layout_, 1);  // Left: Buttons
    main_layout->addLayout(right_layout_, 3); // Right: Status + Terminal

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
    } 
    // Sends message to control PC that the system should stop 
    else {
        start_button->setStyleSheet("background-color: green; color: white;");
        start_button->setText("RUNNING");
        start_button->setDown(true);
        config_button->setDisabled(true);
        sniffer_button->setDisabled(true);

        write_to_terminal(QString("Control System started"));
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
    terminal_->append(msg);
    terminal_->moveCursor(QTextCursor::End);
}



void GUI::setup_status_lights() {
    // Main layout for the two 2x2 grids
    QHBoxLayout *mainGridLayout = new QHBoxLayout(status_light_widget);

    // Create two widgets for the 2x2 grids
    QWidget *gridWidget1 = new QWidget(status_light_widget);
    QWidget *gridWidget2 = new QWidget(status_light_widget);

    // Setup each 2x2 grid with vertical lights
    setupSingleLightGrid(gridWidget1, "Control Modes", "Waypoint Control", "Dynamic Positioning", "Altitude Hold", "Depth Hold",
                         "On", "Available", "Unavailable", "blue", "green", "red");
    setupSingleLightGrid(gridWidget2, "Sensor Status", "DVL", "IMU", "Depth Sensor", "USBL",
                         "Available", "Degraded", "Unavailable", "green", "yellow", "red");

    // Add the two grids to the main layout
    mainGridLayout->addWidget(gridWidget1);
    mainGridLayout->addWidget(gridWidget2);

    status_light_widget->setLayout(mainGridLayout);
}

void GUI::setupSingleLightGrid(QWidget *parent, const QString &groupName, const QString& status1, const QString& status2, const QString& status3, const QString& status4,
                               const QString& indicator1, const QString& indicator2, const QString& indicator3, 
                               const QString& light_color1, const QString& light_color2, const QString& light_color3) {
    // Outer layout for this grid
    QVBoxLayout *outerLayout = new QVBoxLayout(parent);

    // Title for the group
    QLabel *groupLabel = new QLabel(groupName, parent);
    groupLabel->setAlignment(Qt::AlignCenter);
    groupLabel->setStyleSheet("font-weight: bold;");
    outerLayout->addWidget(groupLabel);

    // Grid layout for the 2x2 status lights
    QGridLayout *gridLayout = new QGridLayout;
    QStringList statuses = {status1, status2, status3, status4};

    for (int i = 0; i < 4; ++i) {
        QLabel *label = new QLabel(statuses[i], parent);
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet("font-weight: bold;");

        QLabel *light = new QLabel(parent);
        light->setFixedSize(40, 40); // Status light size
        light->setStyleSheet("background-color: red; border-radius: 20px; border: 1px solid black;");

        gridLayout->addWidget(label, i / 2 * 2, i % 2, Qt::AlignCenter);
        gridLayout->addWidget(light, i / 2 * 2 + 1, i % 2, Qt::AlignCenter);
    }

    outerLayout->addLayout(gridLayout);

    // Vertical layout for color indicators
    QVBoxLayout *colorIndicatorLayout = new QVBoxLayout;

    QStringList colorDescriptions = {indicator1, indicator2, indicator3};
    QStringList colors = {light_color1, light_color2, light_color3};

    for (int i = 0; i < 3; ++i) {
        QHBoxLayout *indicatorLayout = new QHBoxLayout;

        QLabel *colorLight = new QLabel(parent);
        colorLight->setFixedSize(20, 20); // Smaller light size
        colorLight->setStyleSheet(QString("background-color: %1; border-radius: 10px; border: 1px solid black;")
                                      .arg(colors[i]));

        QLabel *colorLabel = new QLabel(colorDescriptions[i], parent);
        colorLabel->setStyleSheet("font-weight: bold;");

        indicatorLayout->addWidget(colorLight);
        indicatorLayout->addWidget(colorLabel);

        colorIndicatorLayout->addLayout(indicatorLayout);
    }

    outerLayout->addLayout(colorIndicatorLayout);
}
