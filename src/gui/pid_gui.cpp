#include "gui/pid_gui.hpp"
#include <iostream>

PID_GUI::PID_GUI(QWidget *parent) 
: QWidget(parent) {

    // Lets see whats going on
    QVBoxLayout* main_layout = new QVBoxLayout;
    QLabel* title = new QLabel("Controller Gains", this);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-weight: bold; font-size: 20px;");

    // PARAMETER GAINS //////////////////////////////////////////////////////////////

    udp_socket_ = new QUdpSocket(this);

    QVBoxLayout* gains_layout = new QVBoxLayout;

    // Surge gains
    surge_label_ = new QLabel("Surge", this);
    surge_label_->setAlignment(Qt::AlignCenter);
    surge_label_->setStyleSheet("font-weight: bold; font-size: 16px;");
    surge_label_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    surge_kp_label_ = new QLabel("KP", this);
    surge_kp_label_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    surge_kp_label_->setAlignment(Qt::AlignCenter);
    surge_kp_input_ = new QLineEdit(this);
    //surge_kp_input_->setValidator(new QDoubleValidator(0, 100, 2, this));
    surge_kp_input_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    surge_kp_input_->setAlignment(Qt::AlignCenter);

    surge_ki_label_ = new QLabel("KI", this);
    surge_ki_label_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    surge_ki_label_->setAlignment(Qt::AlignCenter);
    surge_ki_input_ = new QLineEdit(this);
    //surge_ki_input_->setValidator(new QDoubleValidator(0, 100, 2, this));
    surge_ki_input_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    surge_ki_input_->setAlignment(Qt::AlignCenter);

    surge_kd_label_ = new QLabel("KD", this);
    surge_kd_label_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    surge_kd_label_->setAlignment(Qt::AlignCenter);
    surge_kd_input_ = new QLineEdit(this);
    //surge_kd_input_->setValidator(new QDoubleValidator(0, 100, 2, this));   
    surge_kd_input_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    surge_kd_input_->setAlignment(Qt::AlignCenter);

    // Set up surge layout
    QVBoxLayout* surge_layout = new QVBoxLayout;
    surge_layout->addWidget(surge_label_);
    QHBoxLayout* surge_gains_layout = new QHBoxLayout;
    QHBoxLayout* surge_label_layout = new QHBoxLayout;
    surge_label_layout->addWidget(surge_kp_label_);
    surge_gains_layout->addWidget(surge_kp_input_);
    surge_label_layout->addWidget(surge_ki_label_);
    surge_gains_layout->addWidget(surge_ki_input_);
    surge_label_layout->addWidget(surge_kd_label_);
    surge_gains_layout->addWidget(surge_kd_input_);
    surge_layout->addLayout(surge_label_layout);
    surge_layout->addLayout(surge_gains_layout);

    // Add to main layout
    // Sway gains
    sway_label_ = new QLabel("Sway", this);
    sway_label_->setAlignment(Qt::AlignCenter);
    sway_label_->setStyleSheet("font-weight: bold; font-size: 16px;");
    sway_label_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    sway_kp_label_ = new QLabel("KO", this);
    sway_kp_label_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sway_kp_label_->setAlignment(Qt::AlignCenter);
    sway_kp_input_ = new QLineEdit(this);
    //sway_kp_input_->setValidator(new QDoubleValidator(0, 100, 2, this));
    sway_kp_input_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sway_kp_input_->setAlignment(Qt::AlignCenter);

    sway_ki_label_ = new QLabel("KI", this);
    sway_ki_label_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sway_ki_label_->setAlignment(Qt::AlignCenter);
    sway_ki_input_ = new QLineEdit(this);
    //sway_ki_input_->setValidator(new QDoubleValidator(0, 100, 2, this));
    sway_ki_input_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sway_ki_input_->setAlignment(Qt::AlignCenter);

    sway_kd_label_ = new QLabel("KD", this);
    sway_kd_label_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sway_kd_label_->setAlignment(Qt::AlignCenter);
    sway_kd_input_ = new QLineEdit(this);
    //sway_kd_input_->setValidator(new QDoubleValidator(0, 100, 2, this));
    sway_kd_input_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sway_kd_input_->setAlignment(Qt::AlignCenter);

    // Set up sway layout
    QVBoxLayout* sway_layout = new QVBoxLayout;
    sway_layout->addWidget(sway_label_);
    QHBoxLayout* sway_gains_layout = new QHBoxLayout;
    QHBoxLayout* sway_label_layout = new QHBoxLayout;
    sway_label_layout->addWidget(sway_kp_label_);
    sway_gains_layout->addWidget(sway_kp_input_);
    sway_label_layout->addWidget(sway_ki_label_);
    sway_gains_layout->addWidget(sway_ki_input_);
    sway_label_layout->addWidget(sway_kd_label_);
    sway_gains_layout->addWidget(sway_kd_input_);
    sway_layout->addLayout(sway_label_layout);
    sway_layout->addLayout(sway_gains_layout);

    // Heave gains
    heave_label_ = new QLabel("Heave", this);
    heave_label_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    heave_label_->setAlignment(Qt::AlignCenter);
    heave_label_->setAlignment(Qt::AlignCenter);
    heave_label_->setStyleSheet("font-weight: bold; font-size: 16px;");
    heave_label_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    heave_kp_label_ = new QLabel("KP", this);
    heave_kp_label_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    heave_kp_label_->setAlignment(Qt::AlignCenter);
    heave_kp_input_ = new QLineEdit(this);
    //heave_kp_input_->setValidator(new QDoubleValidator(0, 100, 2, this));
    heave_kp_input_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    heave_kp_input_->setAlignment(Qt::AlignCenter);

    heave_ki_label_ = new QLabel("KI", this);
    heave_ki_label_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    heave_ki_label_->setAlignment(Qt::AlignCenter);
    heave_ki_input_ = new QLineEdit(this);
    //heave_ki_input_->setValidator(new QDoubleValidator(0, 100, 2, this));
    heave_ki_input_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    heave_ki_input_->setAlignment(Qt::AlignCenter);

    heave_kd_label_ = new QLabel("KD", this);
    heave_kd_label_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    heave_kd_label_->setAlignment(Qt::AlignCenter);
    heave_kd_input_ = new QLineEdit(this);
    //heave_kd_input_->setValidator(new QDoubleValidator(0, 100, 2, this));
    heave_kd_input_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    heave_kd_input_->setAlignment(Qt::AlignCenter);

    // Set up heave layout
    QVBoxLayout* heave_layout = new QVBoxLayout;
    heave_layout->addWidget(heave_label_);
    QHBoxLayout* heave_gains_layout = new QHBoxLayout;
    QHBoxLayout* heave_label_layout = new QHBoxLayout;
    heave_label_layout->addWidget(heave_kp_label_);
    heave_gains_layout->addWidget(heave_kp_input_);
    heave_label_layout->addWidget(heave_ki_label_);
    heave_gains_layout->addWidget(heave_ki_input_);
    heave_label_layout->addWidget(heave_kd_label_);
    heave_gains_layout->addWidget(heave_kd_input_);
    heave_layout->addLayout(heave_label_layout);
    heave_layout->addLayout(heave_gains_layout);

    // YAW gains
    yaw_label_ = new QLabel("Yaw", this);
    yaw_label_->setAlignment(Qt::AlignCenter);
    yaw_label_->setStyleSheet("font-weight: bold; font-size: 16px;");
    yaw_label_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    yaw_kp_label_ = new QLabel("KP", this);
    yaw_kp_label_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    yaw_kp_label_->setAlignment(Qt::AlignCenter);
    yaw_kp_input_ = new QLineEdit(this);
    //yaw_kp_input_->setValidator(new QDoubleValidator(0, 100, 2, this));
    yaw_kp_input_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    yaw_kp_input_->setAlignment(Qt::AlignCenter);

    yaw_ki_label_ = new QLabel("KI", this);
    yaw_ki_label_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    yaw_ki_label_->setAlignment(Qt::AlignCenter);
    yaw_ki_input_ = new QLineEdit(this);
    //yaw_ki_input_->setValidator(new QDoubleValidator(0, 100, 2, this));
    yaw_ki_input_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    yaw_ki_input_->setAlignment(Qt::AlignCenter);

    yaw_kd_label_ = new QLabel("KD", this);
    yaw_kd_label_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    yaw_kd_label_->setAlignment(Qt::AlignCenter);
    yaw_kd_input_ = new QLineEdit(this);
    //yaw_kd_input_->setValidator(new QDoubleValidator(0, 100, 2, this));
    yaw_kd_input_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    yaw_kd_input_->setAlignment(Qt::AlignCenter);

    // Set up yaw layout
    QVBoxLayout* yaw_layout = new QVBoxLayout;
    yaw_layout->addWidget(yaw_label_);
    QHBoxLayout* yaw_gains_layout = new QHBoxLayout;
    QHBoxLayout* yaw_label_layout = new QHBoxLayout;
    yaw_label_layout->addWidget(yaw_kp_label_);
    yaw_gains_layout->addWidget(yaw_kp_input_);
    yaw_label_layout->addWidget(yaw_ki_label_);
    yaw_gains_layout->addWidget(yaw_ki_input_);
    yaw_label_layout->addWidget(yaw_kd_label_);
    yaw_gains_layout->addWidget(yaw_kd_input_);
    yaw_layout->addLayout(yaw_label_layout);
    yaw_layout->addLayout(yaw_gains_layout);

    // Buttons
    send_button_ = new QPushButton("Set", this);
    send_button_->setStyleSheet("font-size: 12px; font-weight: bold;");
    send_button_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    default_button_ = new QPushButton("Reset Default", this);
    default_button_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    default_button_->setStyleSheet("font-size: 12px; font-weight: bold;");
    QHBoxLayout* button_layout = new QHBoxLayout;
    button_layout->addWidget(send_button_);
    button_layout->addWidget(default_button_);
    connect(send_button_, &QPushButton::clicked, this, &PID_GUI::send_button_pressed);
    connect(default_button_, &QPushButton::clicked, this, &PID_GUI::default_button_pressed);

    // Fille gains layout
    // gains_layout->addLayout(surge_layout);
    gains_layout->addLayout(surge_layout);
    gains_layout->addLayout(sway_layout);
    gains_layout->addLayout(heave_layout);
    gains_layout->addLayout(yaw_layout);
    gains_layout->addLayout(button_layout);

    //////////////////////////////////////////////////////////////

    // Movement //////////////////////////////////////////////////
    QVBoxLayout* move_layout = new QVBoxLayout;

    QVBoxLayout* surge_move_layout = new QVBoxLayout;
    QLabel* surge_move_label = new QLabel("Forward [m]", this);
    surge_move_label->setAlignment(Qt::AlignCenter);
    surge_move_label->setStyleSheet("font-weight: bold; font-size: 16px;");
    surge_move_label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    surge_move_ = new QLineEdit(this);
    //surge_move_->setValidator(new QDoubleValidator(-100, 100, 2, this));
    surge_move_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    surge_move_layout->addWidget(surge_move_label, 0, Qt::AlignCenter);
    surge_move_layout->addWidget(surge_move_, 0, Qt::AlignCenter);

    QVBoxLayout* sway_move_layout = new QVBoxLayout;
    QLabel* sway_move_label = new QLabel("Sideways [m]", this);
    sway_move_label->setAlignment(Qt::AlignCenter);
    sway_move_label->setStyleSheet("font-weight: bold; font-size: 16px;");
    sway_move_label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sway_move_ = new QLineEdit(this);
    //sway_move_->setValidator(new QDoubleValidator(-100, 100, 2, this));
    sway_move_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sway_move_layout->addWidget(sway_move_label, 0, Qt::AlignCenter);
    sway_move_layout->addWidget(sway_move_, 0, Qt::AlignCenter);

    QVBoxLayout* heave_move_layout = new QVBoxLayout;
    QLabel* heave_move_label = new QLabel("Up/Down [m]", this);
    heave_move_label->setAlignment(Qt::AlignCenter);
    heave_move_label->setStyleSheet("font-weight: bold; font-size: 16px;");
    heave_move_label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    heave_move_ = new QLineEdit(this);
    //heave_move_->setValidator(new QDoubleValidator(-100, 100, 2, this));
    heave_move_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    heave_move_layout->addWidget(heave_move_label, 0, Qt::AlignCenter);
    heave_move_layout->addWidget(heave_move_, 0, Qt::AlignCenter);

    QVBoxLayout* yaw_move_layout = new QVBoxLayout;
    QLabel* yaw_move_label = new QLabel("Yaw [deg]", this);
    yaw_move_label->setAlignment(Qt::AlignCenter);
    yaw_move_label->setStyleSheet("font-weight: bold; font-size: 16px;");
    yaw_move_label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    yaw_move_ = new QLineEdit(this);
    //yaw_move_->setValidator(new QDoubleValidator(-100, 100, 2, this));
    yaw_move_ = new QLineEdit(this);
    //yaw_move_->setValidator(new QDoubleValidator(-100, 100, 2, this));
    yaw_move_layout->addWidget(yaw_move_label, 0, Qt::AlignCenter);
    yaw_move_layout->addWidget(yaw_move_, 0, Qt::AlignCenter);

    send_command_button_ = new QPushButton("Send Command", this);
    send_command_button_->setStyleSheet("font-size: 12px; font-weight: bold;");
    send_command_button_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    connect(send_command_button_, &QPushButton::clicked, this, &PID_GUI::send_command_button_pressed);

    move_layout->addLayout(surge_move_layout);
    move_layout->addLayout(sway_move_layout);
    move_layout->addLayout(heave_move_layout);
    move_layout->addLayout(yaw_move_layout);
    move_layout->addWidget(send_command_button_, 0, Qt::AlignCenter);

    //////////////////////////////////////////////////////////////


    // PREDEFINED GAInN VALUES/////////////////////////////////////

    //QLabel* predefined_title_ = new QLabel("Controller Settings", this);
    //predefined_title_->setAlignment(Qt::AlignCenter);
    //predefined_title_->setStyleSheet("font-weight: bold; font-size: 20px;");
    
    low_gains_button_ = new QPushButton("LOW", this);
    low_gains_button_->setCheckable(true);
    low_gains_button_->setStyleSheet("font-size: 20px; font-weight: bold;");
    low_gains_button_->setFixedSize(200, 200);
    low_gains_button_->setChecked(true);
    connect(low_gains_button_, &QPushButton::clicked, this, &PID_GUI::low_gains_button_pressed);

    medium_gains_button_ = new QPushButton("MEDIUM", this);
    medium_gains_button_->setCheckable(true);
    medium_gains_button_->setStyleSheet("font-size: 20px; font-weight: bold;");
    medium_gains_button_->setFixedSize(200, 200);
    connect(medium_gains_button_, &QPushButton::clicked, this, &PID_GUI::medium_gains_button_pressed);

    high_gains_button_ = new QPushButton("HIGH", this);
    high_gains_button_->setCheckable(true);
    high_gains_button_->setStyleSheet("font-size: 20px; font-weight: bold;");
    high_gains_button_->setFixedSize(200, 200);
    connect(high_gains_button_, &QPushButton::clicked, this, &PID_GUI::high_gains_button_pressed);

    advanced_settings_button_ = new QPushButton("Advanced Settings", this);
    advanced_settings_button_->setStyleSheet("font-size: 12px; font-weight: bold;");
    connect(advanced_settings_button_, &QPushButton::clicked, this, &PID_GUI::advanced_button_pressed);


    QVBoxLayout* predefined_gains_button_layout = new QVBoxLayout;
    //predefined_gains_button_layout->addWidget(predefined_title_, 0, Qt::AlignCenter);
    predefined_gains_button_layout->addWidget(low_gains_button_, 0, Qt::AlignCenter);
    predefined_gains_button_layout->addWidget(medium_gains_button_, 0, Qt::AlignCenter);
    predefined_gains_button_layout->addWidget(high_gains_button_, 0 , Qt::AlignCenter);
    predefined_gains_button_layout->addWidget(advanced_settings_button_, 0, Qt::AlignCenter);



    ////////////////////////////////////////////////////////////////

    // Set up main layout
    QHBoxLayout* widget_layout = new QHBoxLayout();
    main_layout->addWidget(title,1);
    widget_layout->addLayout(predefined_gains_button_layout,1);
    widget_layout->addLayout(gains_layout,1);
    widget_layout->addLayout(move_layout,1);
    main_layout->addLayout(widget_layout,19);

    // Get default gains
    set_default_gains();

    setLayout(main_layout);
}

