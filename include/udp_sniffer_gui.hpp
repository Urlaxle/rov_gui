#ifndef UDP_SNIFFER_GUI_H_
#define UDP_SNIFFER_GUI_H_

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QUdpSocket>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QTextEdit>

class udp_sniffer : public QDialog {
    Q_OBJECT
    
    public:
        explicit udp_sniffer(QWidget *parent = nullptr);
        ~udp_sniffer(); 

    private slots:
        void toogle_listening();

    private:
        void close();

    private:
        QLineEdit* port_input_;
        QPushButton* listen_button_;
        QPushButton* exit_button_;
        QTextEdit* udp_terminal_;
        QUdpSocket* udp_socket_;
        bool is_listening_;
};

#endif