// main.cpp
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "texteditor.hpp"
#include "app_environment.h"
#include "import_qml_components_plugins.h"
#include "import_qml_plugins.h"
#include "mainhelp.h"
#include "textedit.h"
#include "textview.h"

int main(int argc, char *argv[]) {
    set_qt_environment();

    QApplication app(argc, argv);

    TextEditor *textEditor = new TextEditor();


    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("textEditor", textEditor);

    const QUrl url(u"qrc:/Main/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl) QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);

    //QObject::connect()

    engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
    engine.addImportPath(":/");
    engine.load(url);

    if (engine.rootObjects().isEmpty()) return -1;

    return app.exec();
}