PID_GUI::~PID_GUI() {
}

void PID_GUI::send_button_pressed() {
    QString msg = "$PID," + surge_kp_input_->text() + "," + surge_ki_input_->text() + "," + surge_kd_input_->text() + "," + sway_kp_input_->text() + "," + sway_ki_input_->text() + "," + sway_kd_input_->text() + "," + heave_kp_input_->text() + "," + heave_ki_input_->text() + "," + heave_kd_input_->text() + "," + yaw_kp_input_->text() + "," + yaw_ki_input_->text() + "," + yaw_kd_input_->text();
    send_udp_msg(msg);
}

void PID_GUI::send_udp_msg(const QString &msg) {

    // Send UDP message
    QHostAddress target_address = QHostAddress("127.0.0.1");
    quint16 target_port = 9100;
    udp_socket_->writeDatagram(msg.toUtf8(), target_address, target_port);

}

void PID_GUI::default_button_pressed() {

    // Medium gains are default atm
    surge_kp_input_->setText("0.2"); 
    surge_ki_input_->setText("0.05");
    surge_kd_input_->setText("0.05");
    sway_kp_input_->setText("0.2");
    sway_ki_input_->setText("0.05");
    sway_kd_input_->setText("0.05");
    heave_kp_input_->setText("0.25");
    heave_ki_input_->setText("0.05");
    heave_kd_input_->setText("0.05");
    yaw_kp_input_->setText("0.15");
    yaw_ki_input_->setText("0.05");
    yaw_kd_input_->setText("0.05");
}

