//setFocusPeriod.h
#ifndef SETFOCUSPERIOD_H
#define SETFOCUSPERIOD_H

#include <QObject>
#include <QQuickItem>
#include <QMenu>
#include "QtCore/qtimer.h"
#include "studytimer.h"
#include "timerUI.h"

class SetFocusPeriod : public QQuickItem {
    Q_OBJECT
    Q_PROPERTY(QString time READ getTime NOTIFY timeChanged)

public:
    SetFocusPeriod(QQuickItem *parent = nullptr);
    ~SetFocusPeriod();
signals:
    void timeChanged();
    void setTime(const QString &time);

public slots:
    void showMenu();
    Q_INVOKABLE void handleStop();
    Q_INVOKABLE void handleStart();
    Q_INVOKABLE QString getTime() const;

private:
    QMenu menu;
    CountDownTimer timer = CountDownTimer(0, 0);
    QTimer q_timer;
    bool counting;

private slots:
    void handleTwentyFiveMinutes();
    void handleThirtyMinutes();
    void handleFourtyFiveMinutes();
    void handleOneHour();
    void handlePause();
    void handleTimeout();
    void handleContinue();


};

#endif // SETFOCUSPERIOD_H
