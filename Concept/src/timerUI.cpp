//timerUI.cpp

#include <QAction>
#include "timerUI.h"
#include <QDebug>
#include <QCursor>
#include <QQmlContext>
#include <iostream>
#include "QtQml/qqmlapplicationengine.h"
#include "studytimer.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QWidget>
#include <QMenu>




timerStart::timerStart(QObject *parent) :
        QObject(parent),
        startAction("Start", this), 
        pauseAction("Pause", this), 
        continueAction("Continue", this), 
        stopAction("Stop", this), 
        started(0),
        paused(0)

        {

        QAction *action15 = new QAction("15 Minutes", this);
        QAction *action30 = new QAction("30 Minutes", this);
        QAction *action45 = new QAction("45 Minutes", this);
        QAction *action60 = new QAction("1 Hour", this);
        QAction *action1 = new QAction("1 min", this);

        QAction *break5 = new QAction("5 Minutes", this);
        QAction *break10 = new QAction("10 Minutes", this);
        QAction *break15 = new QAction("15 Minutes", this);
        QAction *break20 = new QAction("20 Minutes", this);
        QAction *breakUntil = new QAction("Until continued", this);
        QAction *break10s = new QAction("10 Seconds", this);

        connect(&startAction, &QAction::triggered, this, &timerStart::startTheTimer);
        connect(&pauseAction, &QAction::triggered, this, &timerStart::pauseTimer);
        connect(&continueAction, &QAction::triggered, this, &timerStart::continueTimer);
        connect(&stopAction, &QAction::triggered, this, &timerStart::stopTimer);

        // connect(action25, &QAction::triggered, this, &timerStart::choose25);
        // connect(action30, &QAction::triggered, this, &timerStart::choose30);
        // connect(action45, &QAction::triggered, this, &timerStart::choose45);
        // connect(action60, &QAction::triggered, this, &timerStart::choose60);
        // connect(action1, &QAction::triggered, this, &timerStart::choose1);

        connect(action15, &QAction::triggered, this, [=]() { chooseTime(15); });
        connect(action30, &QAction::triggered, this, [=]() { chooseTime(30); });
        connect(action45, &QAction::triggered, this, [=]() { chooseTime(45); });
        connect(action60, &QAction::triggered, this, [=]() { chooseTime(60); });
        connect(action1, &QAction::triggered, this, [=]() { chooseTime(1); });

        // connect(break5, &QAction::triggered, this, &timerStart::chooseBreak5);
        // connect(break10, &QAction::triggered, this, &timerStart::chooseBreak10);
        // connect(break15, &QAction::triggered, this, &timerStart::chooseBreak15);
        // connect(break20, &QAction::triggered, this, &timerStart::chooseBreak20);
        connect(break5, &QAction::triggered, this, [=]() { chooseBreak(0, 5); });
        connect(break10, &QAction::triggered, this, [=]() { chooseBreak(0, 10); });
        connect(break15, &QAction::triggered, this, [=]() { chooseBreak(0, 15); });
        connect(break20, &QAction::triggered, this, [=]() { chooseBreak(0, 20); });
        connect(break10s, &QAction::triggered, this, [=]() { chooseBreak(10, 0); });
        connect(breakUntil, &QAction::triggered, this, &timerStart::chooseBreakUntil);

        q_timer = new QTimer(this);
        q_timer->start(1000);
        connect(q_timer, &QTimer::timeout, this, &timerStart::qTimerTimeout);
        connect(this, &timerStart::timerFinished, this, &timerStart::onTimerFinished);

        time_menu.addAction(action15);
        time_menu.addAction(action30);
        time_menu.addAction(action45);
        time_menu.addAction(action60);
        time_menu.addAction(action1);

        break_menu.addAction(break10s);
        break_menu.addAction(break5);
        break_menu.addAction(break10);
        break_menu.addAction(break15);
        break_menu.addAction(break20);
        break_menu.addAction(breakUntil);
        }