void PID_GUI::send_command_button_pressed() {
    QString msg = "$MOVE," + surge_move_->text() + "," + sway_move_->text() + "," + heave_move_->text() + "," + yaw_move_->text();
    send_udp_msg(msg);
}

void PID_GUI::low_gains_button_pressed() {
    std::cout << "Low Gains Button Is Pressed!" << std::endl;
    if (low_gains_button_->isChecked()) {
        medium_gains_button_->setChecked(false);
        high_gains_button_->setChecked(false);

        // Change predefined gains accordingly
        surge_kp_input_->setText("0.2"); 
        surge_ki_input_->setText("0.05");
        surge_kd_input_->setText("0.05");
        sway_kp_input_->setText("0.2");
        sway_ki_input_->setText("0.05");
        sway_kd_input_->setText("0.05");
        heave_kp_input_->setText("0.25");
        heave_ki_input_->setText("0.05");
        heave_kd_input_->setText("0.05");
        yaw_kp_input_->setText("0.15");
        yaw_ki_input_->setText("0.05");
        yaw_kd_input_->setText("0.05");
        surge_move_->setText("0.0");
        sway_move_->setText("0.0");
        heave_move_->setText("0.0");
        yaw_move_->setText("0.0");

        QString msg = "$PID," + surge_kp_input_->text() + "," + surge_ki_input_->text() + "," + surge_kd_input_->text() + "," + sway_kp_input_->text() + "," + sway_ki_input_->text() + "," + sway_kd_input_->text() + "," + heave_kp_input_->text() + "," + heave_ki_input_->text() + "," + heave_kd_input_->text() + "," + yaw_kp_input_->text() + "," + yaw_ki_input_->text() + "," + yaw_kd_input_->text();
        send_udp_msg(msg);

        // Change predefined gains accordingly
    } else {
        // Low gains already in effect, no need to do anything
        low_gains_button_->setChecked(true);
    }
}

