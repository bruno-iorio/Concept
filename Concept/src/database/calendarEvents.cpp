#include "precompiled.h"
#include "QxOrm_Impl.h"
#include "database/calendarEvents.h"

QX_REGISTER_CPP_QX_CONCEPTAPP(calendarEvents)

namespace qx {
    template <> void register_class(QxClass<calendarEvents> &t) {
        t.setName("calendarEvents");
	t.id(&Event::id, "id");
        t.data(&calendarEvent::name, "event");
        t.data(&calendarEvent::date, "event_date");
    }
}
