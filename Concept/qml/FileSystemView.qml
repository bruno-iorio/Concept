// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import QtQuick.Effects
import QtQuick.Controls.Basic
import Concept

pragma ComponentBehavior: Bound

Rectangle {
    id: root

    signal noteClicked(var index)
    signal reset()

    onReset: {
        for (let i = 0; i < explorerTreeView.model.rowCount(); i++)
            explorerTreeView.toggleExpanded(i)
    }

    required property var editor

    TreeView {
        id: explorerTreeView

        property int lastIndex: -1

        anchors.fill: parent
        model: ExplorerModel
        // rootIndex: FileSystemModel.rootIndex
        boundsBehavior: Flickable.StopAtBounds
        boundsMovement: Flickable.StopAtBounds
        clip: true

        Component.onCompleted: {
            for (let i = 0; i < model.rowCount(); i++)
                explorerTreeView.toggleExpanded(i)
        }

        // The delegate represents a single entry in the filesystem.
        delegate: TreeViewDelegate {
            id: treeDelegate
            indentation: 8
            implicitWidth: explorerTreeView.width > 0 ? explorerTreeView.width : 250
            implicitHeight: 25

            required property int index
            property var modelType: !treeDelegate.hasChildren ? 1 : 2
            property var dataId: treeDelegate.treeView.model.data(treeDelegate.treeView.index(treeDelegate.row, 0), Qt.DisplayRole)
            // property var dataName: treeDelegate.treeView.model.data(
            //     treeDelegate.treeView.index(treeDelegate.row, 0), Qt.DisplayRole
            // )

            indicator: Image {
                id: directoryIcon

                x: treeDelegate.leftMargin + (treeDelegate.depth * treeDelegate.indentation)
                anchors.verticalCenter: parent.verticalCenter
                source: treeDelegate.hasChildren ? (treeDelegate.expanded
                            ? "icons/folder_open.svg" : "icons/folder_closed.svg")
                        : "icons/generic_file.svg"
                sourceSize.width: 20
                sourceSize.height: 20
                fillMode: Image.PreserveAspectFit

                smooth: true
                antialiasing: true
                asynchronous: true
            }

            // Change contentItem's color based on whether the item is selected or not.
            contentItem: Text {
                clip: false
                text: treeDelegate.treeView.model.getTitle(treeDelegate.dataId, treeDelegate.modelType)
                elide: Text.ElideRight
                color: Colors.text
            }

            background: Rectangle {
                color: (treeDelegate.index === explorerTreeView.lastIndex)
                    ? Colors.selection
                    : (hoverHandler.hovered ? Colors.active : "transparent")
            }

            // We color the directory icons with this MultiEffect, where we overlay
            // the colorization color ontop of the SVG icons.
            MultiEffect {
                id: iconOverlay

                anchors.fill: directoryIcon
                source: directoryIcon

                colorizationColor: (treeDelegate.expanded && treeDelegate.hasChildren)
                                         ? Colors.color2 : Colors.folder
                colorization: 1.0
                brightness: 1.0
            }

            HoverHandler {
                id: hoverHandler
            }

            TapHandler {
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                onSingleTapped: (eventPoint, button) => {
                    switch (button) {
                        case Qt.LeftButton:
                            explorerTreeView.toggleExpanded(treeDelegate.row)
                            // If this model item doesn't have children, it means it's
                            // representing a file.
                            if (!treeDelegate.hasChildren && treeDelegate.modelType === 1)
                                editor.controller.openNote(treeDelegate.dataId)
                        break;
                        case Qt.RightButton:
                            if (treeDelegate.hasChildren){
                                folderContextMenu.popup();
                                console.log("Folder context menu");
                            }
                            else{
                                noteContextMenu.popup();
                                console.log("Note context menu");
                            }
                        break;
                    }
                }
            }

            CMenu {
                id: folderContextMenu
                Action {
                    text: qsTr("New note")
                    onTriggered: console.log(true) // TODO: Create note at this layer
                }
                Action {
                    text: qsTr("New folder")
                    onTriggered: console.log(true) // TODO: Create a sibling folder
                }
                Action {
                    text: qsTr("Rename")
                    onTriggered: {
                        if (editor) {
                            editor.controller.renameFolder(editor.currentFolderId, editor.currentFolderName);

                        }
                    }
                }
                Action {
                    text: qsTr("Delete")
                    onTriggered: console.log(true) // TODO: Delete this folder and all its contents
                }
            }

            CMenu {

                id: noteContextMenu
                Action {
                    text: qsTr("Rename")
                    onTriggered: {
                                     if (editor) {
                                         editor.controller.renameNote(editor.currentNoteId, editor.currentNoteTitle, editor.text.text);

                                     }
                        }
                }
                Action {
                    text: qsTr("Delete")
                    onTriggered: {
                        if (editor) {
                            editor.controller.deleteNote(editor.currentNoteId, editor.currentNoteTitle, editor.text.text);

                        }
                    } // TODO: Delete this note
                }


            }



        }



        // Provide our own custom ScrollIndicator for the TreeView.
        ScrollIndicator.vertical: ScrollIndicator {
            active: true
            implicitWidth: 15

            contentItem: Rectangle {
                implicitWidth: 6
                implicitHeight: 6

                color: Colors.color1
                opacity: explorerTreeView.movingVertically ? 0.5 : 0.0

                Behavior on opacity {
                    OpacityAnimator {
                        duration: 500
                    }
                }
            }
        }
    }
}