void startTimer(QApplication* app) {
qmlRegisterType<timerStart>("Custom Controls", 1, 0, "TimerStart");

QQmlApplicationEngine engine;
timerStart myTimerStart;
engine.rootContext()->setContextProperty("TimerStart", &myTimerStart);

engine.load(QUrl(QStringLiteral("qrc:/Main/main.qml")));
if (engine.rootObjects().isEmpty())
    exit(-1);

app->exec();
}

void timerStart::chooseTime(int minutes) {

    if (started) {
        emit timerFinished();
    }
    timer = CountDownTimer(0, minutes, 0);
    timer.countdowntimer = 1;
    time_string = createTimeString(timer.hour, timer.minute, timer.second);
    emit timeChanged();

}

/*
void timerStart::choose1() {
    timer = CountDownTimer(1, 0);
    countdowntimer = 1;
    time_string = createTimeString(timer.hour, timer.minute, timer.second);
    emit timeChanged();
}

void timerStart::choose25() {
    timer = CountDownTimer(25, 0);
    countdowntimer = 1;
    time_string = createTimeString(timer.hour, timer.minute, timer.second);
    emit timeChanged();
}

void timerStart::choose30() {
    timer = CountDownTimer(30, 0);
    countdowntimer = 1;
    time_string = createTimeString(timer.hour, timer.minute, timer.second);
    emit timeChanged();
}

void timerStart::choose45() {
    timer = CountDownTimer(45, 0);
    countdowntimer = 1;
    time_string = createTimeString(timer.hour, timer.minute, timer.second);
    emit timeChanged();
}

void timerStart::choose60() {
    timer = CountDownTimer(0, 1);
    countdowntimer = 1;
    time_string = createTimeString(timer.hour, timer.minute, timer.second);
    emit timeChanged();
}
*/

void timerStart::startTheTimer() {
    qDebug() << "starting timer";

    if (!started) {
    timer.counting = 1;
    started = 1;
    start_time = get_time();
    last_go_time = get_time(); }

    else {
        //emit errorMessage();
    }
}

bool timerStart::update_time(Timer &tim) {

    // qDebug() << "updating time";

    if (!tim.countdowntimer) {
        if (tim.second != 59) {tim.second ++;}
        else {tim.second = 0;
            if (tim.minute != 59) {tim.minute ++;}
            else {tim.minute = 0;
                tim.hour ++;}
        }   
    } else {
        if (tim.second != 0) {tim.second --;}
        else {tim.second = 59;
            if (tim.minute != 0) {tim.minute --;}
            else {tim.minute = 59;
                tim.hour --;}
        }
    }

    time_string = createTimeString(tim.hour, tim.minute, tim.second);
    emit timeChanged();

    if (tim.second == 0 && tim.minute == 0 && tim.hour == 0) {
        qDebug() << "timer zeroed";
        // if (break_timer.counting) {
        //     break_timer.counting = 0;
        //     if (started) {
        //         timer.counting = 1;
        //     }
        // } else {
        //     emit timerFinished();
        // }
        tim.counting = 0;
    }

    return tim.counting;
}

void timerStart::qTimerTimeout () {

    // qDebug() << "qTimerTimeout";
    // qDebug() << "timer.counting: " << timer.counting;

    if (timer.counting) {
        timer.counting = update_time(timer);
    }

    if (break_timer.counting) {
        break_timer.counting = update_time(break_timer);
        if (break_timer.counting == 0) {
            qDebug() << "break timer finished";
            break_timer = CountUpTimer();
            time_string = createTimeString(timer.hour, timer.minute, timer.second);
            continueTimer();
            emit timeChanged();        }
    }
}

void timerStart::showTimeMenu() {
    time_menu.exec(QCursor::pos());
}

void timerStart::showBreakMenu() {
    break_menu.exec(QCursor::pos());
}

