import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Concept

pragma ComponentBehavior: Bound

Rectangle {
    id: root

    anchors.fill: parent

    color: Colors.surface1

    RowLayout {
        // Center on top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top

        // Two buttons with width of half the parent
        Button {
            text: "New"
            Layout.fillWidth: true
        }

        Button {
            text: "Clear"
            Layout.fillWidth: true
        }
    }
}
