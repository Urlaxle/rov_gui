#include "gui/compass_gui.hpp"

compass::compass(QWidget *parent)
    : QWidget(parent), heading_angle(0) {
    // Load the robot image
    robot_image = QPixmap(":/images/minerva.png");
    robot_image = robot_image.scaled(250, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Timer to update the heading angle and repaint
    //QTimer *timer = new QTimer(this);
    //connect(timer, &QTimer::timeout, this, &compass::update_heading);
    //timer->start(100);  // Update every 100 ms
}

compass::~compass() {
}
/*
void compass::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    // Use the default Qt background color
    painter.fillRect(rect(), palette().color(QPalette::Window));

    // Draw the compass
    int diameter = qMin(width(), height()) - 20; // Leave some margin
    int centerX = width() / 2;
    int centerY = height() / 2;
    int radius = diameter / 2;

    QPen pen(Qt::black, 2); // Black border with 2px width
    painter.setPen(pen);
    painter.drawEllipse(centerX - radius, centerY - radius, diameter, diameter);

    // Draw the directional indicators (0, 90, 180, 270 degrees)
    QFont font = painter.font();
    font.setPointSize(16);
    painter.setFont(font);

    painter.drawText(centerX - 7, centerY - radius + 30, "0");    // Top
    painter.drawText(centerX + radius - 40, centerY + 8, "90");    // Right
    painter.drawText(centerX - 18, centerY + radius - 20, "180"); // Bottom
    painter.drawText(centerX - radius + 15, centerY + 8, "270");  // Left

    // Draw directional lines
    painter.drawLine(centerX, centerY - radius, centerX, centerY - radius + 10); // Top (0)
    painter.drawLine(centerX + radius, centerY, centerX + radius - 10, centerY); // Right (90)
    painter.drawLine(centerX, centerY + radius, centerX, centerY + radius - 10); // Bottom (180)
    painter.drawLine(centerX - radius, centerY, centerX - radius + 10, centerY); // Left (270)

    // Draw the robot image on top of the compass
    painter.save();  // Save the current painter state

    // Move the painter origin to the center of the compass
    painter.translate(centerX, centerY);

    // Rotate the painter by the current heading angle
    painter.rotate(heading_angle);

    // Draw the robot image, centered on the compass
    int robotWidth = robot_image.width();
    int robotHeight = robot_image.height();
    painter.drawPixmap(-robotWidth / 2, -robotHeight / 2, robot_image);

    painter.restore();  // Restore the painter state
}
*/

void compass::paintEvent(QPaintEvent *event) {
        QPainter painter(this);

        // Use the default Qt background color
        painter.fillRect(rect(), palette().color(QPalette::Window));

        // Draw the compass
        int diameter = qMin(width(), height()) - 20; // Leave some margin
        int centerX = width() / 2;
        int centerY = height() / 2;
        int radius = diameter / 2;

        QPen pen(Qt::black, 2); // Black border with 2px width
        painter.setPen(pen);
        painter.drawEllipse(centerX - radius, centerY - radius, diameter, diameter);

        // Draw the directional indicators (0, 90, 180, 270 degrees)
        QFont font = painter.font();
        font.setPointSize(16);
        painter.setFont(font);

        painter.drawText(centerX - 7, centerY - radius + 30, "0");    // Top
        painter.drawText(centerX + radius - 40, centerY + 8, "90");  // Right
        painter.drawText(centerX - 18, centerY + radius - 20, "180"); // Bottom
        painter.drawText(centerX - radius + 15, centerY + 8, "270"); // Left

        // Draw directional lines
        painter.drawLine(centerX, centerY - radius, centerX, centerY - radius + 10); // Top (0)
        painter.drawLine(centerX + radius, centerY, centerX + radius - 10, centerY); // Right (90)
        painter.drawLine(centerX, centerY + radius, centerX, centerY + radius - 10); // Bottom (180)
        painter.drawLine(centerX - radius, centerY, centerX - radius + 10, centerY); // Left (270)

        // Draw the robot image on top of the compass
        painter.save(); // Save the current painter state

        // Move the painter origin to the center of the compass
        painter.translate(centerX, centerY);

        // Rotate the painter by the current heading angle
        painter.rotate(heading_angle);

        // Draw the robot image, centered on the compass
        int robotWidth = robot_image.width();
        int robotHeight = robot_image.height();
        painter.drawPixmap(-robotWidth / 2, -robotHeight / 2, robot_image);

        painter.restore(); // Restore the painter state

        // Draw the heading setpoint indicator if enabled
        if (show_setpoint) {
            painter.save();
            painter.translate(centerX, centerY);
            painter.rotate(heading_setpoint);

            QPen setpointPen(Qt::red, 4); // Red pen for the setpoint indicator
            painter.setPen(setpointPen);
            painter.drawLine(0, -radius, 0, -radius + 20); // Draw the indicator as a line pointing outward

            painter.restore();
        }
    }

void compass::update_heading() {
    // Simulate a heading change
    heading_angle += 1;
    if (heading_angle >= 360) {
        heading_angle -= 360;
    }

    // Trigger a repaint
    update();
}

void compass::set_heading(const int& heading, const int& heading_hold) {

    if (heading > 360 || heading < 0) {
        return;
    }

    // Simulate a heading change, in degrees. The ROV is 90 degrees rotated counter clockwise
    heading_angle = heading;

    // Set an indicator on desired heading
    if (heading_hold > 0 && heading_hold < 360) {
        heading_setpoint = heading_hold;
        show_setpoint = true;
    } else {
        show_setpoint = false;
    }

    update();
}