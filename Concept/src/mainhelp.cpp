// mainhelp.cpp
#include "mainhelp.h"
#include <QAction>
#include <QCursor>
#include <QDebug>
#include <QQuickItem>
#include <QBoxLayout>

MainHelp::MainHelp(QQuickItem *parent) : QQuickItem(parent) {
    QAction *helpAction1 = new QAction("File - View - Format", this);
    QAction *helpAction2 = new QAction("Notebooks", this);
    QAction *helpAction3 = new QAction("Study Timer", this);
    QAction *helpAction4 = new QAction("Global Search", this);
    QAction *helpAction5 = new QAction("Replace", this);

    connect(helpAction1, &QAction::triggered, this, &MainHelp::handleHelpAction1);
    connect(helpAction2, &QAction::triggered, this, &MainHelp::handleHelpAction2);
    connect(helpAction3, &QAction::triggered, this, &MainHelp::handleHelpAction3);
    connect(helpAction4, &QAction::triggered, this, &MainHelp::handleHelpAction4);
    connect(helpAction5, &QAction::triggered, this, &MainHelp::handleHelpAction5);



    helpMenu.addAction(helpAction1);
    helpMenu.addAction(helpAction2);
    helpMenu.addAction(helpAction3);
    helpMenu.addAction(helpAction4);
    helpMenu.addAction(helpAction5);


}

void MainHelp::showHelpMenu() {
    // Show the context menu at the current cursor position
    helpMenu.exec(QCursor::pos());
}

void MainHelp::handleHelpAction2() {
    qDebug() << "Help Text 2 clicked!";

    HelpNotebooks *helpNotebooks = new HelpNotebooks();
    helpNotebooks->exec();  // Use exec() for a modal dialog

    // Cleanup the dialog when done
    delete helpNotebooks;
}

void MainHelp::handleHelpAction3() {
    qDebug() << "Help Text 3 clicked!";

    StudyTimer *studyTimer = new StudyTimer();
    ~studyTimer -> exec();


}

void MainHelp::handleHelpAction4() {
    qDebug() << "Help Text 4 clicked!";

    HelpGlobalSearch *helpGlobalSearch = new HelpGlobalSearch();
    ~helpGlobalSearch -> exec();
}


void MainHelp::handleHelpAction5() {
    qDebug() << "Help Text 5 clicked!";

    Replace *replace = new Replace();
    ~replace -> exec();
}

MainHelp::~MainHelp() {
    // Perform cleanup or resource release here, if needed
}

void MainHelp::handleHelpAction1() {
    qDebug() << "File";

    HelpDialog1 *helpDialog1 = new HelpDialog1();
    helpDialog1->exec();  // Use exec() for a modal dialog

    // Cleanup the dialog when done
    delete helpDialog1;
}

StudyTimer::StudyTimer(QWidget *parent) : QDialog(parent){
    setWindowTitle("Study Timer Help");

    featuresTimer = new QLabel("Features:", this);

    timerList = new QListWidget(this);
    timerList->addItem("Where?");
    timerList->addItem("Set Focus Period");
    timerList->addItem("Start/Stop");
    timerList->addItem("Break");
    timerList->addItem("Continue");
    timerList->addItem("Statistics");

    timerFeatExplained["Where?"] = "Collumn on the right!";
    timerFeatExplained["Set Focus Period"] = "Choose the period you want to \nfocus for and press Start.";
    timerFeatExplained["Start/Stop"] = "Start or Stop the timer.";
    timerFeatExplained["Break"] = "Stop the timer to take a break.";
    timerFeatExplained["Continue"] = "Start the timer again after \nthe break, continues the time.";
    timerFeatExplained["Statistics"] = "See your progress!";

    timerFeatureLabel = new QLabel("", this);

    closeTimer = new QPushButton("Close", this);

    QVBoxLayout *layoutTimer = new QVBoxLayout(this);
    layoutTimer->addWidget(featuresTimer);
    layoutTimer->addWidget(timerList);
    layoutTimer->addWidget(timerFeatureLabel);
    layoutTimer->addWidget(closeTimer);

    connect(closeTimer, &QPushButton::clicked, this, &StudyTimer::close);

    // Connect the itemClicked signal to the custom slot
    connect(timerList, &QListWidget::itemClicked, this, &StudyTimer::timer_selected);

}

void StudyTimer::timer_selected(QListWidgetItem *item){
    QString feature = item->text();
    if (timerFeatExplained.contains(feature)) {
        timerFeatureLabel->setText(timerFeatExplained[feature]);
    } else {
        timerFeatureLabel->setText("");
    }
}