void PID_GUI::medium_gains_button_pressed() {
    std::cout << "Medium Gains Button Is Pressed!" << std::endl;
    if (medium_gains_button_->isChecked()) {
        low_gains_button_->setChecked(false);
        high_gains_button_->setChecked(false);

        // Change predefined gains accordingly
        surge_kp_input_->setText("0.4"); 
        surge_ki_input_->setText("0.1");
        surge_kd_input_->setText("0.15");
        sway_kp_input_->setText("0.4");
        sway_ki_input_->setText("0.1");
        sway_kd_input_->setText("0.15");
        heave_kp_input_->setText("0.3");
        heave_ki_input_->setText("0.1");
        heave_kd_input_->setText("0.1");
        yaw_kp_input_->setText("0.3");
        yaw_ki_input_->setText("0.1");
        yaw_kd_input_->setText("0.2");
        surge_move_->setText("0.0");
        sway_move_->setText("0.0");
        heave_move_->setText("0.0");
        yaw_move_->setText("0.0");

        QString msg = "$PID," + surge_kp_input_->text() + "," + surge_ki_input_->text() + "," + surge_kd_input_->text() + "," + sway_kp_input_->text() + "," + sway_ki_input_->text() + "," + sway_kd_input_->text() + "," + heave_kp_input_->text() + "," + heave_ki_input_->text() + "," + heave_kd_input_->text() + "," + yaw_kp_input_->text() + "," + yaw_ki_input_->text() + "," + yaw_kd_input_->text();
        send_udp_msg(msg);

    } else {
        // Medium gains already in effect, no need to do anything
        medium_gains_button_->setChecked(true);
    }
}

