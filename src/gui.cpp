#include "gui.hpp"

GUI::GUI(QWidget *parent) : QWidget(parent) {

    setWindowTitle("MINERVA II CONTROL SYSTEM");
    setFixedSize(1920, 1080);
    // Main Layout
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    this->setLayout(mainLayout);
    left_layout = new QVBoxLayout;


    // Button layout
    button_layout = new QVBoxLayout;
    start_button = new QPushButton("START CONTROL SYSTEM");
    log_button = new QPushButton("START LOGGING");
    config_button = new QPushButton("CONFIGURE");
    sniffer_button = new QPushButton("UDP SNIFFER");
    synch_button = new QPushButton("SYNCHRONIZE");
    help_button = new QPushButton("HELP");
    exit_button = new QPushButton("EXIT");
    config_button->setCheckable(true);
    start_button->setCheckable(true);
    sniffer_button->setCheckable(true);
    button_layout->addWidget(start_button);
    button_layout->addWidget(log_button);
    button_layout->addWidget(config_button);
    button_layout->addWidget(sniffer_button);
    button_layout->addWidget(synch_button);
    button_layout->addWidget(help_button);
    button_layout->addWidget(exit_button);
    button_layout->addStretch();

    // Thruster Layout
    thruster_indicator_layout = new QGridLayout;
    QProgressBar *bars[7];
    QLabel *labels[7];
    QStringList labelsText = {"T1", "T2", "T3", "T4", "T5", "T6", "T7"};
    
    for (int i = 0; i < 7; ++i) {
        // Create progress bar
        bars[i] = new QProgressBar;
        bars[i]->setOrientation(Qt::Vertical);
        bars[i]->setRange(0, 100);
        bars[i]->setValue(50); // Initial value

        // Create label
        labels[i] = new QLabel(labelsText[i]);
        labels[i]->setAlignment(Qt::AlignCenter);
        labels[i]->setStyleSheet("font-weight: bold;");

        // Add to layout
        int row = (i < 3) ? 0 : 2; // Top row for first 3 bars, bottom row for next 4 bars
        int col = (i < 3) ? 1 + (i*2) : (i - 3) * 2;
        thruster_indicator_layout->addWidget(bars[i], row, col);  // Add bar
        thruster_indicator_layout->addWidget(labels[i], row+1, col);  // Add label below the bar
    }

    // Compass Layout
    compass = new CompassWidget;
    compass->setFixedSize(500, 500);

    // Status indicators
    status_layout = new QVBoxLayout;
    QLabel *statusLabel = new QLabel("Minerva II Control System", this);
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setStyleSheet("font-weight: bold; font-size: 20px;");
    status_layout->addWidget(statusLabel);

    // Declare log terminal
    terminal = new QTextEdit(this);
    terminal->setReadOnly(true); // Make it read-only
    terminal->setStyleSheet("background-color: black; color: white; font-family: monospace; border: 5px solid gray; border-radius: 5px;");
    write_to_terminal(QString("Welcome to the MINERVA II Control System"));
    status_layout->addWidget(terminal,3);

    // Control system indicators
    status_light_widget = new QWidget(this);
    setup_status_lights();
    status_layout->addWidget(status_light_widget,1); 

    // Add layouts to main layout
    left_layout->addLayout(button_layout);  // Left: Buttons
    left_layout->addWidget(compass, 16);  // Left: Compass
    left_layout->addLayout(thruster_indicator_layout, 2); // Right: Thruster Indicators
    mainLayout->addLayout(left_layout, 1);  // Left: Buttons
    mainLayout->addLayout(status_layout, 3); // Right: Status + Terminal

    // Connect signals and slots
    connect(start_button, &QPushButton::clicked, this, &GUI::on_start_button);
    connect(config_button, &QPushButton::clicked, this, &GUI::on_config_button);
    connect(exit_button, &QPushButton::clicked, this, &GUI::on_exit_button);
    connect(sniffer_button, &QPushButton::clicked, this, &GUI::on_sniffer_button);

    // Show widgets
    this->show();
}

GUI::~GUI() {
}

void GUI::on_start_button() {
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

    // Open configuration dialog
    ConfigDialog *config_dialog = new ConfigDialog(ip_address_, control_system_port_, system_status_port_, mission_status_port_, this);
    connect(config_dialog, &ConfigDialog::configUpdated, this, &GUI::update_config);
    config_dialog->exec();
    config_button->setChecked(false);
}

