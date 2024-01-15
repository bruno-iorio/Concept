#ifndef CONCEPTAPP_EDITOR_H
#define CONCEPTAPP_EDITOR_H

#include <QObject>
#include <QtQml>
//#include "database.hpp"
#include "database/folders.h"


class ConceptEditor : public QObject {
    Q_OBJECT
    QML_ELEMENT
    public:
        explicit ConceptEditor(QObject *parent = nullptr);
        Q_INVOKABLE void createNote();
        Q_INVOKABLE void openNote(int id);
        Q_INVOKABLE void saveNote(int id, const QString &name, const QString &content);
        Q_INVOKABLE void lastModifiedNote();
        Q_INVOKABLE void renameNote(int id, const QString &name, const QString &content);
        Q_INVOKABLE void deleteNote(int id, const QString &name, const QString &content);
        Q_INVOKABLE void renameFolder(long id, const QString &currentName);
    signals:
        void noteOpened(long id, const QString &name, const QString &content);
        void noteCreated(long id, const QString &name, const QString &content);
        void noteRenamed(int id, const QString &name, const QString &content);
        void noteDeleted(int id, const QString &name, const QString &content);
        void folderRenamed(long id, const QString &name);

    /*public slots:
        void renameNote(int id, const QString &currentName, const QString &content);*/

};

#endif //CONCEPTAPP_EDITOR_H