void PID_GUI::high_gains_button_pressed() {
    std::cout << "High Gains Button Is Pressed!" << std::endl;
    if (high_gains_button_->isChecked()) {
        low_gains_button_->setChecked(false);
        medium_gains_button_->setChecked(false);

        // Change predefined gains accordingly
        surge_kp_input_->setText("0.6"); 
        surge_ki_input_->setText("0.2");
        surge_kd_input_->setText("0.3");
        sway_kp_input_->setText("0.6");
        sway_ki_input_->setText("0.2");
        sway_kd_input_->setText("0.3");
        heave_kp_input_->setText("0.7");
        heave_ki_input_->setText("0.3");
        heave_kd_input_->setText("0.2");
        yaw_kp_input_->setText("0.6");
        yaw_ki_input_->setText("0.15");
        yaw_kd_input_->setText("0.25");
        surge_move_->setText("0.0");
        sway_move_->setText("0.0");
        heave_move_->setText("0.0");
        yaw_move_->setText("0.0");

        QString msg = "$PID," + surge_kp_input_->text() + "," + surge_ki_input_->text() + "," + surge_kd_input_->text() + "," + sway_kp_input_->text() + "," + sway_ki_input_->text() + "," + sway_kd_input_->text() + "," + heave_kp_input_->text() + "," + heave_ki_input_->text() + "," + heave_kd_input_->text() + "," + yaw_kp_input_->text() + "," + yaw_ki_input_->text() + "," + yaw_kd_input_->text();
        send_udp_msg(msg);

    } else {
        // High gains already in effect, no need to do anything
        high_gains_button_->setChecked(true);
    }
}

