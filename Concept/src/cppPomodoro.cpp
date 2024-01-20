#include "includes/cppPomodoro.h"

Pomodoro::Pomodoro(QWidget *parent) : QWidget(parent) {
    studyTimerBlock = new QWidget(this);
    studyTimerBlock->resize(parent->width(), parent->height() * 0.30);
    studyTimerBlock->move(0, 0);
    studyTimerBlock->setStyleSheet("background-color: #FFFFFF;");

    studyTimerText = new QLabel(this);
    studyTimerText->setText("Study Timer");
    studyTimerText->setFont(QFont("Helvetica", studyTimerBlock->height() * 0.17));
    studyTimerText->setStyleSheet("color: #000000;");

    timerBlock = new QWidget(this);
    timerBlock->resize(parent->width(), parent->height() * 0.15);
    timerBlock->move(0, studyTimerBlock->height());
    timerBlock->setStyleSheet("background-color: #c4c8cc;");

    studyButton = new QPushButton(this);
    spacerButtonsTimerBlock = new QWidget(this);
    breakButton = new QPushButton(this);

    rowLayout = new QVBoxLayout(this);
    rowLayout->addWidget(studyButton);
    rowLayout->addWidget(spacerButtonsTimerBlock);
    rowLayout->addWidget(breakButton);

    studyButton->setText("Start");
    studyButton->setFont(QFont("Helvetica", timerBlock->height() * 0.15));
    studyButton->setStyleSheet("background-color: #738290;");
    studyButton->setFixedWidth(timerBlock->width() / 2);

    spacerButtonsTimerBlock->setStyleSheet("background-color: #FFFFFF;");
    spacerButtonsTimerBlock->setFixedWidth(timerBlock->width() * 0.003);
    spacerButtonsTimerBlock->setFixedHeight(timerBlock->height());

    breakButton->setText("Continue");
    breakButton->setFont(QFont("Helvetica", timerBlock->height() * 0.15));
    breakButton->setStyleSheet("background-color: #738290;");
    breakButton->setFixedWidth(timerBlock->width() / 2 - spacerButtonsTimerBlock->width());
    // breakButton.top = studyButton->top
    breakButton->move(studyButton->width() + spacerButtonsTimerBlock->width(), studyButton->y());
}