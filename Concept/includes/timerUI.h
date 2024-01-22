//timerUI.h
#ifndef TIMERUI_H
#define TIMERUI_H

#include <QObject>
#include <QQuickItem>
#include <QGuiApplication>
#include <QWidget>
#include <QMenu>
#include "QtCore/qtimer.h"
#include "studytimer.h"
#include <QAction>
#include <QApplication>
#include <chrono>
#include <thread>
#include <ctime>
#include <QObject>
#include <QTimer>

class timerStart : public QObject
{
    Q_OBJECT
public:

    timerStart(QObject *parent = nullptr);

    Timer timer = CountUpTimer();
    //CountDownTimer timerDown = CountDownTimer(0, 0);
    QString time_string = "00:00";
    bool countdowntimer;
    int total_time = 0;

    Q_INVOKABLE QString get_time_string() const {
        qDebug() << "getting time string";
        return time_string;
    }

    Q_INVOKABLE void choose25();
    Q_INVOKABLE void choose30();
    Q_INVOKABLE void choose45();
    Q_INVOKABLE void choose60();
    Q_INVOKABLE void choose1();

signals:
    void timeChanged();
    void timerFinished();
    void timerStopped();
    void timerPaused();
    void timerContinued();
    void timerStarted();

public slots:
    void showMenu();
    void startTheTimer();
    void pauseTimer();
    void continueTimer();
    void stopTimer();
    void onTimerFinished();
    void updateTime();

private:

    void activeCounting() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        update_time();
    }

    bool update_time();

    QString createTimeString(int hours, int minutes, int seconds) {
    QString timeString;
    if (hours != 0) {
        timeString = QString("%1:%2:%3").arg(hours, 2, 10, QChar('0')).arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
    } else {
        timeString = QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
    }
    return timeString;
    }

    bool started;

    QAction startAction;
    QAction pauseAction;
    QAction continueAction;
    QAction stopAction;
    QAction action25;
    QAction action30;
    QAction action45;
    QAction action60;
    QMenu menu;
    QTimer *q_timer;
};

void startTimer(QApplication* app);

#endif // TIMERUI_H