HelpDialog1::HelpDialog1(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Help File");

    // Create and setup UI components
    titleLabel = new QLabel("", this);
    featuresLabel = new QLabel("Features:", this);

    // Create a QListWidget for displaying the list of features
    featuresList = new QListWidget(this);
    featuresList->addItem("Save Note");
    featuresList->addItem("New Note");
    featuresList->addItem("Increase/Decrease Font");
    featuresList->addItem("Toggle Line Number");
    featuresList->addItem("Toggle Expand Path");
    featuresList->addItem("Search");
    featuresList->addItem("Exit");


    // Populate the feature explanations map
    featureExplanations["Save Note"] = "This feature saves the note into the \nNotebooks section.";
    featureExplanations["New Note"] = "This feature creates a new note in the current \ntext editor, while still adding it to the \nNotebooks section.";
    featureExplanations["Increase/Decrease Font"] = "This feature changes the \nfont size as wanted.";
    featureExplanations["Toggle Line Number"] = "Turn ON/OFF the line numbers on the left of \nthe text editor.";
    featureExplanations["Toggle Expand Path"] = "This feature expands all \npaths in the current file.";
    featureExplanations["Exit"] = "Closes the whole app.";
    featureExplanations["Search"] = "Search a keyword in the current \ntext editor.";


    // Create a QLabel for displaying feature explanations
    featureExplanationLabel = new QLabel("", this);

    closeButton = new QPushButton("Close", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    layout->addWidget(featuresLabel);
    layout->addWidget(featuresList);
    layout->addWidget(featureExplanationLabel);
    layout->addWidget(closeButton);

    connect(closeButton, &QPushButton::clicked, this, &HelpDialog1::close);

    // Connect the itemClicked signal to the custom slot
    connect(featuresList, &QListWidget::itemClicked, this, &HelpDialog1::onFeatureItemSelected);
}

StudyTimer::~StudyTimer(){

}

void HelpDialog1::onFeatureItemSelected(QListWidgetItem *item) {
    // Update the explanation label based on the selected feature
    QString feature = item->text();
    if (featureExplanations.contains(feature)) {
        featureExplanationLabel->setText(featureExplanations[feature]);
    } else {
        featureExplanationLabel->setText("");
    }
}

HelpDialog1::~HelpDialog1() {
    // Perform cleanup or resource release here, if needed
}


HelpNotebooks::HelpNotebooks(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Help Notebooks");

    // Create and setup UI components
    titleNotebooks = new QLabel("", this);
    featuresNotebooks = new QLabel("This section is where you find your saved and current \nfolders and files. You can toggle between them, \nopen which one you like, read or edit it!", this);

    closeButton2 = new QPushButton("Close", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titleNotebooks);
    layout->addWidget(featuresNotebooks);
    //layout->addWidget(featuresList);
    //layout->addWidget(featureExplanationLabel);
    layout->addWidget(closeButton2);

    connect(closeButton2, &QPushButton::clicked, this, &HelpNotebooks::close);

    // Connect the itemClicked signal to the custom slot
    //connect(featuresList, &QListWidget::itemClicked, this, &HelpDialog1::onFeatureItemSelected);
}

HelpGlobalSearch::HelpGlobalSearch(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Help Global Search");

    // Create and setup UI components
    titleGSearch = new QLabel("Looking for keywords globally:", this);
    featuresGSearch = new QLabel("Find the lens on the \nSide Bar! With it \nyou can search for keywords within \nany file or folder in the app.", this);

    closeGSearch = new QPushButton("Close", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titleGSearch);
    layout->addWidget(featuresGSearch);
    //layout->addWidget(featuresList);
    //layout->addWidget(featureExplanationLabel);
    layout->addWidget(closeGSearch);

    connect(closeGSearch, &QPushButton::clicked, this, &HelpGlobalSearch::close);

    // Connect the itemClicked signal to the custom slot
    //connect(featuresList, &QListWidget::itemClicked, this, &HelpDialog1::onFeatureItemSelected);
}

HelpGlobalSearch::~HelpGlobalSearch(){}



HelpNotebooks::~HelpNotebooks() {

}

Replace::Replace(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Help Replace");

    // Create and setup UI components
    titleReplace = new QLabel("", this);
    featuresReplace = new QLabel("Use:", this);

    // Create a QListWidget for displaying the list of features
    featuresListReplace = new QListWidget(this);
    featuresListReplace->addItem("Where:");
    featuresListReplace->addItem("Keyword");
    featuresListReplace->addItem("Search");
    featuresListReplace->addItem("Second Line");
    featuresListReplace->addItem("Replace One");
    featuresListReplace->addItem("Replace All");
    featuresListReplace->addItem("Replacing");


    // Populate the feature explanations map
    featureExplanationsReplace["Where:"] = "Find it in the Format menu!";
    featureExplanationsReplace["Keyword"] = "Enter any keyword you \nwant to find.";
    featureExplanationsReplace["Second Line"] = "Enter in the second \nline the word you want \nyour keyword replaced with.";
    featureExplanationsReplace["Replace One"] = "Choose to replace just the \nfirst appearence of the keyword";
    featureExplanationsReplace["Replace All"] = "Choose to replace all \nappearences of your keyword.";
    featureExplanationsReplace["Replacing"] = "The replacing happens \n automatically, you just need \nto save the changes.";
    featureExplanationsReplace["Search"] = "Search up the word \nin the current editor.";


    // Create a QLabel for displaying feature explanations
    featureExplanationReplace = new QLabel("", this);

    closeReplace = new QPushButton("Close", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titleReplace);
    layout->addWidget(featuresReplace);
    layout->addWidget(featuresListReplace);
    layout->addWidget(featureExplanationReplace);
    layout->addWidget(closeReplace);

    connect(closeReplace, &QPushButton::clicked, this, &Replace::close);

    // Connect the itemClicked signal to the custom slot
    connect(featuresListReplace, &QListWidget::itemClicked, this, &Replace::onSelected);
}

Replace::~Replace(){}

void Replace::onSelected(QListWidgetItem *item) {
    // Update the explanation label based on the selected feature
    QString feature = item->text();
    if (featureExplanationsReplace.contains(feature)) {
        featureExplanationReplace->setText(featureExplanationsReplace[feature]);
    } else {
        featureExplanationReplace->setText("");
    }
}

