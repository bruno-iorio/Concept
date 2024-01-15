#ifndef EVENTCALENDAR_H
#define EVENTCALENDAR_H

#include <QMainWindow>
#include <QCalendarWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTextBrowser>

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

#endif // EVENTCALENDAR_H