void timerStart::chooseBreak(int s, int m) {
    pauseTimer();
    break_timer = CountDownTimer(s, m, 0);
    break_timer.counting = 1;
    time_string = createTimeString(break_timer.hour, break_timer.minute, break_timer.second);
    emit timeChanged();

    if (started == 0) {
        last_stop_time = timer.get_time();
    }
}
/*
void timerStart::chooseBreak5() {
    pauseTimer();
    break_timer = CountDownTimer(5, 0);
    time_string = createTimeString(break_timer.hour, break_timer.minute, break_timer.second);
    emit timeChanged();
    break_timer.counting = 1;
}

void timerStart::chooseBreak10() {
    break_timer = CountDownTimer(10, 0);
    time_string = createTimeString(break_timer.hour, break_timer.minute, break_timer.second);
    emit timeChanged();
    pauseTimer();
    break_timer.counting = 1;
}
void timerStart::chooseBreak15() {
    timer.counting = 0;
    break_timer = CountDownTimer(15, 0);
    time_string = createTimeString(break_timer.hour, break_timer.minute, break_timer.second);
    emit timeChanged();
    pauseTimer();
    break_timer.counting = 1;
}
void timerStart::chooseBreak20() {
    timer.counting = 0;
    break_timer = CountDownTimer(20, 0);
    time_string = createTimeString(break_timer.hour, break_timer.minute, break_timer.second);
    emit timeChanged();
    pauseTimer();
    break_timer.counting = 1;
}
*/

void timerStart::chooseBreakUntil() {
    pauseTimer();
    break_timer = CountUpTimer();
    break_timer.counting = 1;
    time_string = createTimeString(break_timer.hour, break_timer.minute, break_timer.second);
    emit timeChanged();

    if (started == 0) {
        last_stop_time = timer.get_time();
    }
}

void timerStart::pauseTimer() {

    if (started) {
    timer.counting = 0;
    last_stop_time = get_time();
    total_focus_time += difftime(last_stop_time, last_go_time);
    paused = 1;
    } else {
    //error
    }
}

void timerStart::continueTimer() {

        if (started) {
        timer.counting = 1;
        last_go_time = get_time();
        total_break_time += difftime(last_go_time, last_stop_time);
        paused = 0; }

        if (break_timer.counting) {
            break_timer.counting = 0;
            break_timer = CountUpTimer();
            time_string = createTimeString(timer.hour, timer.minute, timer.second);
            emit timeChanged();

            if (timer.counting == 0) {
                if (timer.hour == 0 && timer.minute == 0 && timer.second == 0) {
                    emit timerFinished();
                }
                else {
                    time_string = createTimeString(timer.hour, timer.minute, timer.second);
                }
            }
        }
    }

void timerStart::stopTimer() {
        emit timerFinished();
    }

void timerStart::onTimerFinished() {

        finishing_time = timer.get_time();

        if (started) {

            if (!paused) {
            total_focus_time += difftime(finishing_time, last_go_time);
            } else {
            total_break_time += difftime(finishing_time, last_stop_time);
            }
        }
        
        else if (break_timer.countdowntimer) {
            total_break_time = difftime(finishing_time, last_stop_time);
            total_focus_time = 0;
        }

        else {
            total_break_time = 0;
            total_focus_time = 0;
        }

        qDebug() << "focus: " << total_focus_time;
        qDebug() << "break: " << total_break_time;

        started = 0;
        timer.counting = 0;
        break_timer.counting = 0;
        timer = CountUpTimer();
        break_timer = CountUpTimer();
        time_string = createTimeString(0,0,0);
        emit timeChanged();

        //store total_focus_time and total_break_time here
	timerElements timerStats = timerElements();

	timerStats.totalFocusTime = total_focus_time;
	timerStats.totalBreakTime = total_break_time;
	timerStats.startTime = start_time;
        QSqlError daoError = qx::dao::insert(timerStats);


        paused = 0;
        total_focus_time = 0;
        total_break_time = 0;
        last_go_time = get_time();
        last_stop_time = get_time();
        start_time = get_time();
        finishing_time = get_time();

        qDebug() << "timer finished";

    }
