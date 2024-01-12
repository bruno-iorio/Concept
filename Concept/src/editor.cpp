#include <QtWidgets/QtWidgets>
#include "editor.h"
#include "precompiled.h"
#include "database/notes.h"
#include "errors.h"

ConceptEditor::ConceptEditor(QObject *parent) : QObject(parent) {}

void ConceptEditor::lastModifiedNote() {
    Note_ptr note; note.reset(new Note());
    qx_query query;
    query.orderAsc("last_modified").limit(1);
    QSqlError daoError = qx::dao::fetch_by_query(query, note);
    emit noteOpened(note->id, note->title, note->content);
}

void ConceptEditor::openNote(int id) {
    Note_ptr note; note.reset(new Note());
    note->id = id;
    QSqlError daoError = qx::dao::fetch_by_id(note);

    emit noteOpened(note->id, note->title, note->content);
}

void ConceptEditor::saveNote(int id, const QString &name, const QString &content) {
    Note_ptr note; note.reset(new Note());
    note->id = id;
    note->title = name;
    note->content = content;
    note->last_modified = QDateTime::currentDateTime();

    QSqlError daoError = qx::dao::update(note);
}

void ConceptEditor::createNote() {
    QDialog * d = new QDialog();

    QVBoxLayout * vbox = new QVBoxLayout();
    QLineEdit * name = new QLineEdit();

    QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                                        | QDialogButtonBox::Cancel);
    QLabel * title = new QLabel("Create a new note");
    
    QObject::connect(buttonBox, SIGNAL(accepted()), d, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), d, SLOT(reject()));

    vbox->setGeometry(QRect(0, 0, 300, 300));
    vbox->addWidget(name);
    vbox->addWidget(buttonBox);
    vbox->addWidget(title);
    
    d->setLayout(vbox);

    int result = d->exec();
    if(result == QDialog::Accepted)
    {
        Note_ptr note; note.reset(new Note());
        note->id = 0;
        note->title = name->text();
        note->content = "";
        note->last_modified = QDateTime::currentDateTime();

        QSqlError daoError = qx::dao::insert(note);

        if (daoError.isValid()) {
            error_popup(daoError.text());
            return;
        }

        emit noteCreated(note->id, note->title, note->content);
    }
}
