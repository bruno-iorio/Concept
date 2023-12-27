// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import QtQuick.Controls.Basic
import Concept

ApplicationWindow {
    id: root
    width: 650
    height: 550
    flags: Qt.Window | Qt.FramelessWindowHint
    color: Colors.surface1

    menuBar: CMenuBar {
        id: menuBar

        dragWindow: root
        implicitHeight: 30
        infoText: "About Qt"
    }

    Image {
        id: logo

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 20

        source: "icons/qt_logo.svg"
        sourceSize.width: 80
        sourceSize.height: 80
        fillMode: Image.PreserveAspectFit

        smooth: true
        antialiasing: true
        asynchronous: true
    }

    ScrollView {
        anchors.top: logo.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 20

        TextArea {
            selectedTextColor: Colors.textFile
            selectionColor: Colors.selection
            horizontalAlignment: Text.AlignHCenter
            textFormat: Text.RichText

            text: qsTr("<h3>About Concept Project</h3>")
            color: Colors.textFile
            wrapMode: Text.WordWrap
            readOnly: true
            antialiasing: true
            background: null

            onLinkActivated: function(link) {
                Qt.openUrlExternally(link)
            }
        }
    }

    ResizeButton {
        resizeWindow: root
    }
}
