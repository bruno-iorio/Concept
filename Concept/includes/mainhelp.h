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
    void File();
    void Notebooks();
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

class HelpDialog1 : public QDialog {
    Q_OBJECT

public:
    HelpDialog1(QWidget *parent = nullptr);
    ~HelpDialog1();

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

class StudyTimer : public QDialog {
    Q_OBJECT

public:
    StudyTimer(QWidget *parent = nullptr);
    ~StudyTimer();

private slots:
    void timer_selected(QListWidgetItem *item);

private:
    //QLabel *titleTimer;
    QLabel *featuresTimer;
    QListWidget *timerList;
    QPushButton *closeTimer;
    QLabel *timerFeatureLabel;

    QMap <QString, QString> timerFeatExplained;
};

class HelpNotebooks : public QDialog {
    Q_OBJECT

public:
    HelpNotebooks(QWidget *parent = nullptr);
    ~HelpNotebooks();

//private slots:
  //  void notebook(QListWidgetItem *item);

private:
    QLabel *titleNotebooks;
    QLabel *featuresNotebooks;
    //QListWidget *featuresList;
    QPushButton *closeButton2;
    //QLabel *featureExplanationLabel;

   // QMap<QString, QString> featureExplanations;
};
#endif // MAINHELP_H

