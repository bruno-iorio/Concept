//setFocusPeriod.cpp

#include "setFocusPeriod.h"
#include <QAction>
#include <QDebug>
#include <QCursor>
#include <iostream>
#include "QtQml/qqmlapplicationengine.h"
#include "studytimer.h"
#include "timerUI.h"
#include <QQmlContext>




SetFocusPeriod::SetFocusPeriod(QQuickItem *parent) : QQuickItem(parent) {

    //timer->setInterval(1000); // 1 second

    QAction *action25 = new QAction("25 Minutes", this);
    QAction *action30 = new QAction("30 Minutes", this);
    QAction *action45 = new QAction("45 Minutes", this);
    QAction *action60 = new QAction("1 Hour", this);

    QAction *actionPause = new QAction("Pause", this);
    QAction *actionStop = new QAction("Stop", this);
    QAction *actionContinue = new QAction("Continue", this);
    QAction *actionStart = new QAction("Start", this);

    connect(action25, &QAction::triggered, this, &SetFocusPeriod::handleTwentyFiveMinutes);
    connect(action30, &QAction::triggered, this, &SetFocusPeriod::handleThirtyMinutes);
    connect(action45, &QAction::triggered, this, &SetFocusPeriod::handleFourtyFiveMinutes);
    connect(action60, &QAction::triggered, this, &SetFocusPeriod::handleOneHour);
    // connect(this, &SetFocusPeriod::clicked, this, &SetFocusPeriod::showMenu);

    connect(&q_timer, &QTimer::timeout, this, &SetFocusPeriod::handleTimeout);

    menu.addAction(action25);
    menu.addAction(action30);
    menu.addAction(action45);
    menu.addAction(action60);

}

//void SetFocusPeriod::mousePressEvent(QMouseEvent *event) {
// Emit the clicked signal when the mouse is pressed
//emit clicked();
//QQuickItem::mousePressEvent(event);
//}

QString SetFocusPeriod::getTime() const   {
    return QString("%1:%2:%3").arg(timer.hour, 2, 10, QChar('0')).arg(timer.minute, 2, 10, QChar('0')).arg(timer.second, 2, 10, QChar('0'));
}


void SetFocusPeriod::handleTimeout() {
    if (counting) {
        counting = timer.update_timer();
        if (timer.finished) {
            handleStop();
        }
        emit timeChanged();
        emit setTime(getTime());  // Emit a signal to notify the change in time
    }
}


void SetFocusPeriod::showMenu() {
    std::cout << "I want to open the menu for focus" << std::endl;
    menu.exec(QCursor::pos());
}

void SetFocusPeriod::handleTwentyFiveMinutes() {
    emit timeChanged();

}

void SetFocusPeriod::handleThirtyMinutes() {
    emit timeChanged();
}

void SetFocusPeriod::handleFourtyFiveMinutes() {
    emit timeChanged();
}

void SetFocusPeriod::handleOneHour() {
    emit timeChanged();
}

void SetFocusPeriod::handleStart() {
    if (timer.minute > 0 || timer.hour > 0) {
        counting = true;
        q_timer.start(1000);

        // Emit a signal to update the timer display immediately
        emit timeChanged();
        emit setTime(getTime());
    } else {
        qDebug() << "Focus period not set. Please select a focus period.";
    }
}

void SetFocusPeriod::handlePause() {
    timer.userPause();
}

void SetFocusPeriod::handleStop() {
    counting = false;
    q_timer.stop();
    emit timeChanged();
}


void SetFocusPeriod::handleContinue() {
    timer.userContinue();
}

SetFocusPeriod::~SetFocusPeriod() {}

