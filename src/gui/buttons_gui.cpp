#include "gui/buttons_gui.hpp"

buttons::buttons(QWidget *parent) : QWidget(parent) {

    // Combine buttons and layouts
    button_layout = new QVBoxLayout;
    start_button = new QPushButton("START CONTROL SYSTEM");
    log_button = new QPushButton("START LOGGING");
    config_button = new QPushButton("CONFIGURE");
    sniffer_button = new QPushButton("UDP SNIFFER");
    synch_button = new QPushButton("SYNCHRONIZE");
    help_button = new QPushButton("HELP");
    exit_button = new QPushButton("EXIT");

    // Set checkable buttons
    config_button->setCheckable(true);
    start_button->setCheckable(true);
    sniffer_button->setCheckable(true);

    // Add buttons to layout
    button_layout->addWidget(start_button);
    button_layout->addWidget(log_button);
    button_layout->addWidget(config_button);
    button_layout->addWidget(sniffer_button);
    button_layout->addWidget(synch_button);
    button_layout->addWidget(help_button);
    button_layout->addWidget(exit_button);
    button_layout->addStretch();

    // Connect signals and slots
    connect(start_button, &QPushButton::clicked, this, &buttons::on_start_button);
    connect(log_button, &QPushButton::clicked, this, &buttons::on_log_button);
    connect(config_button, &QPushButton::clicked, this, &buttons::on_config_button);
    connect(sniffer_button, &QPushButton::clicked, this, &buttons::on_sniffer_button);
    connect(synch_button, &QPushButton::clicked, this, &buttons::on_synch_button);
    connect(help_button, &QPushButton::clicked, this, &buttons::on_help_button);
    connect(exit_button, &QPushButton::clicked, this, &buttons::on_exit_button);

    // Set layout
    setLayout(button_layout);
}

buttons::~buttons() {
    delete button_layout;
    delete start_button;
    delete log_button;
    delete config_button;
    delete sniffer_button;
    delete synch_button;
    delete help_button;
    delete exit_button;
}

void buttons::on_start_button() {
    emit start_button_pressed();
}

void buttons::on_log_button() {
    emit log_button_pressed();
}

void buttons::on_sniffer_button() {
    emit sniffer_button_pressed();
}

void buttons::on_config_button() {
    emit config_button_pressed();
}

void buttons::on_synch_button() {
    emit synch_button_pressed();
}

void buttons::on_help_button() {
    emit help_button_pressed();
}

void buttons::on_exit_button() {
    emit exit_button_pressed();
}