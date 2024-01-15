#ifndef SETFOCUSPERIOD_H
#define SETFOCUSPERIOD_H

#include <QObject>
#include <QQuickItem>
#include <QMenu>
#include "studytimer.cpp"

class SetFocusPeriod : public QQuickItem {
    Q_OBJECT
    Q_PROPERTY(QString time READ getTime NOTIFY timeChanged)

public:
    SetFocusPeriod(QQuickItem *parent = nullptr);
    ~SetFocusPeriod();

    QString getTime() const;

signals:
    void timeChanged();

public slots:
    void showMenu();

private:
    QMenu menu;
    CountDownTimer* timer;
    QTimer q_timer;
    bool counting;

private slots:
    void handleTwentyFiveMinutes();
    void handleThirtyMinutes();
    void handleFourtyFiveMinutes();
    void handleOneHour();
    void handlePause();
    void handleStop();
    void handleContinue();
    void handleStart();
};

#endif // SETFOCUSPERIOD_H
