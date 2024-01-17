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
}

SearchReplace::~SearchReplace()
{
}

void SearchReplace::handleSearchAction(const QString &content)
{
    SearchDialog *searchDialog = new SearchDialog(nullptr, content);
    searchDialog->exec();
}

void SearchReplace::handleReplaceAction(const QString &content)
{
    ReplaceDialog *replaceDialog = new ReplaceDialog(nullptr, content);
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
        int index = lines[i].indexOf(keyword);
        if (index != -1)
        {
            // Calculate the start and end positions for the substring
            int start = std::max(0, index - 10);
            int end = std::min(lines[i].length(), index + keyword.length() + 10);

            // Get the substring around the keyword
            QString substring = lines[i].mid(start, end - start);

            // Add the substring to the search results
            QListWidgetItem *item = new QListWidgetItem(QString("Line ") + QString::number(i + 1) + QString(". '") + substring + QString("'"));
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
    QString copy = text;

    text.replace(keyword, replacement);

    emit textChanged(text);

    replaceConfirmationLabel->setText(text); // "Replacement done.");
}
