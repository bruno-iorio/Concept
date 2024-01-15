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
    void showSearchMenu();
    void showReplaceMenu();

private:
    QMenu searchMenu;
    QMenu replaceMenu;

private slots:
    void handleSearchAction();
    void handleReplaceAction();

signals:
    void Search();
    void Replace();
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

    const QString &text;

    QMap<QString, QString> searchConfirmation;
};

class ReplaceDialog : public QDialog
{
    Q_OBJECT

public:
    ReplaceDialog(QWidget *parent = nullptr, const QString &editorText = QString());
    ~ReplaceDialog();

private slots:
    void onReplace();

private:
    QLabel *titleLabel;
    QLabel *keyinputLabel;
    QLabel *newinputLabel;
    QPushButton *replaceButton;
    QPushButton *replaceAllButton;
    QLineEdit *keywordInput;
    QLineEdit *replacementInput;
    QLabel *replaceConfirmationLabel;

    const QString &text;

    QMap<QString, QString> replaceConfirmation;
};

#endif
