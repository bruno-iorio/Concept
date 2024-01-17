#ifndef SEARCHREPLACE_H
#define SEARCHREPLACE_H

#include <QQuickItem>
#include <QMenu>
#include <QObject>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QDialog>
#include <QListWidget> // Corrected from QListWidgetItem
#include <QLineEdit>
#include <QMessageBox>
#include <QMap> // Include QMap header

class SearchReplace : public QQuickItem
{
    Q_OBJECT

public:
    SearchReplace(QQuickItem *parent = nullptr);
    ~SearchReplace();

public slots:
    void handleSearchAction(const QString &content);
    void handleReplaceAction(const QString &content);

private:
    QMenu searchMenu;
    QMenu replaceMenu;
    QString text;
};

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    SearchDialog(QWidget *parent = nullptr, const QString &editorText = QString());
    ~SearchDialog();

private slots:
    void onSearch();

private:
    QLabel *titleLabel;
    QLabel *inputLabel;
    QListWidget *searchResults;
    QPushButton *searchButton;
    QLineEdit *keywordInput;
    QLabel *searchResultsLabel;

    QString text;
};

class ReplaceDialog : public QDialog
{
    Q_OBJECT

public:
    ReplaceDialog(QWidget *parent = nullptr, const QString &editorText = QString());

private slots:
    void onReplace();

private:
    QLabel *titleLabel;
    QLabel *keyinputLabel;
    QLabel *newinputLabel;
    QPushButton *replaceButton;
    QLineEdit *keywordInput;
    QLineEdit *replacementInput;
    QLabel *replaceConfirmationLabel;

    QString text;

signals:
    void textChanged(const QString &newtext);
};

#endif
