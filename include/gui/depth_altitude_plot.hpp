#ifndef DEPTH_ALTITUDE_PLOT_HPP_
#define DEPTH_ALTITUDE_PLOT_HPP_

#include <QWidget>
#include <QVBoxLayout>
#include <QTimer>
#include "qcustomplot.h" // Include QCustomPlot library
#include <deque>
#include <chrono>

class DepthPlotWidget : public QWidget {
    Q_OBJECT

public:
    explicit DepthPlotWidget(double windowDuration = 10.0, QWidget *parent = nullptr)
        : QWidget(parent),
          plot(new QCustomPlot(this)),
          timer(new QTimer(this)),
          windowDuration(windowDuration) 
    {
        // Set up the layout
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(plot);
        setLayout(layout);

        // Set up QCustomPlot
        plot->addGraph();
        plot->xAxis->setLabel("Time (s)");
        plot->yAxis->setLabel("Depth (m)");
        plot->xAxis->setRange(0, windowDuration);
        plot->yAxis->setRange(0, 100); // Adjust as needed for depth range

        // Timer to refresh the plot
        connect(timer, &QTimer::timeout, this, &DepthPlotWidget::updatePlot);
        timer->start(50); // Refresh every 50 ms
    }

    void addData(double depth) {
        double currentTime = getCurrentTimeInSeconds();

        // Add new data
        depthValues.push_back(depth);
        timestamps.push_back(currentTime);

        // Remove old data outside the time window
        while (!timestamps.empty() && (currentTime - timestamps.front()) > windowDuration) {
            timestamps.pop_front();
            depthValues.pop_front();
        }
    }

private slots:
    void updatePlot() {
        if (timestamps.empty()) return;

        // Prepare data for QCustomPlot
        QVector<double> xData, yData;
        double relativeStartTime = timestamps.front();

        for (size_t i = 0; i < timestamps.size(); ++i) {
            xData.append(timestamps[i] - relativeStartTime);
            yData.append(depthValues[i]);
        }

        // Update the graph
        plot->graph(0)->setData(xData, yData);
        plot->replot();
    }

private:
    QCustomPlot *plot;
    QTimer *timer;
    double windowDuration;
    std::deque<double> depthValues;
    std::deque<double> timestamps;

    double getCurrentTimeInSeconds() {
        auto now = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
        return duration.count() / 1000.0;
    }
};

#endif