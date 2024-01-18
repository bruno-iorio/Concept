#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QQuickItem>
#include <QObject>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QDialog>
#include <QListWidget>
#include <QLineEdit>

class ToolBox : public QQuickItem
{
    Q_OBJECT

public:
    ToolBox(QQuickItem *parent = nullptr);
    ~ToolBox();

public slots:
    void handleSearchAction(const QString &content);
    void handleReplaceAction(const QString &content);
    void onReplace();

signals:
    void textChanged(const QString &newtext);

private:
    QDialog *replaceDialog;
    QLabel *replaceTitleLabel;
    QPushButton *replaceButton;
    QLineEdit *keywordInput;
    QLineEdit *replacementInput;
    QLabel *replaceConfirmationLabel;
    QPushButton *closeReplaceButton;

    QString text;
};

// Replace functionality: I had to merge the ReplaceDialog class
// into this class because otherwise the signal isn't emitted
// properly. However, as I don't need to emit anything for the
// SearchDialog, I can keep it as a separate class and it looks cleaner.

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    SearchDialog(QWidget *parent = nullptr, const QString &editorText = QString());
    ~SearchDialog();

private slots:
    void onSearch();

private:
    QDialog *searchDialog;
    QLabel *titleLabel;
    QListWidget *searchResults;
    QPushButton *searchButton;
    QLineEdit *keywordInput;
    QPushButton *closeSearchButton;

    QString text;
};

#endif // TOOLBOX_H
