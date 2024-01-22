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
        countdowntimer(0),
        started(0)
        
        {

        QAction *action25 = new QAction("25 Minutes", this);
        QAction *action30 = new QAction("30 Minutes", this);
        QAction *action45 = new QAction("45 Minutes", this);
        QAction *action60 = new QAction("1 Hour", this);
        QAction *action1 = new QAction("1 min", this);

        connect(&startAction, &QAction::triggered, this, &timerStart::startTheTimer);
        connect(&pauseAction, &QAction::triggered, this, &timerStart::pauseTimer);
        connect(&continueAction, &QAction::triggered, this, &timerStart::continueTimer);
        connect(&stopAction, &QAction::triggered, this, &timerStart::stopTimer);

        connect(action25, &QAction::triggered, this, &timerStart::choose25);
        connect(action30, &QAction::triggered, this, &timerStart::choose30);
        connect(action45, &QAction::triggered, this, &timerStart::choose45);
        connect(action60, &QAction::triggered, this, &timerStart::choose60);
        connect(action1, &QAction::triggered, this, &timerStart::choose1);

        q_timer = new QTimer(this);
        q_timer->start(1000);
        connect(q_timer, &QTimer::timeout, this, &timerStart::updateTime);
        connect(this, &timerStart::timerFinished, this, &timerStart::onTimerFinished);

        menu.addAction(action25);
        menu.addAction(action30);
        menu.addAction(action45);
        menu.addAction(action60);
        menu.addAction(action1);
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


void timerStart::choose1() {
    timer = CountDownTimer(1, 0);
    countdowntimer = 1;
    time_string = createTimeString(timer.second,timer.minute,timer.hour);
    emit timeChanged();
}

void timerStart::choose25() {
    timer = CountDownTimer(25, 0);
    countdowntimer = 1;
    time_string = createTimeString(timer.second,timer.minute,timer.hour);
    emit timeChanged();
}

void timerStart::choose30() {
    timer = CountDownTimer(30, 0);
    countdowntimer = 1;
    time_string = createTimeString(timer.second,timer.minute,timer.hour);
    emit timeChanged();
}

void timerStart::choose45() {
    timer = CountDownTimer(45, 0);
    countdowntimer = 1;
    time_string = createTimeString(timer.second,timer.minute,timer.hour);
    emit timeChanged();
}

void timerStart::choose60() {
    timer = CountDownTimer(0, 1);
    countdowntimer = 1;
    time_string = createTimeString(timer.second,timer.minute,timer.hour);
    emit timeChanged();
}

void timerStart::startTheTimer() {
    timer.counting = 1;
    started = 1;
}

bool timerStart::update_time() {

    qDebug() << "updating time";

    if (!countdowntimer) {
        if (timer.second != 59) {timer.second ++;}
        else {timer.second = 0;
            if (timer.minute != 59) {timer.minute ++;}
            else {timer.minute = 0;
                timer.hour ++;}
        }
    }
    else {
        if (timer.second != 0) {timer.second --;}
        else {timer.second = 59;
            if (timer.minute != 0) {timer.minute --;}
            else {timer.minute = 59;
                timer.hour --;}
        }
    }

    total_time += 1;

    time_string = createTimeString(timer.hour, timer.minute, timer.second);
    emit timeChanged();

    if (timer.second == 0 && timer.minute == 0 && timer.hour == 0) {
        emit timerFinished();
    }

    return timer.counting;
}

void timerStart::updateTime () {
    if (timer.counting) {
        timer.counting = update_time();
    }
}

void timerStart::showMenu() {
    menu.exec(QCursor::pos());
}

void timerStart::pauseTimer() {
    timer.counting = 0;
    }


void timerStart::continueTimer() {
        if (started) {
        timer.counting = 1;}
    }

void timerStart::stopTimer() {
        emit timerFinished();
    }

void timerStart::onTimerFinished() {

        started = 0;
        timer.counting = 0;
        countdowntimer = 0;
        timer = CountUpTimer();
        time_string = createTimeString(0,0,0);
        emit timeChanged();
    }
