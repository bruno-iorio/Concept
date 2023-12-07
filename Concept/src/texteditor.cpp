#include "texteditor.hpp"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

TextEditor::TextEditor(QWidget *parent)
    : QMainWindow(parent) {
    textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);

    createMenu();
}

void TextEditor::createMenu() {
    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    QMenu *fileMenu = menuBar->addMenu("File");

    QAction *newAction = fileMenu->addAction("New");
    connect(newAction, &QAction::triggered, this, &TextEditor::newFile);

    QAction *openAction = fileMenu->addAction("Open");
    connect(openAction, &QAction::triggered, this, &TextEditor::openFile);

    QAction *saveAction = fileMenu->addAction("Save");
    connect(saveAction, &QAction::triggered, this, &TextEditor::saveFile);

    QAction *saveAsAction = fileMenu->addAction("Save As");
    connect(saveAsAction, &QAction::triggered, this, &TextEditor::saveFileAs);
	}

void TextEditor::newFile() {
    textEdit->clear();
    currentFilePath.clear();
}

void TextEditor::openFile() {
    QString filePath = QFileDialog::getOpenFileName(this, "Open File", QString(), "Text Files (*.txt);;All Files (*.*)");
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            textEdit->setPlainText(in.readAll());
            currentFilePath = filePath;
            file.close();
        }
    }
}

void TextEditor::saveFile() {
    if (currentFilePath.isEmpty()) {
        saveFileAs();
    } else {
        QFile file(currentFilePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << textEdit->toPlainText();
            file.close();
        }
    }
}

void TextEditor::saveFileAs() {
    QString filePath = QFileDialog::getSaveFileName(this, "Save File As", QString(), "Text Files (*.txt);;All Files (*.*)");
    if (!filePath.isEmpty()) {
        currentFilePath = filePath;
        saveFile();
    }
}

