#ifndef SETFOCUSPERIOD_H
#define SETFOCUSPERIOD_H

#include <QObject>
#include <QQuickItem>
#include <QMenu>

class SetFocusPeriod : public QQuickItem {
    Q_OBJECT

public:
    SetFocusPeriod(QQuickItem *parent = nullptr);
    ~SetFocusPeriod();

public slots:
    void showMenu();

private:
    QMenu menu;

private slots:
    void handleTwentyFiveMinutes();
    void handleThirtyMinutes();
    void handleFourtyFiveMinutes();
    void handleOneHour();
};

#endif // SETFOCUSPERIOD_H
