#ifndef CONCEPTAPP_EDITOR_H
#define CONCEPTAPP_EDITOR_H

#include <QObject>
#include <QtQml>
//#include "database.hpp"

class ConceptEditor : public QObject {
    Q_OBJECT
    QML_ELEMENT
    public:
        explicit ConceptEditor(QObject *parent = nullptr);
        Q_INVOKABLE void createNote();
        Q_INVOKABLE void openNote(int id);
        Q_INVOKABLE void saveNote(int id, const QString &name, const QString &content);
        Q_INVOKABLE void lastModifiedNote();
    signals:
        void noteOpened(long id, const QString &name, const QString &content);
};

#endif //CONCEPTAPP_EDITOR_H
