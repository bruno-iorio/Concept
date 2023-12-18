// mainhelp.h
#ifndef MAINHELP_H
#define MAINHELP_H

#include <QQuickItem>
#include <QMenu>
#include <QObject>

class MainHelp : public QQuickItem {
    Q_OBJECT

public:
    MainHelp(QQuickItem *parent = nullptr);
    ~MainHelp();

public slots:
    void showHelpMenu();

private:
    QMenu helpMenu;

private slots:
    void handleHelpAction1();
    void handleHelpAction2();
    void handleHelpAction3();
};

#endif // MAINHELP_H
