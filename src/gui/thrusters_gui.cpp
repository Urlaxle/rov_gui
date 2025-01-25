#include "gui/thrusters_gui.hpp"



// For side thrusters
rotated_bar::rotated_bar(QWidget *parent)
    : QWidget(parent) {
    angle_ = 0;

    QGraphicsScene *scene = new QGraphicsScene();
    bar_ = new QProgressBar();

    QGraphicsProxyWidget *proxy_ = scene->addWidget(bar_);
    proxy_->setRotation(angle_);

    QGraphicsView *view = new QGraphicsView(scene);
    view->show();

}

rotated_bar::~rotated_bar() {
}

void rotated_bar::set_rotation(int angle) {
    angle_ = angle;
    set_rotation(angle_);
    update();
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
    // Thruster Layout
    thruster_layout_ = new QGridLayout;
    
    for (int i = 0; i < 7; ++i) {
        // Create progress bar
        bars_[i] = new QProgressBar();
        bars_[i]->setOrientation(Qt::Vertical);
        bars_[i]->setRange(0, 100);
        bars_[i]->setValue(0); // Initial value
        //bars_[i]->set_rotation(90); // Rotate 90 degrees

        // Create label
        labels_[i] = new QLabel(labels_text_[i]);
        labels_[i]->setAlignment(Qt::AlignCenter);
        labels_[i]->setStyleSheet("font-weight: bold;");

        // Add to layout
        int row = (i < 3) ? 0 : 2; // Top row for first 3 bars, bottom row for next 4 bars
        int col = (i < 3) ? 1 + (i*2) : (i - 3) * 2;
        thruster_layout_->addWidget(bars_[i], row, col);  // Add bar
        thruster_layout_->addWidget(labels_[i], row+1, col);  // Add label below the bar
    }

    setLayout(thruster_layout_);
}

thrusters::~thrusters() {
}

QProgressBar* thrusters::get_thruster(int i) const {
    return bars_[i];
}