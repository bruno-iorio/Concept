#ifndef CONCEPTAPP_EDITOR_H
#define CONCEPTAPP_EDITOR_H

#include <QObject>
#include <QtQml>
#include "database/folders.h"
#include "database/notes.h"

class ConceptEditor : public QObject
{
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
        Q_INVOKABLE void openFolder(long id);
        Q_INVOKABLE void createFolder();
        Q_INVOKABLE void deleteFolder(long id);
        Q_INVOKABLE QString renderHtml(QString note);
    signals:
        void noteOpened(long id, const QString &name, const QString &content);
        void noteCreated(long id, const QString &name, const QString &content);
        void noteRenamed(int id, const QString &name, const QString &content);
        void noteDeleted(int id, const QString &name, const QString &content);
        void folderOpened(long id, const QString &name);
        void folderRenamed(long id, const QString &name);
        void folderCreated(long id, const QString &name);
        void folderDeleted(long id);


    /*public slots:
        void renameNote(int id, const QString &currentName, const QString &content);*/
    private:
        std::vector<Folder> folders;
};

#endif // CONCEPTAPP_EDITOR_H
