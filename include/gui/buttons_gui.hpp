#ifndef BUTTONS_GUI_H_
#define BUTTONS_GUI_H_

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>


class buttons : public QWidget {
    Q_OBJECT

public:
    explicit buttons(QWidget *parent = nullptr);
    ~buttons();

    // It should be possible to get buttons in main window
    QPushButton* get_start_button() const { return start_button; }
    QPushButton* get_log_button() const { return log_button; }
    QPushButton* get_configuration_button() const { return config_button; }
    QPushButton* get_sniffer_button() const { return sniffer_button; }
    QPushButton* get_synch_button() const { return synch_button; }
    QPushButton* get_help_button() const { return help_button; }

signals:
    void start_button_pressed();
    void log_button_pressed();
    void config_button_pressed();
    void sniffer_button_pressed();
    void synch_button_pressed();
    void help_button_pressed();
    void exit_button_pressed();

private slots:
    void on_start_button();
    void on_log_button();
    void on_config_button();
    void on_sniffer_button();
    void on_synch_button();
    void on_help_button();
    void on_exit_button();

private:

    // Layouts
    QVBoxLayout *button_layout;
    
    // Buttons
    QPushButton *start_button;
    QPushButton *log_button;
    QPushButton *sniffer_button;
    QPushButton *config_button;
    QPushButton *synch_button;
    QPushButton *help_button;
    QPushButton *exit_button;

};







#endif