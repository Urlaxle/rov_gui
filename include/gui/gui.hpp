#ifndef CRAZYFLIE_GUI_H_
#define CRAZYFLIE_GUI_H_

// GUI elements
#include <gui/udp_sniffer_gui.hpp>
#include <gui/configuration_gui.hpp>
#include <gui/buttons_gui.hpp>
#include <gui/compass_gui.hpp>
#include <gui/thrusters_gui.hpp>

// QT 
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
#include <QGridLayout>
#include <QProgressBar>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTransform>
#include <QTimer>
#include <QPainter>

#include <iostream>


// MAIN GUI
class GUI : public QWidget{
    Q_OBJECT

public:
    GUI(QWidget *parent = nullptr);
    ~GUI();

private:
    // Buttons presses
    void update_config(const QString &ip, int port1, int port2, int port3);
    void setup_status_lights();
    void write_to_terminal(const QString &msg);
    void setupSingleLightGrid(QWidget *parent, const QString &groupName, const QString& status1, const QString& status2, const QString& status3, const QString& status4
                              , const QString& indicator1, const QString& indicator2, const QString& indicator3, 
                              const QString& light_color1, const QString& light_color2, const QString& light_color3);

private slots:
    void on_start_button();
    void on_config_button();
    void on_sniffer_button();
    void on_exit_button();

private:

    // IP address and port of the control PC
    QString ip_address_ = "172.16.1.70";
    int control_system_port_ = 8570;
    int system_status_port_ = 8670;
    int mission_status_port_ = 8671;

    // GUI Elements
    QVBoxLayout* left_layout_;
    QVBoxLayout* right_layout_;
    buttons* buttons_widget_;
    compass* compass_widget_;
    thrusters* thrusters_widget_;
    QTextEdit* terminal_;

    // GUI elements
    QWidget *status_light_widget;

};

#endif