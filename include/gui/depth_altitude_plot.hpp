#ifndef DEPTH_ALTITUDE_PLOT_HPP_
#define DEPTH_ALTITUDE_PLOT_HPP_

#include <QWidget>
#include <QVBoxLayout>
#include <QTimer>
#include "qcustomplot.h" // Include QCustomPlot library
#include <deque>
#include <chrono>
#include <iostream>


class DepthPlotWidget : public QWidget {
    Q_OBJECT

public:
    explicit DepthPlotWidget(double windowDuration = 60.0, QWidget *parent = nullptr)
        : QWidget(parent),
          plot(new QCustomPlot(this)),
          timer(new QTimer(this)),
          windowDuration(windowDuration),
          depthHoldActive(false),
          altitudeHoldActive(false),
          depthHoldValue(0),
          altitudeHoldValue(0)
    {
        // Set up the layout
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(plot);
        setLayout(layout);

        // Set up QCustomPlot
        plot->addGraph(); // Main data graph for depth
        plot->graph(0)->setName("Depth");
        plot->xAxis->setLabel("Time (s)");
        plot->yAxis->setLabel("Depth (m)");
        plot->xAxis->setRange(0, windowDuration);
        plot->yAxis->setRange(0, 100); // Initial range for depth, dynamically adjusted
        plot->yAxis->setRangeReversed(true); // Reverse the y-axis for depth
        plot->graph(0)->setPen(QPen(Qt::blue, 2, Qt::SolidLine)); // Blue solid line for depth
        plot->graph(0)->setName("Depth");

        // Add the second y-axis for altitude
        QCPAxis *rightAxis = plot->yAxis2; // Use the default right y-axis
        rightAxis->setVisible(true);      // Ensure it's visible
        rightAxis->setLabel("Altitude (m)");
        rightAxis->setRange(0, 10);       // Initial range for altitude
        //plot->axisRect()->addAxis(QCPAxis::atRight);
        //QCPAxis *rightAxis = plot->axisRect()->axis(QCPAxis::atRight);
        rightAxis->setVisible(true);

        // Add a second graph for altitude, linked to the right y-axis
        plot->addGraph(plot->xAxis, rightAxis);
        plot->graph(1)->setName("Altitude");
        plot->graph(1)->setPen(QPen(Qt::red, 2, Qt::SolidLine)); // Blue solid line for depth

        // Enable and configure the legend
        plot->legend->setVisible(true);
        plot->legend->setFont(QFont("Helvetica", 9));
        plot->legend->setBrush(QBrush(QColor(255, 255, 255, 150))); // Semi-transparent white background
        plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop | Qt::AlignLeft);

        // Set decimal precision
        plot->yAxis->setNumberPrecision(1); // One decimal place
        plot->yAxis->setNumberFormat("f");  // Fixed-point notation (no scientific notation)

        // Set fixed number of decimals for altitude (right y-axis)
        plot->yAxis2->setNumberPrecision(1); // One decimal place
        plot->yAxis2->setNumberFormat("f");  // Fixed-point notation (no scientific notation)

        // Depth Hold
        plot->addGraph(); // Depth hold indicator
        plot->graph(2)->setPen(QPen(Qt::blue, 2, Qt::DashLine)); // Blue dashed line for depth hold
        plot->graph(2)->setName("Depth Setpoint");

        // Altitude Hold
        plot->addGraph(plot->xAxis, rightAxis);
        plot->graph(3)->setPen(QPen(Qt::red, 2, Qt::DashLine)); // Red dashed line for altitude hold
        plot->graph(3)->setName("Altitude Setpoint");


        // Timer to refresh the plot
        connect(timer, &QTimer::timeout, this, &DepthPlotWidget::updatePlot);
        timer->start(200); // Refresh every 200 ms
    }

    void addDepthData(double depth) {
        double currentTime = getCurrentTimeInSeconds();

        // Add depth data
        depthValues.push_back(depth);
        depthTimestamps.push_back(currentTime);

        // Remove old depth data outside the time window
        while (!depthTimestamps.empty() && (currentTime - depthTimestamps.front()) > windowDuration) {
            depthTimestamps.pop_front();
            depthValues.pop_front();
        }
    }

    void addAltitudeData(double altitude) {
        double currentTime = getCurrentTimeInSeconds();

        // Add altitude data
        altitudeValues.push_back(altitude);
        altitudeTimestamps.push_back(currentTime);

        // Remove old altitude data outside the time window
        while (!altitudeTimestamps.empty() && (currentTime - altitudeTimestamps.front()) > windowDuration) {
            altitudeTimestamps.pop_front();
            altitudeValues.pop_front();
        }
    }

    void setDepthHold(double depth) {
        depthHoldActive = true;
        depthHoldValue = depth;
        updatePlot();
    }

    void clearDepthHold() {
        depthHoldActive = false;
        updatePlot();
    }

    void setAltitudeHold(double depth) {
        altitudeHoldActive = true;
        altitudeHoldValue = depth;
        updatePlot();
    }

    void clearAltitudeHold() {
        altitudeHoldActive = false;
        updatePlot();
    }

