#ifndef CRAZYFLIE_GUI_H_
#define CRAZYFLIE_GUI_H_

#include <QMainWindow>
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QString>
#include <QIntValidator>
#include <QHostAddress>
#include <QTextEdit>

#include <iostream>

// MAIN GUI
class GUI : public QWidget{
    Q_OBJECT

public:
    GUI(QWidget *parent = nullptr);
    ~GUI();

private:
    // Buttons presses
    void on_start_button();
    void on_config_button();
    void on_exit_button();
    void update_config(const QString &ip, int port1, int port2, int port3);
    void setup_status_lights();
    void write_to_terminal(const QString &msg);
    void setupSingleLightGrid(QWidget *parent, const QString &groupName);


private:

    // IP address and port of the control PC
    QString ip_address_ = "172.16.1.70";
    int control_system_port_ = 8570;
    int system_status_port_ = 8670;
    int mission_status_port_ = 8671;

    // GUI elements
    QVBoxLayout *status_layout;
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QGroupBox *groupBox;
    QVBoxLayout *button_layout;
    QPushButton *start_button;
    QPushButton *log_button;
    QPushButton *sniffer_button;
    QPushButton *config_button;
    QPushButton *exit_button;
    QPushButton *help_button;
    QTextEdit *terminal;
    QWidget *status_light_widget;
};


// Configuration dialog
class ConfigDialog : public QDialog {
    Q_OBJECT

public:
    explicit ConfigDialog(const QString &initialIP, int initialPort1, int initialPort2, int initialPort3, QWidget *parent = nullptr);

signals:
    void configUpdated(const QString &ip, int port1, int port2, int port3);

private slots:
    void onConfirm();

private:
    QLineEdit *ip_address;
    QLineEdit *port1;
    QLineEdit *port2;
    QLineEdit *port3;
    QLabel *error_label;
};


#endif