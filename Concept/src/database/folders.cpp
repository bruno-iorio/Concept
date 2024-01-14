#include "precompiled.h"

#include "database/notes.h"
#include "database/folders.h"

#include "QxOrm_Impl.h"

QX_REGISTER_CPP_QX_CONCEPTAPP(Folder)

namespace qx {
    template <> void register_class(QxClass<Folder> &t) {
        t.setName("t_folders");

        t.id(&Folder::id, "id");
        t.data(&Folder::name, "name");

        t.relationOneToMany(&Folder::notes, "notes", "folder_id");
    }
}
