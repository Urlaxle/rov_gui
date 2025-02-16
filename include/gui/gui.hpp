#ifndef CRAZYFLIE_GUI_H_
#define CRAZYFLIE_GUI_H_

// GUI elements
#include <gui/udp_sniffer_gui.hpp>
#include <gui/configuration_gui.hpp>
#include <gui/buttons_gui.hpp>
#include <gui/compass_gui.hpp>
#include <gui/thrusters_gui.hpp>
#include <gui/indicator_gui.hpp>    
#include <gui/waypoint_list.hpp>
#include <gui/number_display.hpp>
#include <gui/depth_altitude_plot.hpp>
#include <gui/pid_gui.hpp>
#include <gui/altitude_gui.hpp>

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
#include <QTabWidget>
#include <QTime>
#include <QVBoxLayout>
#include <QUdpSocket>

#include <iostream>
#include <string_view>
#include <vector>


// MAIN GUI
class GUI : public QWidget{
    Q_OBJECT

public:
    GUI(QWidget *parent = nullptr);
    ~GUI();

private:
    void update_config(const QString &ip, int port1, int port2, int port3);
    void write_to_terminal(const QString &msg);
    void send_udp_msg(const QString &msg);

private slots:
    // Buttons presses
    void on_start_button();
    void on_config_button();
    void on_sniffer_button();
    void on_exit_button();
    void on_stop_button();

    void toogle_listening();
    void close();

private:

    // IP address and port of the control PC
    QString ip_address_ = "127.0.0.1";
    int control_system_port_ = 8570;
    int system_status_port_ = 8670;
    int mission_status_port_ = 8671;

    // GUI Elements
    QVBoxLayout* left_layout_;
    QVBoxLayout* right_layout_;
    QVBoxLayout* stop_layout_;
    QPushButton* stop_button_;
    buttons* buttons_widget_;
    compass* compass_widget_;
    thrusters* thrusters_widget_;
    QTextEdit* terminal_;
    indicators* status_light_widget_;
    waypoint_list* waypoint_list_widget_;
    number_display* number_display_widget_;
    DepthPlotWidget* depth_plot_;
    AltitudeTuning* altitude_tuning_widget_;

    // Communication parameters
    QUdpSocket* control_socket_;
    QUdpSocket* udp_socket_;
    quint16 control_port_ = 9101;
    bool control_is_listening_ = false;


};

#endif