// UDP Sniffer button pressed
void GUI::on_sniffer_button() {
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
    terminal->append(msg);
    terminal->moveCursor(QTextCursor::End);
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

















////////////////////////////////////////// CONFIGURATION DIALOG //////////////////////////////////////////

// Constructor
ConfigDialog::ConfigDialog(const QString &initialIP, int initialPort1, int initialPort2, int initialPort3, QWidget *parent)
    : QDialog(parent) {
    setWindowTitle("Configuration");
    setFixedSize(400, 300);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // IPv4 Address Field
    QLabel *ip_label = new QLabel("IP Address - Control PC:", this);
    ip_address = new QLineEdit(this);
    ip_address->setText(initialIP);

    // Port Fields
    QLabel *port1_label = new QLabel("Port 1 - Control System Communication:", this);
    port1 = new QLineEdit(this);
    port1->setText(QString::number(initialPort1));

    QLabel *port2_label = new QLabel("Port 2 - Control System Status:", this);
    port2 = new QLineEdit(this);
    port2->setText(QString::number(initialPort2));

    QLabel *port3_label = new QLabel("Port 3 - Mission Status:", this);
    port3 = new QLineEdit(this);
    port3->setText(QString::number(initialPort3));

    QIntValidator *portValidator = new QIntValidator(1000, 65535, this);
    port1->setValidator(portValidator);
    port2->setValidator(portValidator);
    port3->setValidator(portValidator);

    // Add fields to layout
    mainLayout->addWidget(ip_label);
    mainLayout->addWidget(ip_address);
    mainLayout->addWidget(port1_label);
    mainLayout->addWidget(port1);
    mainLayout->addWidget(port2_label);
    mainLayout->addWidget(port2);
    mainLayout->addWidget(port3_label);
    mainLayout->addWidget(port3);

    // Error Label
    error_label = new QLabel(this);
    error_label->setStyleSheet("color: red;");
    mainLayout->addWidget(error_label);

    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    QPushButton *confirmButton = new QPushButton("Confirm", this);
    QPushButton *cancelButton = new QPushButton("Cancel", this);

    buttonLayout->addWidget(confirmButton);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);

    // Connect buttons
    connect(confirmButton, &QPushButton::clicked, this, &ConfigDialog::onConfirm);
    connect(cancelButton, &QPushButton::clicked, this, &ConfigDialog::reject);
}

void ConfigDialog::onConfirm() {

    // Checking that input is accepted before closing dialog
    bool valid = true;
    ip_address->setStyleSheet("");
    port1->setStyleSheet("");
    port2->setStyleSheet("");
    port3->setStyleSheet("");
    error_label->clear();

    // Validate IP Address
    QHostAddress address;
    if (!address.setAddress(ip_address->text()) || address.protocol() != QAbstractSocket::IPv4Protocol) {

        ip_address->setStyleSheet("border: 1px solid red;");
        error_label->setText("Invalid IP address. Please enter a valid IPv4 address.");
        valid = false;
    }

    // Validate Port 1
    if (port1->text().isEmpty() || port1->text().toInt() < 1000 || port1->text().toInt() > 65535) {
        port1->setStyleSheet("border: 1px solid red;");
        error_label->setText("Port 1 must be an integer between 1001 and 65535.");
        valid = false;
    }

    // Validate Port 2
    if (port2->text().isEmpty() || port2->text().toInt() < 1000 || port2->text().toInt() > 65535) {
        port2->setStyleSheet("border: 1px solid red;");
        error_label->setText("Port 2 must be an integer between 1001 and 65535.");
        valid = false;
    }

    // Validate Port 3
    if (port3->text().isEmpty() || port3->text().toInt() < 1000 || port3->text().toInt() > 65535) {
        port3->setStyleSheet("border: 1px solid red;");
        error_label->setText("Port 3 must be an integer between 1001 and 65535.");
        valid = false;
    }

    // If all inputs are valid, accept the dialog
    if (valid) {
        emit configUpdated(
            ip_address->text(),
            port1->text().toInt(),
            port2->text().toInt(),
            port3->text().toInt()
        );
        accept();
    }
}

