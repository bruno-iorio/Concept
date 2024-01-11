#include "QxOrm.h"
#include "database/focus_time.h"
#include "QxOrm_Impl.h"

QX_REGISTER_CPP(FocusTime)

namespace qx {
    template <> void register_class(QxClass<FocusTime> &t) {
        t.setName("t_focus_time");

        t.id(&FocusTime::id, "id");
        t.data(&FocusTime::start_time, "start_time");
        t.data(&FocusTime::end_time, "end_time");
        t.data(&FocusTime::time_spent, "time_spent");
    }
}