void PID_GUI::advanced_button_pressed() {

    key_dialog key_dia(this);
    key_dia.set_key(key_);
    if (key_dia.exec() == QDialog::Accepted && key_dia.is_key_correct()) {

        // Enable advanced settings
        enable_advanced_settings(true);
        advanced_settings_button_->setEnabled(false);
    } 
       
}

void PID_GUI::enable_advanced_settings(bool enable) {

    // Set interface based on input
    surge_kp_input_->setEnabled(enable);
    surge_ki_input_->setEnabled(enable);
    surge_kd_input_->setEnabled(enable);
    sway_kp_input_->setEnabled(enable);
    sway_ki_input_->setEnabled(enable);
    sway_kd_input_->setEnabled(enable);
    heave_kp_input_->setEnabled(enable);
    heave_ki_input_->setEnabled(enable);
    heave_kd_input_->setEnabled(enable);
    yaw_kp_input_->setEnabled(enable);
    yaw_ki_input_->setEnabled(enable);
    yaw_kd_input_->setEnabled(enable);

    send_button_->setEnabled(enable);
    default_button_->setEnabled(enable);

    if (!enable) {
        surge_label_->setStyleSheet("font-weight: bold; font-size: 16px; color: gray;");
        surge_kp_label_->setStyleSheet("font-weight: bold; font-size: 12px; color: gray;");
        surge_ki_label_->setStyleSheet("font-weight: bold; font-size: 12px; color: gray;");
        surge_kd_label_->setStyleSheet("font-weight: bold; font-size: 12px; color: gray;");
        sway_label_->setStyleSheet("font-weight: bold; font-size: 16px; color: gray;");
        sway_kp_label_->setStyleSheet("font-weight: bold; font-size: 12px; color: gray;");
        sway_ki_label_->setStyleSheet("font-weight: bold; font-size: 12px; color: gray;");
        sway_kd_label_->setStyleSheet("font-weight: bold; font-size: 12px; color: gray;");
        heave_label_->setStyleSheet("font-weight: bold; font-size: 16px; color: gray;");
        heave_kp_label_->setStyleSheet("font-weight: bold; font-size: 12px; color: gray;");
        heave_ki_label_->setStyleSheet("font-weight: bold; font-size: 12px; color: gray;");
        heave_kd_label_->setStyleSheet("font-weight: bold; font-size: 12px; color: gray;");
        yaw_label_->setStyleSheet("font-weight: bold; font-size: 16px; color: gray;");
        yaw_kp_label_->setStyleSheet("font-weight: bold; font-size: 12px; color: gray;");
        yaw_ki_label_->setStyleSheet("font-weight: bold; font-size: 12px; color: gray;");
        yaw_kd_label_->setStyleSheet("font-weight: bold; font-size: 12px; color: gray;");

    } else {
        surge_label_->setStyleSheet("font-weight: bold; font-size: 16px; color: black;");
        surge_kp_label_->setStyleSheet("font-weight: bold; font-size: 12px; color: black;");
        surge_ki_label_->setStyleSheet("font-weight: bold; font-size: 12px; color: black;");
        surge_kd_label_->setStyleSheet("font-weight: bold; font-size: 12px; color: black;");
        sway_label_->setStyleSheet("font-weight: bold; font-size: 16px; color: black;");
        sway_kp_label_->setStyleSheet("font-weight: bold; font-size: 12px; color: black;");
        sway_ki_label_->setStyleSheet("font-weight: bold; font-size: 12px; color: black;");
        sway_kd_label_->setStyleSheet("font-weight: bold; font-size: 12px; color: black;");
        heave_label_->setStyleSheet("font-weight: bold; font-size: 16px; color: black;");
        heave_kp_label_->setStyleSheet("font-weight: bold; font-size: 12px; color: black;");
        heave_ki_label_->setStyleSheet("font-weight: bold; font-size: 12px; color: black;");
        heave_kd_label_->setStyleSheet("font-weight: bold; font-size: 12px; color: black;");
        yaw_label_->setStyleSheet("font-weight: bold; font-size: 16px; color: black;");
        yaw_kp_label_->setStyleSheet("font-weight: bold; font-size: 12px; color: black;");
        yaw_ki_label_->setStyleSheet("font-weight: bold; font-size: 12px; color: black;");
        yaw_kd_label_->setStyleSheet("font-weight: bold; font-size: 12px; color: black;");

    }
}

