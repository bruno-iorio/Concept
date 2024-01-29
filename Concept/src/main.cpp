// main.cpp
#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDirIterator>
#include <QFontDatabase>
#include "includes/app_environment.h"
#include "includes/import_qml_components_plugins.h"
#include "includes/import_qml_plugins.h"
#include "QxOrm.h"
#include "database/database.h"
#include <QDebug>
#include "explorer.h"
#include <QTreeView>
#include "includes/mainhelp.h"
#include "includes/setFocusPeriod.h"
#include "includes/todoList.h"
#include "includes/ToolBox.h"
#include "includes/calendar.h"
#include "includes/calc.h"
#include <iostream>
#include <vector>
#include "includes/timerUI.h"

int main(int argc, char *argv[])
{
    // Initialize QxOrm
    qx::QxSqlDatabase::getSingleton()->setDriverName("QSQLITE");
    qx::QxSqlDatabase::getSingleton()->setDatabaseName("./database.sqlite");
    qx::QxSqlDatabase::getSingleton()->setHostName("localhost");
    qx::QxSqlDatabase::getSingleton()->setUserName("root");
    qx::QxSqlDatabase::getSingleton()->setPassword("");

    // Create the table if it doesn't exist
    qx::dao::create_table<Note>();
    qx::dao::create_table<Folder>();
    qx::dao::create_table<FocusTime>();
    qx::dao::create_table<timerElements>();
    qx::dao::create_table<calendarEvents>();

    // Add a note to the database
    Note_ptr note;
    note.reset(new Note());

    // Check if at least 1 note exists, if not, create a test note

    if (qx::dao::count<calendarEvents>() == 0)
    {
        qDebug() << "no calendarEvents found."
                 << "\n";
    }
    if (qx::dao::count<Note>() == 0)
    {
        qDebug() << "No notes found, creating a test note";
        note->id = 1;
        note->title = QString("Test title");
        note->content = QString("Test content");
        note->last_modified = QDateTime::currentDateTime();

        QSqlError dao = qx::dao::insert(note);
    }
    else
    {
        qx::dao::fetch_all(note);
    }

    // Create test folder
    Folder_ptr folder;
    folder.reset(new Folder());

    if (qx::dao::count<Folder>() == 0)
    {
        qDebug() << "No folders found, creating a test folder";
        folder->id = 1;
        folder->name = QString("Test folder");
        folder->notes.push_back(note);

        QSqlError dao = qx::dao::insert_with_all_relation(folder);
    }
    else
    {
        qx::dao::fetch_all(folder);
    }

    // Add test note to test folder
    if (qx::dao::count<Folder>() > 0)
    {
        qDebug() << "Adding test note to test folder";
        note->folder = folder;
        QSqlError dao = qx::dao::update_with_all_relation(note);
        qDebug() << dao.text();
    }
    
    // checking if timerElements is being stored in the database.
    if (qx::dao::count<timerElements>() == 0) {
        qDebug() << "No timerElements found";
    } else {
	qDebug() << " TIMER ELEMENTS FOUND " << "\n";
	}




    set_qt_environment();

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;


    // Font database
    QDirIterator it(":/content/fonts", QDirIterator::Subdirectories);

    while (it.hasNext())
    {
        QFontDatabase::addApplicationFont(it.next());
    }

    app.setFont(QFont("Roboto Mono"));

    // Defining the types that will be used within the QML
    qmlRegisterType<MainHelp>("CustomControls", 1, 0, "MainHelp");
    qmlRegisterType<SetFocusPeriod>("CustomControls", 1, 0, "SetFocusPeriod");
    qmlRegisterType<timerStart>("CustomControls", 1, 0, "TimerStart");


    timerStart myTimerStart;
    engine.rootContext()->setContextProperty("myTimerStart", &myTimerStart); // Exposing to QML

    //RedSquareManager redSquareManager;
    qmlRegisterType<Calendar>("CustomControls", 1, 0, "Calendar");
    qmlRegisterType<ToolBox>("CustomControls", 1, 0, "ToolBox");
    qmlRegisterType<CalendarQML>("CustomControls", 1, 0, "CalendarQML");
    qmlRegisterType<Calc>("CustomControls", 1, 0, "Calc");

    const QUrl url(u"qrc:/Main/main.qml"_qs);
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl)
        {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
    engine.addImportPath(":/");
    engine.load(url);

    NewListAbstractModel model(&app);
    engine.rootContext()->setContextProperty("fileListModel", QVariant::fromValue(&model));

    // Set Focus Period Button
    SetFocusPeriod focusItem;
    engine.rootContext()->setContextProperty("focusItem", &focusItem);

    // Help Button
    MainHelp helpItem;
    HelpDialog1 helpDialog1;
    engine.rootContext()->setContextProperty("helpItem", &helpItem);
    QObject::connect(&helpItem, &MainHelp::File, [&helpDialog1]()
                     {
                         helpDialog1.show(); // You can use show() instead of exec() for modeless dialog
                     });

    // Calendar Button
    CalendarQML calendarItem = CalendarQML();
    engine.rootContext()->setContextProperty("calendarItem", &calendarItem);

    QObject::connect(&calendarItem, &CalendarQML::File, [&calendarItem]()
                     { calendarItem.showCalendar(); });

    // Connect the signal from CalendarQML to close the Calendar
    QObject::connect(&calendarItem, &CalendarQML::showCalendar, [&calendarItem]()
                     { calendarItem.closeCalendarFromQML(); });

    // Connect the aboutToQuit signal to close the calendar when the application is about to quit
    QObject::connect(qApp, &QGuiApplication::aboutToQuit, [&calendarItem]()
                     { calendarItem.closeCalendarFromQML(); });

    HelpNotebooks helpNotebooks;
    engine.rootContext()->setContextProperty("helpItem", &helpItem);
    QObject::connect(&helpItem, &MainHelp::Notebooks, [&helpNotebooks]()
                     {
                         helpNotebooks.show(); // You can use show() instead of exec() for modeless dialog
                     });

    if (engine.rootObjects().isEmpty())
    {
        std::cout << "Root Objects is empty" << std::endl;
        return -1;
    }
    //    QTreeView treeView;
    //    ExplorerModel model;
    //    treeView.setModel(&model);
    //    treeView.show();

    return app.exec();
}
