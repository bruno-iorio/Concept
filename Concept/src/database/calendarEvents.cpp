#include "precompiled.h"
#include "QxOrm_Impl.h"
#include "database/calendarEvents.h"

QX_REGISTER_CPP_QX_CONCEPTAPP(calendarEvents)

namespace qx {
    template <> void register_class(QxClass<calendarEvents> &t) {
        t.setName("calendarEvents");
	t.id(&calendarEvents::id, "id");
        t.data(&calendarEvents::eventName, "name");
        t.data(&calendarEvents::date, "event_date");
    }
}