void PID_GUI::set_default_gains() {

    // Set default gains
    surge_downforce_ = 0.0;
    surge_kp_ = 0.4;
    surge_ki_ = 0.2;
    surge_kd_ = 0.2;

    sway_downforce_ = 0.0;
    sway_kp_ = 0.4;
    sway_ki_ = 0.2;
    sway_kd_ = 0.2;

    heave_downforce_ = 0.0;
    heave_kp_ = 0.4;
    heave_ki_ = 0.2;
    heave_kd_ = 0.2;

    yaw_downforce_ = 0.0;
    yaw_kp_ = 0.4;
    yaw_ki_ = 0.2;
    yaw_kd_ = 0.2;

    surge_kp_input_->setText(QString::number(surge_kp_));
    surge_ki_input_->setText(QString::number(surge_ki_));
    surge_kd_input_->setText(QString::number(surge_kd_));
    sway_kp_input_->setText(QString::number(sway_kp_));
    sway_ki_input_->setText(QString::number(sway_ki_));
    sway_kd_input_->setText(QString::number(sway_kd_));
    heave_kp_input_->setText(QString::number(heave_kp_));
    heave_ki_input_->setText(QString::number(heave_ki_));
    heave_kd_input_->setText(QString::number(heave_kd_));
    yaw_kp_input_->setText(QString::number(yaw_kp_));
    yaw_ki_input_->setText(QString::number(yaw_ki_));
    yaw_kd_input_->setText(QString::number(yaw_kd_));

    surge_move_->setText("0.0");
    sway_move_->setText("0.0");
    heave_move_->setText("0.0");
    yaw_move_->setText("0.0");

    // Set default values to the GUI
    enable_advanced_settings(false);
}




