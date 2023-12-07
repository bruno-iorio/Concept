#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QMainWindow>
#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

class TextEditor : public QMainWindow {
Q_OBJECT
public:
    TextEditor(QWidget *parent = nullptr);
    virtual ~TextEditor(){};
private slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();

private:
    QTextEdit *textEdit;
    QString currentFilePath;

    void createMenu();
};

#endif // TEXTEDITOR_H
