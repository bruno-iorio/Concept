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
#include "setFocusPeriod.h"

int main(int argc, char *argv[]) {
    set_qt_environment();

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<MainHelp>("CustomControls", 1, 0, "MainHelp");
    qmlRegisterType<SetFocusPeriod>("CustomControls", 1, 0, "SetFocusPeriod");

    const QUrl url(u"qrc:/Main/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl) QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);

    //QObject::connect()
    TextEditor textEditorWindow;
    engine.rootContext()->setContextProperty("textEditor", &textEditorWindow);

    engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
    engine.addImportPath(":/");
    engine.load(url);

    //Set Focus Period Button
    SetFocusPeriod focusItem;
    engine.rootContext()->setContextProperty("focusItem", &focusItem);

    //Help Button
    MainHelp helpItem;
    engine.rootContext()->setContextProperty("helpItem", &helpItem);

    if (engine.rootObjects().isEmpty()) return -1;

    return app.exec();
}