////////////////////////// Key Dialog //////////////////////////

key_dialog::key_dialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Enter keyword");
    setModal(true);

    // Layout and Widgets
    QVBoxLayout* main_layout = new QVBoxLayout;

    QLabel* prompt = new QLabel("WARNING! Changing parameters may alter system functionality.\nPassword:", this);
    main_layout->addWidget(prompt);

    key_input_ = new QLineEdit(this);
    key_input_->setEchoMode(QLineEdit::Password);
    main_layout->addWidget(key_input_);

    error_label_ = new QLabel("", this); 
    error_label_->setStyleSheet("color: red;");
    error_label_->setVisible(false);
    main_layout->addWidget(error_label_);

    QHBoxLayout* button_layout = new QHBoxLayout;
    key_button_ = new QPushButton("Enter", this);
    cancel_button_ = new QPushButton("Cancel", this);
    connect(key_button_, &QPushButton::clicked, this, &key_dialog::key_entered);
    connect(cancel_button_, &QPushButton::clicked, this, &key_dialog::close);

    button_layout->addWidget(key_button_);
    button_layout->addWidget(cancel_button_);
    main_layout->addLayout(button_layout);

    setLayout(main_layout);
    
}

key_dialog::~key_dialog() {
}

void key_dialog::key_entered() {
    if (key_input_->text() == key_) {
        password_correct_ = true;
        accept(); // Close the dialog
    } else {
        error_label_->setText("Incorrect password. Please try again.");
        error_label_->setVisible(true);
        key_input_->setStyleSheet("border: 2px solid red;"); // Red border
    }
}   

void key_dialog::close() {
    reject();
}

void key_dialog::set_key(QString key) {
    key_ = key;
}

bool key_dialog::is_key_correct() {
    return password_correct_;
}
