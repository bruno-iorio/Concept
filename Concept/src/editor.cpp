#include <QtWidgets/QtWidgets>
#include "editor.h"
#include "QxOrm.h"
#include "database/notes.h"

ConceptEditor::ConceptEditor(QObject *parent) : QObject(parent) {}

void ConceptEditor::lastModifiedNote() {
    std::shared_ptr<Note> note; note.reset(new Note());
    qx_query query;
    query.orderAsc("last_modified").limit(1);
    QSqlError daoError = qx::dao::fetch_by_query(query, note);
    qDebug() << "Last modified note: " << note->id;
    emit noteOpened(note->id, note->title, note->content);
}

void ConceptEditor::openNote(int id) {
    qDebug() << "Open note with id: " << id;
    std::shared_ptr<Note> note; note.reset(new Note());
    note->id = id;
    QSqlError daoError = qx::dao::fetch_by_id(note);

    emit noteOpened(note->id, note->title, note->content);
}

void ConceptEditor::saveNote(int id, const QString &name, const QString &content) {
    qDebug() << "Save note with id: " << id;
    std::shared_ptr<Note> note; note.reset(new Note());
    note->id = id;
    note->title = name;
    note->content = content;
    note->last_modified = QDateTime::currentDateTime();

    QSqlError daoError = qx::dao::update(note);
}

void ConceptEditor::createNote() {
    QDialog * d = new QDialog();
    d->setWindowTitle("Create a new note");

    QVBoxLayout * vbox = new QVBoxLayout();
    QLineEdit * name = new QLineEdit();

    QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                                        | QDialogButtonBox::Cancel);

    QObject::connect(buttonBox, SIGNAL(accepted()), d, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), d, SLOT(reject()));

    vbox->addWidget(name);
    vbox->addWidget(buttonBox);

    d->setLayout(vbox);

    int result = d->exec();
    if(result == QDialog::Accepted)
    {
        std::shared_ptr<Note> note; note.reset(new Note());
        note->id = 0;
        note->title = name->text();
        note->content = "";
        note->last_modified = QDateTime::currentDateTime();

        QSqlError daoError = qx::dao::insert(note);
        qDebug() << "Note created";

        emit noteOpened(note->id, note->title, note->content);
    }
}
