// SearchReplace.h
#ifndef SEARCHREPLACE_H
#define SEARCHREPLACE_H

#include <QQuickItem>
#include <QMenu>
#include <QObject>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QDialog>
#include <QListWidgetItem>
#include <QLineEdit>
#include <QMessageBox>

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
    SearchDialog(QWidget *parent = nullptr);
    ~SearchDialog();

private slots:
    void onSearch(QListWidgetItem *item);

private:
    QLabel *titleLabel;
    QLabel *inputLabel;
    QListWidget *searchResults;
    QPushButton *searchButton;
    QLineEdit *keywordInput;
    QLabel *searchResultsLabel;

    QString &text;

    QMap<QString, QString> searchConfirmation;
};

class ReplaceDialog : public QDialog
{
    Q_OBJECT

public:
    ReplaceDialog(QWidget *parent = nullptr);
    ~ReplaceDialog();

private slots:
    void onReplace(QListWidgetItem *item);

private:
    QLabel *titleLabel;
    QLabel *keyinputLabel;
    QLabel *newinputLabel;
    QPushButton *replaceAllButton;
    QLineEdit *keywordInput;
    QLineEdit *replacementInput;

    QString &text;

    QMap<QString, QString> replaceConfirmation;
};

#endif
