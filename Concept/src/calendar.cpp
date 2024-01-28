//calendar.cpp
#include "calendar.h"
#include <QVBoxLayout>
#include <QDate>
#include <QTextCharFormat>
#include <QMainWindow>
#include <QxOrm.h>
#include "database/calendarEvents.h"
#include <QDebug>
#include "QxOrm_Impl.h"

Calendar::Calendar(QWidget *parent) : QMainWindow(parent)
{
    calendarWidget = new QCalendarWidget(this);
    eventLineEdit = new QLineEdit(this);
    addButton = new QPushButton("Add Event", this);
    eventDisplay = new QScrollArea(this);
    layoutEvents = new QVBoxLayout(eventDisplay);

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

    this->initializeEvents();
    eventDisplay->show();
}

void Calendar::addEvent()
{
    QDate selectedDate = calendarWidget->selectedDate();
    QString eventText = eventLineEdit->text();
    
    if (!eventText.isEmpty())
    {
		calendarEvents e = calendarEvents();
    		e.eventName = eventText;
    		e.date = selectedDate;
    		e.id = qx::dao::count<calendarEvents>() + 1;
    		QSqlError daoError = qx::dao::insert(e);
		eventBox* x = new eventBox(eventDisplay, e);
		layoutEvents->addWidget(x);
    }

    
    eventLineEdit->clear();
}

void Calendar::initializeEvents(){
    QVector<calendarEvents> e;
    QSqlError fetchError = qx::dao::fetch_all(e);
    if(fetchError.isValid())
    {
	    return;
    }

    	for(calendarEvents eventinDB : e){
		
	    	qDebug() << eventinDB.id;
		eventBox* x = new eventBox(eventDisplay, eventinDB);
		layoutEvents->addWidget(x);
} 
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


eventBox::eventBox(QWidget *parent, calendarEvents event) : QWidget(parent){
    this->e = event;
    closeButton = new QPushButton("X", this);
    closeButton->setFixedSize(20, 20);

    connect(closeButton, &QPushButton::clicked, this, &eventBox::removeEventFromDatabase);
    connect(closeButton, &QPushButton::clicked, this, &QWidget::close); // Close the widget when closeButton is clicked

    QString name = QString("%1: %2").arg(e.date.toString("yyyy-MM-dd")).arg(e.eventName);
    title = new QLabel(name, this);
    title->setAlignment(Qt::AlignCenter);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(closeButton, 0, Qt::AlignTop | Qt::AlignRight);
    layout->addWidget(title, 1, Qt::AlignCenter);
    layout->setContentsMargins(0, 0, 0, 0);
}
void eventBox::removeEventFromDatabase(){
	 long id = e.id;
         QSqlError removeError = qx::dao::delete_by_id(e);
	 std::vector<calendarEvents> m;
	 QSqlError fetchError = qx::dao::fetch_all(m);
	 for(calendarEvents x : m){
		if(x.id >= id){
			x.id = x.id -1;
		}

	 }
    }
