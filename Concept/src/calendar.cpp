//calendar.cpp
#include "../includes/calendar.h"
#include <QVBoxLayout>
#include <QDate>
#include <QTextCharFormat>
#include <QMainWindow>

Calendar::Calendar(QWidget *parent) : QMainWindow(parent)
{
    calendarWidget = new QCalendarWidget(this);
    eventLineEdit = new QLineEdit(this);
    addButton = new QPushButton("Add Event", this);
    eventDisplay = new QTextBrowser(this);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(calendarWidget);
    layout->addWidget(eventLineEdit);
    layout->addWidget(addButton);
    layout->addWidget(eventDisplay);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    connect(addButton, SIGNAL(clicked()), this, SLOT(addEvent()));

    setWindowTitle("Event Calendar");

    connect(this, SIGNAL(destroyed(QObject*)), this, SLOT(closeCalendar()));

    setGeometry(50, 100, 200, 300);
}

void Calendar::addEvent()
{
    QDate selectedDate = calendarWidget->selectedDate();
    QString eventText = eventLineEdit->text();

    if (!eventText.isEmpty())
    {
        QString currentText = eventDisplay->toPlainText();
        currentText += QString("%1: %2\n").arg(selectedDate.toString("yyyy-MM-dd")).arg(eventText);
        eventDisplay->setText(currentText);
    }

    eventLineEdit->clear();
}

CalendarQML::CalendarQML(QObject *parent) : QObject(parent)
{
    this->myCalendar = new Calendar();
}

void CalendarQML::showCalendar()
{
    myCalendar->show();
}

void Calendar::closeCalendar() {
    emit calendarClosed();
}

void CalendarQML::closeCalendarFromQML() {
    myCalendar->close();  // Close the calendar window
}

void Calendar::closeCalendarFromButton() {
    close();  // Close the calendar window
}
