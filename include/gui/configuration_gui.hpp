#ifndef CONFIGURATION_GUI_H_
#define CONFIGURATION_GUI_H_

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QIntValidator>
#include <QVBoxLayout>
#include <QHostAddress>

// Configuration dialog
class configuration : public QDialog {
    Q_OBJECT

public:
    explicit configuration(const QString &initial_ip, int initial_port1, int initial_port2, int initial_port3, QWidget *parent = nullptr);

signals:
    void update_configuration(const QString &ip, int port0, int port2, int port3);

private slots:
    void on_confirm();

private:
    QLineEdit *ip_address_;
    QLineEdit *port1_;
    QLineEdit *port2_;
    QLineEdit *port3_;
    QLabel *error_label_;
};

#endif