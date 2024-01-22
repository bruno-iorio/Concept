#ifndef CONCEPTAPP_NOTES_H
#define CONCEPTAPP_NOTES_H

#include "precompiled.h"


class Folder;

class QX_CONCEPTAPP_DLL_EXPORT Note {
public:
    typedef std::shared_ptr<Folder> Folder_ptr;

    long id;

    QString title;
    QString content;
    QDateTime last_modified;

    Folder_ptr folder;

    Note() : id(0) { ; }
    virtual ~Note() { ; }


    void rename(const QString& newTitle) {
        title = newTitle;
        last_modified = QDateTime::currentDateTime(); // Update last_modified timestamp
    }

};

QX_REGISTER_HPP_QX_CONCEPTAPP(Note, qx::trait::no_base_class_defined, 0)

typedef std::shared_ptr<Note> Note_ptr;
typedef std::vector<Note_ptr> list_note;

#endif //CONCEPTAPP_NOTES_H
