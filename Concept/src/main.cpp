// main.cpp
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDirIterator>
#include <QtSql>
#include <QFontDatabase>
#include "includes/app_environment.h"
#include "includes/import_qml_components_plugins.h"
#include "includes/import_qml_plugins.h"
#include "QxOrm.h"
#include "database/database.h"

int main(int argc, char *argv[]) {
    // Initialize QxOrm
    qx::QxSqlDatabase::getSingleton()->setDriverName("QSQLITE");
    qx::QxSqlDatabase::getSingleton()->setDatabaseName("./database.sqlite");
    qx::QxSqlDatabase::getSingleton()->setHostName("localhost");
    qx::QxSqlDatabase::getSingleton()->setUserName("root");
    qx::QxSqlDatabase::getSingleton()->setPassword("");

    // Create the table if it doesn't exist
    qx::dao::create_table<Note>();
//    qx::dao::create_table<Folder>();
//    qx::dao::create_table<FocusTime>();

    // Add a note to the database
    Note_ptr note; note.reset(new Note());

    // Check if at least 1 note exists, if not, create a test note

    if (qx::dao::count<Note>() == 0) {
        qDebug() << "No notes found, creating a test note";
        note->id = 1;
        note->title = QString("Test title");
        note->content = QString("Test content");
        note->last_modified = QDateTime::currentDateTime();

        QSqlError dao = qx::dao::insert(note);
    }

    set_qt_environment();

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // Font database
    QDirIterator it(":/content/fonts", QDirIterator::Subdirectories);

    while (it.hasNext()) {
        QFontDatabase::addApplicationFont(it.next());
    }

    app.setFont(QFont("Roboto Mono"));

    const QUrl url(u"qrc:/Main/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl) QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);


    engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
    engine.addImportPath(":/");
    engine.load(url);

    if (engine.rootObjects().isEmpty()) return -1;

    return app.exec();
}