private slots:
    void updatePlot() {
        if (depthTimestamps.empty() && altitudeTimestamps.empty()) return;

        // Prepare depth data for QCustomPlot
        QVector<double> xDepth, yDepth;
        if (!depthTimestamps.empty()) {
            double relativeStartTime = depthTimestamps.front();
            for (size_t i = 0; i < depthTimestamps.size(); ++i) {
                xDepth.append(depthTimestamps[i] - relativeStartTime);
                yDepth.append(depthValues[i]);
            }
        }

        // Update depth graph
        plot->graph(0)->setData(xDepth, yDepth);

        // Dynamically adjust depth y-axis range
        if (!depthValues.empty()) {
            double minDepth = *std::min_element(depthValues.begin(), depthValues.end());
            double maxDepth = *std::max_element(depthValues.begin(), depthValues.end());
            double depthPadding = (maxDepth - minDepth) * 0.1; // 10% padding
            if (depthPadding == 0) depthPadding = 1.0; // Ensure non-zero padding for constant values
            plot->yAxis->setRange(maxDepth + depthPadding, minDepth - depthPadding);
        }

        // Prepare altitude data for QCustomPlot
        QVector<double> xAltitude, yAltitude;
        if (!altitudeTimestamps.empty()) {
            double relativeStartTime = altitudeTimestamps.front();
            for (size_t i = 0; i < altitudeTimestamps.size(); ++i) {
                xAltitude.append(altitudeTimestamps[i] - relativeStartTime);
                yAltitude.append(altitudeValues[i]);
            }
        }

        // Update altitude graph
        plot->graph(1)->setData(xAltitude, yAltitude);

        // Dynamically adjust altitude y-axis range
        if (!altitudeValues.empty()) {
            double minAltitude = *std::min_element(altitudeValues.begin(), altitudeValues.end());
            double maxAltitude = *std::max_element(altitudeValues.begin(), altitudeValues.end());
            double altitudePadding = (maxAltitude - minAltitude) * 0.1; // 10% padding
            if (altitudePadding == 0) altitudePadding = 1.0; // Ensure non-zero padding for constant values
            plot->axisRect()->axis(QCPAxis::atRight)->setRange(minAltitude - altitudePadding, maxAltitude + altitudePadding);
        }

        // Update depth hold
        if (depthHoldActive) {
            QVector<double> holdX, holdY;
            holdX.append(0); // Start of the x-axis range
            holdX.append(windowDuration); // End of the x-axis range
            holdY.append(depthHoldValue);
            holdY.append(depthHoldValue);

            plot->graph(2)->setData(holdX, holdY); // Update the depth hold indicator
            plot->graph(2)->setVisible(true); // Ensure the graph is visible
        } else {
            plot->graph(2)->setVisible(false); // Hide the depth hold graph
        }

        // Update altitude hold
        if (altitudeHoldActive) {
            QVector<double> holdX, holdY;
            holdX.append(0); // Start of the x-axis range
            holdX.append(windowDuration); // End of the x-axis range
            holdY.append(altitudeHoldValue);
            holdY.append(altitudeHoldValue);

            plot->graph(3)->setData(holdX, holdY); // Update the depth hold indicator
            plot->graph(3)->setVisible(true); // Ensure the graph is visible
        } else {
            plot->graph(3)->setVisible(false); // Hide the depth hold graph
        }

        // Replot the graph
        plot->replot();
    }

private:
    QCustomPlot *plot;
    QTimer *timer;
    double windowDuration;

    std::deque<double> depthValues;
    std::deque<double> depthTimestamps;

    std::deque<double> altitudeValues;
    std::deque<double> altitudeTimestamps;

    bool depthHoldActive;
    double depthHoldValue;

    bool altitudeHoldActive;
    double altitudeHoldValue;

    double getCurrentTimeInSeconds() {
        auto now = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
        return duration.count() / 1000.0;
    }
};

#endif