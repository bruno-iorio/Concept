#ifndef CALENDAR_EVENTS_H
#define CALENDAR_EVENTS_H
#include<QString>
#include <QDate>
#include "precompiled.h"


class QX_CONCEPTAPP_DLL_EXPORT  calendarEvents{
	public:
		long id{0};
		QDate date;
		QString eventName;

};

    typedef std::shared_ptr<calendarEvents> event_ptr;
    typedef std::vector<event_ptr> list_event;
    QX_REGISTER_HPP_QX_CONCEPTAPP(calendarEvents, qx::trait::no_base_class_defined, 0)


#endif
