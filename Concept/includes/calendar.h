#ifndef EVENTCALENDAR_H
#define EVENTCALENDAR_H

#include <QMainWindow>
#include <QCalendarWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTextBrowser>
#include <QObject>

class Calendar : public QMainWindow {
    Q_OBJECT

public:
    Calendar(QWidget *parent = nullptr);

private slots:
    void addEvent();

private:
    QCalendarWidget *calendarWidget;
    QLineEdit *eventLineEdit;
    QPushButton *addButton;
    QTextBrowser *eventDisplay;

};

class CalendarQML : public QObject {
    Q_OBJECT
public:
    CalendarQML(QObject *parent = nullptr);

public slots:
    void showCalendar();

private:
    Calendar *myCalendar;

signals:
    void File();
};


#endif // EVENTCALENDAR_H
