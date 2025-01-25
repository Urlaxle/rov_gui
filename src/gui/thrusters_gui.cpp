#include "gui/thrusters_gui.hpp"
#include <iostream>


// Progress Bar starting from middle




// For side thrusters
rotated_bar::rotated_bar(QWidget *parent)
    : QGraphicsView(parent) {
{

    scene_ = new QGraphicsScene(this);
    setScene(scene_);

    // Set up a progress bar and embedd it
    bar_ = new QProgressBar();
    bar_ ->setAlignment(Qt::AlignCenter);
    bar_->setFixedSize(300, 50);
    bar_->setTextVisible(false);
    proxy_ = new QGraphicsProxyWidget();
    proxy_->setWidget(bar_);
    scene_->addItem(proxy_);

    setFrameStyle(QFrame::NoFrame);                  // Remove the view's border
    setRenderHint(QPainter::Antialiasing);

    setRenderHint(QPainter::Antialiasing);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(300, 300);
}


}

rotated_bar::~rotated_bar() {
}

void rotated_bar::set_inverted(bool inverted) {
    bar_->setInvertedAppearance(inverted);
}

void rotated_bar::set_rotation(int angle) {
    angle_ = angle;
    proxy_->setRotation(angle_);
}

void rotated_bar::setOrientation(Qt::Orientation orientation) {
    bar_->setOrientation(orientation);
}

void rotated_bar::setValue(int value) {
    bar_->setValue(value);
}

void rotated_bar::setRange(int min, int max) {
    bar_->setRange(min, max);
}

thrusters::thrusters(QWidget *parent)
    : QWidget(parent) {


    // Title widget
    QLabel* title = new QLabel("Thruster Forces", this);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-weight: bold; font-size: 20px;");
    QVBoxLayout* title_layout = new QVBoxLayout;


    // Thruster Layout
    thruster_layout_ = new QHBoxLayout();


    // Horizontal Thrusters
    QVBoxLayout* vertical_horizontal_layout = new QVBoxLayout;
    QHBoxLayout* horizontal_layout_1 = new QHBoxLayout;
    QHBoxLayout* horizontal_layout_2 = new QHBoxLayout;
    QGridLayout* grid_horizontal_layout = new QGridLayout;
    
    for (int i = 0; i < 4; ++i) {
        rotated_bars_[i] = new rotated_bar();
        rotated_bars_[i]->setOrientation(Qt::Horizontal);
        rotated_bars_[i]->setRange(0, 100);
        rotated_bars_[i]->setValue(0); // Initial value
        if (i  == 0 || i ==3 ) {
            rotated_bars_[i]->set_rotation(-45); // Rotate 270 degrees
        } else{
            rotated_bars_[i]->set_rotation(45); // Rotate 90 degrees
            rotated_bars_[i]->set_inverted(true);
        }

        if (i < 2) {
            grid_horizontal_layout->addWidget(rotated_bars_[i], 0, i);  // Add bar
        } else {
        grid_horizontal_layout->addWidget(rotated_bars_[i], 2, i-2);  // Add bar
        }
        
    }


    horizontal_layout_1->addWidget(rotated_bars_[0]);
    horizontal_layout_1->addWidget(rotated_bars_[1]);
    horizontal_layout_2->addWidget(rotated_bars_[2]);
    horizontal_layout_2->addWidget(rotated_bars_[3]);
    vertical_horizontal_layout->addLayout(horizontal_layout_1);
    vertical_horizontal_layout->addLayout(horizontal_layout_2);
    vertical_horizontal_layout->setSpacing(0);


    // Vertical Thrusters
    QGridLayout* grid_layout = new QGridLayout;

    for (int i = 0; i < 3; ++i) {
        bars_[i] = new QProgressBar();
        bars_[i]->setOrientation(Qt::Vertical);
        bars_[i]->setRange(0, 100);
        bars_[i]->setValue(0); // Initial value
        bars_[i]->setFixedSize(50, 300);

        if (i == 0 || i == 2) {
            grid_layout->addWidget(bars_[i], 0, i);  // Add bar
        } else {
            grid_layout->addWidget(bars_[i], 1, i);  // Add bar
        }
    }

    thruster_layout_->addLayout(grid_horizontal_layout);
    thruster_layout_->addLayout(grid_layout);

    // Set layout
    title_layout->addWidget(title);
    title_layout->addLayout(thruster_layout_);
    setLayout(title_layout);
    //setLayout(thruster_layout_);
}

thrusters::~thrusters() {
}

rotated_bar* thrusters::get_thruster(int i) const {
    return rotated_bars_[i];
}