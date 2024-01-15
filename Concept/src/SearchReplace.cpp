#include "editor.h"
#include "database/notes.h"
#include "SearchReplace.h"
#include <QAction>
#include <QCursor>
#include <QDebug>
#include <QBoxLayout>
#include <QtWidgets/QtWidgets>

SearchReplace::SearchReplace(QQuickItem *parent) : QQuickItem(parent)
{
    QAction *Search = new QAction("Search", this);
    QAction *Replace = new QAction("Replace", this);

    connect(Search, &QAction::triggered, this, &SearchReplace::handleSearchAction);
    connect(Replace, &QAction::triggered, this, &SearchReplace::handleReplaceAction);

    searchMenu.addAction(Search);
    searchMenu.addAction(Replace);
}

SearchReplace::~SearchReplace()
{
}

void SearchReplace::showSearchMenu()
{
    searchMenu.exec(QCursor::pos());
}

void SearchReplace::showReplaceMenu()
{
    replaceMenu.exec(QCursor::pos());
}

void SearchReplace::handleSearchAction()
{
    SearchDialog *searchDialog = new SearchDialog();
    searchDialog->exec();
}

void SearchReplace::handleReplaceAction()
{
    ReplaceDialog *replaceDialog = new ReplaceDialog();
    replaceDialog->exec();
}

SearchDialog::SearchDialog(QWidget *parent, const QString &editorText) : QDialog(parent), text(editorText)
{
    setWindowTitle("Search");

    titleLabel = new QLabel("Enter keyword to search:", this);
    keywordInput = new QLineEdit(this);
    searchButton = new QPushButton("Search", this);
    searchResults = new QListWidget(this); // Create a QListWidget for displaying search results

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    layout->addWidget(keywordInput);
    layout->addWidget(searchButton);
    layout->addWidget(searchResults); // Add the QListWidget to the layout

    connect(searchButton, &QPushButton::clicked, this, &SearchDialog::onSearch);
}

void SearchDialog::onSearch()
{
    // Get the keyword from the input
    QString keyword = keywordInput->text();

    // Clear the search results
    searchResults->clear();

    // Split the text into lines
    QStringList lines = text.split("\n");

    // Go through each line
    for (int i = 0; i < lines.size(); ++i)
    {
        // If the line contains the keyword
        if (lines[i].contains(keyword))
        {
            // Add the line to the search results
            QListWidgetItem *item = new QListWidgetItem(lines[i]);
            searchResults->addItem(item);
        }
    }
}

SearchDialog::~SearchDialog() {}

ReplaceDialog::ReplaceDialog(QWidget *parent, const QString &editorText) : QDialog(parent), text(editorText)
{
    setWindowTitle("Replace");

    titleLabel = new QLabel("Enter keyword to replace and its replacement:", this);
    keywordInput = new QLineEdit(this);
    replacementInput = new QLineEdit(this);
    replaceButton = new QPushButton("Replace", this);
    replaceAllButton = new QPushButton("Replace All", this);
    replaceConfirmationLabel = new QLabel("", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    layout->addWidget(keywordInput);
    layout->addWidget(replacementInput);
    layout->addWidget(replaceButton);
    layout->addWidget(replaceConfirmationLabel);

    connect(replaceButton, &QPushButton::clicked, this, &ReplaceDialog::onReplace);
}

void ReplaceDialog::onReplace()
{
    // Get the keyword and its replacement from the inputs
    QString keyword = keywordInput->text();
    QString replacement = replacementInput->text();

    // Replace all occurrences of the keyword in the text
    // text.replace(keyword, replacement);

    // Update the confirmation label
    replaceConfirmationLabel->setText("Replacement done.");
}

ReplaceDialog::~ReplaceDialog() {}
