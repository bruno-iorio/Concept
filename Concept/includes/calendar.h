// calendar.h

#ifndef EVENTCALENDAR_H
#define EVENTCALENDAR_H

#include <QMainWindow>
#include <vector>
#include <QScrollArea>
#include <QCalendarWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTextBrowser>
#include <QObject>
#include <QVBoxLayout>
#include <QLabel>
#include "database/calendarEvents.h"
#include <QVector>
class Calendar : public QMainWindow {
    Q_OBJECT

public:
    Calendar(QWidget *parent = nullptr);
    void initializeEvents();

public slots:
    void addEvent();
    void closeCalendar();
    void closeCalendarFromButton();

private:
    QCalendarWidget *calendarWidget;
    QLineEdit *eventLineEdit;
    QPushButton *addButton;
    QScrollArea *eventDisplay;
    QVBoxLayout *layoutEvents;

signals:
    void calendarClosed();
};


class CalendarQML : public QObject {
    Q_OBJECT
public:
    CalendarQML(QObject *parent = nullptr);
public slots:
    void showCalendar();
    void closeCalendarFromQML();  // New slot to close the calendar from QML
private:
    Calendar *myCalendar;
signals:
    void File();
};





class eventBox : public QWidget {
public:
    eventBox(QWidget *parent = nullptr,calendarEvents event = calendarEvents());
    void removeEventFromDatabase();
private:

    calendarEvents e;
    QPushButton* closeButton;
    QLabel* title;

};

#endif // EVENTCALENDAR_H
