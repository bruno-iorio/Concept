#include <QtWidgets/QtWidgets>
#include "editor.h"
#include "precompiled.h"
#include "database/notes.h"
#include "database/folders.h"
#include "errors.h"
#include <QxOrm.h>
#include "QxOrm_Impl.h"




ConceptEditor::ConceptEditor(QObject *parent) : QObject(parent) {}

void ConceptEditor::lastModifiedNote()
{
    Note_ptr note;
    note.reset(new Note());
    qx_query query;
    query.orderAsc("last_modified").limit(1);
    QSqlError daoError = qx::dao::fetch_by_query(query, note);
    emit noteOpened(note->id, note->title, note->content);
}

void ConceptEditor::openNote(int id)
{
    Note_ptr note;
    note.reset(new Note());
    note->id = id;
    QSqlError daoError = qx::dao::fetch_by_id(note);

    emit noteOpened(note->id, note->title, note->content);
}

void ConceptEditor::saveNote(int id, const QString &name, const QString &content)
{
    Note_ptr note;
    note.reset(new Note());
    note->id = id;
    note->title = name;
    note->content = content;
    note->last_modified = QDateTime::currentDateTime();

    QSqlError daoError = qx::dao::update(note);
}

void ConceptEditor::createNote()
{
    QDialog *d = new QDialog();

    QVBoxLayout *vbox = new QVBoxLayout();
    QLineEdit *name = new QLineEdit();

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    QLabel *title = new QLabel("Create a new note");

    QObject::connect(buttonBox, SIGNAL(accepted()), d, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), d, SLOT(reject()));

    vbox->setGeometry(QRect(0, 0, 300, 300));
    vbox->addWidget(name);
    vbox->addWidget(buttonBox);
    vbox->addWidget(title);

    d->setLayout(vbox);

    int result = d->exec();
    if (result == QDialog::Accepted)
    {
        Note_ptr note;
        note.reset(new Note());
        note->id = 0;
        note->title = name->text();
        note->content = "";
        note->last_modified = QDateTime::currentDateTime();

        QSqlError daoError = qx::dao::insert(note);

        if (daoError.isValid())
        {
            error_popup(daoError.text());
            return;
        }

        emit noteCreated(note->id, note->title, note->content);
    }
}

void ConceptEditor::renameNote(int id, const QString &currentName, const QString &content)
{
    QDialog *d = new QDialog();

    QVBoxLayout *vbox = new QVBoxLayout();
    QLineEdit *nameLineEdit = new QLineEdit();
    nameLineEdit->setText(currentName); // Set the initial text

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    QObject::connect(buttonBox, SIGNAL(accepted()), d, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), d, SLOT(reject()));

    vbox->setGeometry(QRect(0, 0, 300, 300));
    vbox->addWidget(nameLineEdit);
    vbox->addWidget(buttonBox);

    d->setLayout(vbox);

    int result = d->exec();
    if (result == QDialog::Accepted)
    {

        Note_ptr note(new Note());

        note->id = id;
        note->title = nameLineEdit->text();
        note->content = content;
        note->last_modified = QDateTime::currentDateTime();
        QSqlError daoError = qx::dao::update_with_all_relation(note);
        emit noteRenamed(note->id, note->title, note->content);

        delete d; // Free the memory

        if (daoError.isValid())
        {
            error_popup(daoError.text());
            return;
        }
    }
    else
    {
        delete d; // Free the memory in case of rejection
    }
}

void ConceptEditor::deleteNote(int id, const QString &currentName, const QString &content)
{
    // Create a dialog to confirm the deletion
    QMessageBox::StandardButton confirmation;
    confirmation = QMessageBox::question(nullptr, "Confirm Deletion",
                                         "Are you sure you want to delete this note?",
                                         QMessageBox::Yes | QMessageBox::No);

    // Check the user's response
    if (confirmation == QMessageBox::No)
    {
        return; // User canceled the deletion
    }

    // Proceed with the deletion
    Note_ptr note;
    note.reset(new Note());
    note->id = id;

    QSqlError daoError = qx::dao::delete_by_id(note);
    emit noteDeleted(note->id, note->title, note->content);

    if (daoError.isValid())
    {
        error_popup(daoError.text());
        return;
    }
}

