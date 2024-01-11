#ifndef CONCEPTAPP_FOLDERS_H
#define CONCEPTAPP_FOLDERS_H

#include "precompiled.h"

class Note;

class QX_CONCEPTAPP_DLL_EXPORT Folder {
public:
    typedef std::shared_ptr<Note> Note_ptr;
    typedef std::vector<Note_ptr> list_note;

    long id;
    QString name;

    list_note notes;

    Folder() : id(0) { ; }
    virtual ~Folder() { ; }
};

QX_REGISTER_HPP_QX_CONCEPTAPP(Folder, qx::trait::no_base_class_defined, 0)

typedef std::shared_ptr<Folder> Folder_ptr;
typedef std::vector<Folder_ptr> list_folder;

#endif //CONCEPTAPP_FOLDERS_H
