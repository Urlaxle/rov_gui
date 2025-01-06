#include "udp_sniffer_gui.hpp"
#include <QHostAddress>

// Constructor for UDP Sniffer
udp_sniffer::udp_sniffer(QWidget *parent) :
    QDialog(parent), is_listening_(false), udp_socket_(new QUdpSocket(this)) 
    {

    // Layouts
    QVBoxLayout* main_layout = new QVBoxLayout(this);
    QHBoxLayout* input_layout = new QHBoxLayout();

    // Widgets
    QLabel* port_label = new QLabel("Port: ", this);
    port_input_ = new QLineEdit(this);
    port_input_->setPlaceholderText("8760");
    listen_button_ = new QPushButton("Start Listening", this);
    exit_button_ = new QPushButton("Exit", this);

    // Terminal for displaying incoming messages
    udp_terminal_ = new QTextEdit(this);
    udp_terminal_->setReadOnly(true);
    udp_terminal_->setFont(QFont("Courier",10));
    udp_terminal_->setStyleSheet("background-color: black; color: white; font-family: monospace; border: 5px solid gray; border-radius: 5px;");
    udp_terminal_->setPlaceholderText("Welcome to the UDP Sniffer");
    udp_terminal_->setFixedSize(800,600);

    // Place widgets in layouts
    input_layout->addWidget(port_label);
    input_layout->addWidget(port_input_);
    input_layout->addWidget(listen_button_);
    input_layout->addWidget(exit_button_);
    main_layout->addLayout(input_layout);
    main_layout->addWidget(udp_terminal_);

    // Set validator to ensure that a int is set as port
    QIntValidator* port_validator = new QIntValidator(1024, 49151, this);
    port_input_->setValidator(port_validator);

    // Connect buttons
    connect(listen_button_, &QPushButton::clicked, this, &udp_sniffer::toogle_listening);
    connect(exit_button_, &QPushButton::clicked, this, &udp_sniffer::close);
}

// QT handles destructor for us
udp_sniffer::~udp_sniffer() {
}

// Shuts down UDP sniffer window
void udp_sniffer::close() {
    QDialog::close();
}

// Toggles listening on the UDP socket
void udp_sniffer::toogle_listening() {

    // If we are not listening, start to listen
    if (!is_listening_) {

        // Checks that port is valid
        bool ok;
        quint16 port = port_input_->text().toUShort(&ok);
        if (!ok || port < 1024 || port > 49151) {
            udp_terminal_->append("Invalid port number. Please enter a port number between 1024 and 49151.");
            return;
        }

        // Binds port and starts to listen
        if (udp_socket_->bind(QHostAddress::Any, port)) {
            udp_terminal_->append(QString("Listening on port %1").arg(port));
            listen_button_->setText("Stop Listening");
            is_listening_ = true;

            // Capturing incoming messages
            connect(udp_socket_, &QUdpSocket::readyRead, this, [this](){
                while (udp_socket_->hasPendingDatagrams()) {
                    QByteArray datagram;
                    datagram.resize(udp_socket_->pendingDatagramSize());
                    QHostAddress sender;
                    quint16 sender_port;
                    udp_socket_->readDatagram(datagram.data(), datagram.size(), &sender, &sender_port);
                    udp_terminal_->append(QString("Message from %1:%2: %3").arg(sender.toString()).arg(sender_port).arg(QString(datagram)));
                }
            });

        // Port may already be busy    
        } else {
            udp_terminal_->append("Failed to bind port. Please try another port.");
        }

    } else {
        // Stop listening
        udp_socket_->close();
        listen_button_->setText("Start Listening");
        is_listening_ = false;
        udp_terminal_->append("Stopped listening on port " + port_input_->text());
    }
}