void ConceptEditor::openFolder(long id) {
    Folder_ptr folder; folder.reset(new Folder());
    folder->id = id;
    QSqlError daoError = qx::dao::fetch_by_id(folder);

    emit folderOpened(folder->id, folder->name);
}

void ConceptEditor::renameFolder(long id, const QString &currentName) {


   /* QDialog *d = new QDialog();

    QVBoxLayout *vbox = new QVBoxLayout();
    QLineEdit *nameLineEdit = new QLineEdit();
    nameLineEdit->setText(currentName); // Set the initial text

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    QObject::connect(buttonBox, SIGNAL(accepted()), d, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), d, SLOT(reject()));

    vbox->setGeometry(QRect(0, 0, 300, 300));
    vbox->addWidget(nameLineEdit);
    vbox->addWidget(buttonBox);

    d->setLayout(vbox);

    int result = d->exec();
    // Fetch the existing folder
    Folder_ptr folder;
    folder.reset(new Folder());
    folder->id = id;

    QSqlError fetchError = qx::dao::fetch_by_id_with_all_relation(folder);
    if (fetchError.isValid()) {
        // Handle the error, e.g., show an error message
        error_popup(fetchError.text());
        return;
    }

    // Update the folder name
    folder->name = nameLineEdit->text();

    // Update the folder in the database
    QSqlError updateError = qx::dao::fetch_all_with_all_relation(folder);

    if (updateError.isValid()) {
        // Handle the error, e.g., show an error message
        error_popup(updateError.text());
    } else {
        // Emit a signal or perform any additional logic on successful rename
        emit folderRenamed(id, folder->name);
    }*/
}

void ConceptEditor::createFolder() {
    /*
    QDialog * d = new QDialog();

    QVBoxLayout * vbox = new QVBoxLayout();
    QLineEdit * name = new QLineEdit();

    QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                                       | QDialogButtonBox::Cancel);
    QLabel * title = new QLabel("Create a new folder");

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
        Folder_ptr folder; folder.reset(new Folder());
        folder->id = 0;
        folder->name = name->text();

        QSqlError daoError = qx::dao::insert(folder);

        if (daoError.isValid()) {
            error_popup(daoError.text());
            return;
        }

        emit folderCreated(folder->id, folder->name);
    }*/
}

void ConceptEditor::deleteFolder(long id) {
    /*auto folderIt = std::find_if(folders.begin(), folders.end(), [id](const Folder& folder) {
        return folder.id == id;
    });

    // Check if the folder was found
    if (folderIt == folders.end()) {
        // Handle the case where the folder was not found
        return;
    }

    // Create a dialog to confirm the deletion
    QMessageBox::StandardButton confirmation;
    confirmation = QMessageBox::question(nullptr, "Confirm Deletion",
                                         "Are you sure you want to delete this folder and its notes?",
                                         QMessageBox::Yes | QMessageBox::No);

    // Check the user's response
    if (confirmation == QMessageBox::No) {
        return;  // User canceled the deletion
    }

    // Iterate over each note in the folder's list_note and delete it using deleteNote
    for (const auto &note : folderIt->notes) {
        deleteNote(note->id, note->title, note->content);
    }

    // Now, proceed with the deletion of the folder itself
    // Assuming qx::dao::delete_by_id is used to delete the folder
    QSqlError daoError = qx::dao::delete_by_id<Folder>(*folderIt);

    if (daoError.isValid()) {
        error_popup(daoError.text());
        return;
    }



    // Emit a signal or perform other actions to notify the UI about the deletion of the folder
    emit folderDeleted(folderIt->id);*/
}
