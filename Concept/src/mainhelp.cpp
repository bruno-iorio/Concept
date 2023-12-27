// mainhelp.cpp
#include "mainhelp.h"
#include <QAction>
#include <QCursor>
#include <QDebug>
#include <QQuickItem>

MainHelp::MainHelp(QQuickItem *parent) : QQuickItem(parent) {
    QAction *helpAction1 = new QAction("New Text Editor", this);
    QAction *helpAction2 = new QAction("2. Help Text 2", this);
    QAction *helpAction3 = new QAction("3. Help Text 3", this);

    connect(helpAction1, &QAction::triggered, this, &MainHelp::handleHelpAction1);  // Corrected connection
    connect(helpAction2, &QAction::triggered, this, &MainHelp::handleHelpAction2);
    connect(helpAction3, &QAction::triggered, this, &MainHelp::handleHelpAction3);

    helpMenu.addAction(helpAction1);
    helpMenu.addAction(helpAction2);
    helpMenu.addAction(helpAction3);
}

//void MainHelp::handleHelpAction1() {
//qDebug() << "New Text Editor requested!";}
    // Add your logic here to show the arrow or perform any other visual indication


void MainHelp::showHelpMenu() {
    // Show the context menu at the current cursor position
    helpMenu.exec(QCursor::pos());
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

void MainHelp::handleHelpAction1() {
    qDebug() << "New Text Editor requested!";

    // Emit the showRedSquare signal when the first option is selected
    emit showRedSquare();

    // Emit the signal to notify other components that the "New Text Editor" option is selected
    emit newEditorOptionSelected();
}

RedSquareManager::RedSquareManager(QObject *parent)
    : QObject(parent)
{
}

void RedSquareManager::showRedSquare()
{
    qDebug() << "Red Square requested!";
    // Add your logic here to display the red square
    // For simplicity, we'll emit a signal that will be connected to QML
    emit redSquareRequested();
}
