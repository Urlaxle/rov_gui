#include "gui.hpp"

GUI::GUI(QWidget *parent) : QMainWindow(parent) {

    centralWidget = new QWidget(this);
    mainLayout = new QVBoxLayout(centralWidget);

    groupBox = new QGroupBox("Crazyflie Control System", centralWidget);
    layout = new QVBoxLayout(groupBox);

    button1 = new QPushButton("Start", groupBox);
    button2 = new QPushButton("Configure", groupBox);
    button3 = new QPushButton("Exit", groupBox);

    layout->addWidget(button1);
    layout->addWidget(button2);
    layout->addWidget(button3);

    groupBox->setLayout(layout);
    mainLayout->addWidget(groupBox);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

}

GUI::~GUI() {
}