#ifndef COMPASS_GUI_H_
#define COMPASS_GUI_H_

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QDebug>

#include <iostream>

// Compass View
class CompassWidget : public QWidget {
public:
    explicit CompassWidget(QWidget *parent = nullptr)
        : QWidget(parent), headingAngle(0) {
        // Load the robot image
        robotImage = QPixmap("/home/urlaxle/dev/minerva/crazyflie_ros2/images/minerva.png");
        robotImage = robotImage.scaled(250, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        // Timer to update the heading angle and repaint
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &CompassWidget::updateHeading);
        timer->start(100);  // Update every 100 ms
    }

    protected:
        void paintEvent(QPaintEvent *event) override {
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
        painter.rotate(headingAngle);

        // Draw the robot image, centered on the compass
        int robotWidth = robotImage.width();
        int robotHeight = robotImage.height();
        painter.drawPixmap(-robotWidth / 2, -robotHeight / 2, robotImage);

        painter.restore();  // Restore the painter state
    }

    private:
        QPixmap robotImage;
        qreal headingAngle;

        void updateHeading() {
            // Simulate a heading change
            headingAngle += 1;
            if (headingAngle >= 360) {
                headingAngle -= 360;
            }

            // Trigger a repaint
            update();
        }
};




#endif