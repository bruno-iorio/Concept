#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QWidget>
#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QVBoxLayout>

class TextEditor : public QWidget {
    Q_OBJECT
public:
    explicit TextEditor(QWidget *parent = nullptr);
    virtual ~TextEditor() override;


public slots:
    void showEditor();


private slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();


private:
    QTextEdit *textEdit;
    QString currentFilePath;
    QMenuBar *menuBar;
    QWindow *window;

    void createMenu();
};

#endif // TEXTEDITOR_H
