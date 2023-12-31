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
    property alias rootIndex: explorerTreeView.rootIndex

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
            required property var modelData
            property var modelType: !treeDelegate.hasChildren ? "file" : "directory"
            property var dataId: treeDelegate.treeView.model.data(
                treeDelegate.treeView.index(modelData.row, 1), Qt.DisplayRole
            )
            property var dataName: treeDelegate.treeView.model.data(
                treeDelegate.treeView.index(modelData.row, 0), Qt.DisplayRole
            )

            visible: modelData.column === 0

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
                text: treeDelegate.dataName
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
                            let idData = treeDelegate.treeView.model.data(
                                treeDelegate.treeView.index(modelData.row, 1), Qt.DisplayRole
                            )
                            if (!treeDelegate.hasChildren && treeDelegate.modelType === "file")
                                root.noteClicked(idData)
                        break;
                        case Qt.RightButton:
                            if (treeDelegate.hasChildren)
                                contextMenu.popup();
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
                    onTriggered: console.log(true) // TODO: Rename this folder
                }
                Action {
                    text: qsTr("Delete")
                    onTriggered: console.log(true) // TODO: Delete this folder and all its contents
                }
            }

            CMenu {
                id: noteContextMenu
                Action {
                    text: qsTr("New note")
                    onTriggered: console.log(true) // TODO: Create note at this layer
                }
                Action {
                    text: qsTr("Rename")
                    onTriggered: console.log(true) // TODO: Rename this note
                }
                Action {
                    text: qsTr("Delete")
                    onTriggered: console.log(true) // TODO: Delete this note
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
