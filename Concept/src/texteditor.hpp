#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QWidget>
#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QVBoxLayout>
#include <vector>
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
    std::vector<TextEditor*> listofTE;
    int numberofTE{0};
    void createMenu();
};

#endif // TEXTEDITOR_H
