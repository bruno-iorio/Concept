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

using namespace std;

class timerStart : public QObject
{
    Q_OBJECT
public:

    timerStart(QObject *parent = nullptr);

    Timer timer = CountUpTimer();
    Timer break_timer = CountUpTimer();

    QString time_string = "00:00";


    Q_INVOKABLE QString get_time_string() const {
        qDebug() << "getting time string";
        return time_string;
    }

    Q_INVOKABLE void chooseBreakUntil();
    Q_INVOKABLE void chooseBreak(int s, int m);
    Q_INVOKABLE void chooseTime(int m);

    time_t start_time;
    time_t last_go_time;
    time_t last_stop_time;
    time_t finishing_time;
    QTime Today;
    double total_focus_time = 0;
    double total_break_time = 0;

signals:
    void timeChanged();
    void timerFinished();

public slots:
    void showTimeMenu();
    void showBreakMenu();
    void startTheTimer();
    void pauseTimer();
    void continueTimer();
    void stopTimer();
    void onTimerFinished();
    void qTimerTimeout();

private:

    time_t get_time() { //for storing system time
        std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();
        time_t currentTime_t = std::chrono::system_clock::to_time_t(currentTime);
        return currentTime_t;
    } 

    bool update_time(Timer &timer);

    QString createTimeString(int hours, int minutes, int seconds) {
        QString timeString = "";
        if (break_timer.counting) {
            timeString = "Break: ";
        }
        if (hours != 0) {
            timeString += QString("%1:%2:%3").arg(hours, 2, 10, QChar('0')).arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
        } else {
            timeString += QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
        }
        return timeString;
        }



    bool started;
    bool paused;

    QAction startAction;
    QAction pauseAction;
    QAction continueAction;
    QAction stopAction;
    QAction action15;
    QAction action30;
    QAction action45;
    QAction action60;
    QAction action1;
    QAction break5;
    QAction break10;
    QAction break15;
    QAction break20;
    QAction breakUntil;
    QAction break10s;


    QMenu time_menu;
    QMenu break_menu;
    QTimer *q_timer;
};

void startTimer(QApplication* app);

#endif // TIMERUI_H
