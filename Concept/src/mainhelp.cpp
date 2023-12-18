// mainhelp.cpp
#include "mainhelp.h"
#include <QAction>
#include <QCursor>
#include <QDebug>

MainHelp::MainHelp(QQuickItem *parent) : QQuickItem(parent) {
    QAction *helpAction1 = new QAction("1. Help Text 1", this);
    QAction *helpAction2 = new QAction("2. Help Text 2", this);
    QAction *helpAction3 = new QAction("3. Help Text 3", this);

    connect(helpAction1, &QAction::triggered, this, &MainHelp::handleHelpAction1);
    connect(helpAction2, &QAction::triggered, this, &MainHelp::handleHelpAction2);
    connect(helpAction3, &QAction::triggered, this, &MainHelp::handleHelpAction3);

    helpMenu.addAction(helpAction1);
    helpMenu.addAction(helpAction2);
    helpMenu.addAction(helpAction3);
}

void MainHelp::showHelpMenu() {
    // Show the context menu at the current cursor position
    helpMenu.exec(QCursor::pos());
}

void MainHelp::handleHelpAction1() {
    qDebug() << "Help Text 1 clicked!";
    // Add your logic here
}

void MainHelp::handleHelpAction2() {
    qDebug() << "Help Text 2 clicked!";
    // Add your logic here
}

void MainHelp::handleHelpAction3() {
    qDebug() << "Help Text 3 clicked!";
    // Add your logic here
}

MainHelp::~MainHelp() {
    // Perform cleanup or resource release here, if needed
}
