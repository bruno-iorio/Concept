#include "precompiled.h"

#include "database/notes.h"
#include "database/folders.h"

#include "QxOrm_Impl.h"

QX_REGISTER_CPP_QX_CONCEPTAPP(Note)

namespace qx {
    template <> void register_class(QxClass<Note> &t) {
        t.setName("t_notes");

        t.id(& Note::id, "id");

        t.data(& Note::title, "title");
        t.data(& Note::content, "content");
        t.data(& Note::last_modified, "last_modified");

        t.relationManyToOne(&Note::folder, "folder_id");
    }
}
