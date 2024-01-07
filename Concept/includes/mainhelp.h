// mainhelp.h
#ifndef MAINHELP_H
#define MAINHELP_H

#include <QQuickItem>
#include <QMenu>
#include <QObject>
#include <QPushButton>

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

signals:
    void newEditorOptionSelected();
    void showRedSquare();  // New signal for showing the red square

};

class RedSquareManager : public QObject
{
    Q_OBJECT

public:
    RedSquareManager(QObject *parent = nullptr);

public slots:
    void showRedSquare();

signals:
    void redSquareRequested();
};

#endif // MAINHELP_H
