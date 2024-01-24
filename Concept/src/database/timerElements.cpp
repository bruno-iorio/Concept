#include "precompiled.h"
#include "database/timerElements.h"

#include "QxOrm_Impl.h"

QX_REGISTER_CPP_QX_CONCEPTAPP(timerElements)

namespace qx {
    template <> void register_class(QxClass<timerElements> &t) {
        t.setName("timerElements");

        t.id(&timerElements::id, "id");
        t.data(&timerElements::creationDate, "creationDate");

    }
}
