#ifndef INDICATOR_GUI_H_
#define INDICATOR_GUI_H_

#include <QWidget>

class indicators : public QWidget {
    Q_OBJECT

    public:
        explicit indicators(QWidget *parent = nullptr);
        ~indicators();

    private:


};

#endif