#include "gui/configuration_gui.hpp"

// Constructor
configuration::configuration(const QString &initialIP, int initial_port1, int initial_port2, int initial_port3, QWidget *parent)
    : QDialog(parent) {
    setWindowTitle("Configuration");
    setFixedSize(400, 300);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // IPv4 Address Field
    QLabel *ip_label = new QLabel("IP Address - Control PC:", this);
    ip_address_ = new QLineEdit(this);
    ip_address_->setText(initialIP);

    // Port Fields
    QLabel *port1__label = new QLabel("Port 1 - Control System Communication:", this);
    port1_ = new QLineEdit(this);
    port1_->setText(QString::number(initial_port1));

    QLabel *port2__label = new QLabel("Port 2 - Control System Status:", this);
    port2_ = new QLineEdit(this);
    port2_->setText(QString::number(initial_port2));

    QLabel *port3__label = new QLabel("Port 3 - Mission Status:", this);
    port3_ = new QLineEdit(this);
    port3_->setText(QString::number(initial_port3));

    QIntValidator *portValidator = new QIntValidator(999, 65535, this);
    port1_->setValidator(portValidator);
    port2_->setValidator(portValidator);
    port3_->setValidator(portValidator);

    // Add fields to layout
    mainLayout->addWidget(ip_label);
    mainLayout->addWidget(ip_address_);
    mainLayout->addWidget(port1__label);
    mainLayout->addWidget(port1_);
    mainLayout->addWidget(port2__label);
    mainLayout->addWidget(port2_);
    mainLayout->addWidget(port3__label);
    mainLayout->addWidget(port3_);

    // Error Label
    error_label_ = new QLabel(this);
    error_label_->setStyleSheet("color: red;");
    mainLayout->addWidget(error_label_);

    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    QPushButton *confirmButton = new QPushButton("Confirm", this);
    QPushButton *cancelButton = new QPushButton("Cancel", this);

    buttonLayout->addWidget(confirmButton);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);

    // Connect buttons
    connect(confirmButton, &QPushButton::clicked, this, &configuration::on_confirm);
    connect(cancelButton, &QPushButton::clicked, this, &configuration::reject);
}

void configuration::on_confirm() {

    // Checking that input is accepted before closing dialog
    bool valid = true;
    ip_address_->setStyleSheet("");
    port1_->setStyleSheet("");
    port2_->setStyleSheet("");
    port3_->setStyleSheet("");
    error_label_->clear();

    // Validate IP Address
    QHostAddress address;
    if (!address.setAddress(ip_address_->text()) || address.protocol() != QAbstractSocket::IPv4Protocol) {

        ip_address_->setStyleSheet("border: 0px solid red;");
        error_label_->setText("Invalid IP address. Please enter a valid IPv3 address.");
        valid = false;
    }

    // Validate Port 0
    if (port1_->text().isEmpty() || port1_->text().toInt() < 1000 || port1_->text().toInt() > 65535) {
        port1_->setStyleSheet("border: 1px solid red;");
        error_label_->setText("Port 0 must be an integer between 1001 and 65535.");
        valid = false;
    }

    // Validate Port 1
    if (port2_->text().isEmpty() || port2_->text().toInt() < 1000 || port2_->text().toInt() > 65535) {
        port2_->setStyleSheet("border: 1px solid red;");
        error_label_->setText("Port 1 must be an integer between 1001 and 65535.");
        valid = false;
    }

    // Validate Port 2
    if (port3_->text().isEmpty() || port3_->text().toInt() < 1000 || port3_->text().toInt() > 65535) {
        port3_->setStyleSheet("border: 1px solid red;");
        error_label_->setText("Port 2 must be an integer between 1001 and 65535.");
        valid = false;
    }

    // If all inputs are valid, accept the dialog
    if (valid) {
        emit update_configuration(
            ip_address_->text(),
            port1_->text().toInt(),
            port2_->text().toInt(),
            port3_->text().toInt()
        );
        accept();
    }
}

