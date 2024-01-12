// mainhelp.h
#ifndef MAINHELP_H
#define MAINHELP_H

#include <QQuickItem>
#include <QMenu>
#include <QObject>
#include <QPushButton>
#include <QLabel>
#include <QDialog>
#include <QListWidget>

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


/*
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
*/

class HelpDialog : public QDialog {
    Q_OBJECT

public:
    HelpDialog(QWidget *parent = nullptr);
    ~HelpDialog();

private slots:
    void onFeatureItemSelected(QListWidgetItem *item);

private:
    QLabel *titleLabel;
    QLabel *featuresLabel;
    QListWidget *featuresList;
    QPushButton *closeButton;
    QLabel *featureExplanationLabel;

    QMap<QString, QString> featureExplanations;
};
#endif // MAINHELP_H
