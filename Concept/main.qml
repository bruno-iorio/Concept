//main.qml

import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import Concept
import QtQuick.Shapes
import CustomControls 1.0

pragma ComponentBehavior: Bound

ApplicationWindow {
    id: root

    property bool showLineNumbers: true
    property alias editor: editor

    width: Screen.width * 0.95
    height: Screen.height * 0.95
    title: "Concept"
    visible: true
    color: Colors.background

    flags: Qt.Window | Qt.FramelessWindowHint

    function generateInfoText() {
        var infoText = "Concept"
        if (editor.currentNoteTitle !== "") {
            infoText += " - " + editor.currentNoteTitle
        }
        return infoText
    }

    menuBar: CMenuBar {
        dragWindow: root
        infoText: generateInfoText()


        CMenu {
            id: noteContextMenu
            title: qsTr("File")
            /*
            Action {
                text: qsTr("Debug")
                shortcut: "Ctrl+D"
                onTriggered: () => {
                    console.log("Debug triggered")
                    editor.controller.openNote(1)
                }
            }
            */
            Action {
                text: qsTr("Save Note")
                shortcut: "Ctrl+S"
                onTriggered: () => {
                    editor.render(editor.text.text);
                    editor.controller.saveNote(editor.currentNoteId, editor.currentNoteTitle, editor.text.text);
                }
            }
            Action {
                text: qsTr("New Note")
                shortcut: StandardKey.New
                onTriggered: editor.controller.createNote()
            }
            Action {
                text: qsTr("Exit")
                onTriggered: Qt.exit(0)
                shortcut: StandardKey.Quit
            }
        }

        CMenu {
            title: qsTr("View")
            Action {
                text: root.showLineNumbers ? qsTr("Toggle Line Numbers OFF")
                    : qsTr("Toggle Line Numbers ON")
                shortcut: "Ctrl+L"
                onTriggered: root.showLineNumbers = !root.showLineNumbers
            }
            Action {
                text: root.expandPath ? qsTr("Toggle Short Path")
                    : qsTr("Toggle Expand Path")
                enabled: root.currentNoteId !== ""
                onTriggered: root.expandPath = !root.expandPath
            }
            Action {
                text: Colors.isDarkMode ? qsTr("Toggle Light Mode")
                    : qsTr("Toggle Dark Mode")
                onTriggered: Colors.isDarkMode = !Colors.isDarkMode
            }
        }

        ToolBox {
            id: tbTool
            onTextChanged: (newtext) => {
                // Action when the replace button is hit in ToolBox.cpp
                editor.text.text = newtext;
                editor.controller.saveNote(editor.currentNoteId, editor.currentNoteTitle, editor.text.text);
            }
        }

        CMenu {
            title: qsTr("Format")
            Action {
                text: qsTr("Increase Font")
                shortcut: StandardKey.ZoomIn
                onTriggered: editor.text.font.pixelSize += 1
            }
            Action {
                text: qsTr("Decrease Font")
                shortcut: StandardKey.ZoomOut
                onTriggered: editor.text.font.pixelSize -= 1
            }
            Action {
                text: qsTr("Search")
                shortcut: StandardKey.Find
                onTriggered: tbTool.handleSearchAction(editor.text.text, false)
            }
            Action {
                text: qsTr("Replace")
                shortcut: StandardKey.Replace
                onTriggered: tbTool.handleReplaceAction(editor.text.text)
            }
        }

        CMenu {
            id : toolsMenu
            title: qsTr("Count")
            Action {
                text: qsTr("Word Count: ") + editor.currentWordCount
            }
            Action {
                text: qsTr("Character Count: ") + editor.currentCharacterCount
            }
            Action {
                text: qsTr("Non-space Character Count: ") + editor.currentCharacterCountNoSpaces
            }
        }

    }


    RowLayout {
        anchors.fill: parent
        spacing: 0

        CSidebar {
            id: sidebar
            dragWindow: root
            Layout.preferredWidth: 50
            Layout.fillHeight: true
        }

        SplitView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            // Customized handle to drag between the Navigation and the Editor.
            handle: Rectangle {
                implicitWidth: 5
                color: Colors.color2
                border.color: SplitHandle.hovered ? Colors.color2 : Colors.background
                opacity: SplitHandle.hovered || navigationView.width < 15 ? 1.0 : 0.2

                Behavior on opacity {
                    OpacityAnimator {
                        duration: 1000
                    }
                }
            }

            Rectangle {
                id: navigationView
                color: Colors.surface1
                SplitView.preferredWidth: 300
                SplitView.fillHeight: true
                // The stack-layout provides different views, based on the
                // selected buttons inside the sidebar.
                StackLayout {
                    anchors.fill: parent
                    currentIndex: sidebar.currentTabIndex

                    // Shows the help text.
                    /*
                    Text {
                        anchors.leftMargin: 10
                        anchors.topMargin: 10
                        text: qsTr("This is a field")
                        wrapMode: TextArea.Wrap
                        color: Colors.text
                    }
                    */

                    // Shows the files on the file system.
                    FileSystemView {
                        id: fileSystemView
                        editor: editor
                        color: Colors.surface1
                        onNoteClicked: index => {
                            editor.controller.openNote(index)
                        }
                        onFolderClicked: index => {
                                             editor.controller.openFolder(index)
                                         }
                    }


                    ToDoList {}
                    Text {
                        anchors.leftMargin: 10
                        anchors.topMargin: 10
                        text: qsTr("This is a calender")
                        wrapMode: TextArea.Wrap
                        color: Colors.text

                    }
                    Pomodoro {
                        id: pomodoro
                        SplitView.fillWidth: true
                        SplitView.fillHeight: true
                        color: Colors.surface1
                    }
                }
            }

            // The main view that contains the editor.

            CEditor {
                id: editor
                showLineNumbers: root.showLineNumbers
                currentNoteId: 0  // TODO: Change later
                explorer: fileSystemView
                renderer: renderer
                //currentFilePath: root.currentFilePath
                SplitView.preferredWidth: 900
                SplitView.fillHeight: true
            }

            Text {
                id: renderer
                text: ""

                textFormat: TextEdit.RichText

                SplitView.preferredWidth: 900
                SplitView.fillHeight: true

                font: Colors.font
                color: Colors.textFile
            }
        }
    }
}

