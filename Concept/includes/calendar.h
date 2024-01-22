// calendar.h

#ifndef EVENTCALENDAR_H
#define EVENTCALENDAR_H

#include <QMainWindow>
#include <QCalendarWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTextBrowser>
#include <QObject>
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
    QTextBrowser *eventDisplay;
    QVector<calendarEvents> eventList;
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


#endif // EVENTCALENDAR_H
