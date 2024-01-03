#include "setFocusPeriod.h"
#include <QAction>
#include <QDebug>
#include <QCursor>
#include <iostream>

SetFocusPeriod::SetFocusPeriod(QQuickItem *parent) : QQuickItem(parent) {
    QAction *action25 = new QAction("25 Minutes", this);
    QAction *action30 = new QAction("30 Minutes", this);
    QAction *action45 = new QAction("45 Minutes", this);
    QAction *action60 = new QAction("1 Hour", this);

    connect(action25, &QAction::triggered, this, &SetFocusPeriod::handleTwentyFiveMinutes);
    connect(action30, &QAction::triggered, this, &SetFocusPeriod::handleThirtyMinutes);
    connect(action45, &QAction::triggered, this, &SetFocusPeriod::handleFourtyFiveMinutes);
    connect(action60, &QAction::triggered, this, &SetFocusPeriod::handleOneHour);
    // connect(this, &SetFocusPeriod::clicked, this, &SetFocusPeriod::showMenu);

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

void SetFocusPeriod::showMenu() {
    std::cout << "I want to open the menu for focus" << std::endl;
    menu.exec(QCursor::pos());
}

void SetFocusPeriod::handleTwentyFiveMinutes() {
    qDebug() << "Selected: 25 Minutes";
}

void SetFocusPeriod::handleThirtyMinutes() {
    qDebug() << "Selected: 30 Minutes";
}

void SetFocusPeriod::handleFourtyFiveMinutes() {
    qDebug() << "Selected: 45 Minutes";
}

void SetFocusPeriod::handleOneHour() {
    qDebug() << "Selected: 1 Hour";
}

SetFocusPeriod::~SetFocusPeriod() {
}
