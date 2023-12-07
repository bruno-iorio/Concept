import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick.Window 2.2
import Concept

Rectangle {
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight

    // This is the title bar
    Rectangle {
        id: nameBar
        width: parent.width
        height: 130
        color: "#A1B5D8"

        //Title Concept
        Text {
            text: "Concept"
            id: conceptText
            font.pixelSize: 80
            font.family: "Helvetica"
            anchors.left: parent.left
            verticalAlignment: Text.AlignVCenter
            leftPadding: 200
        }

        //spacing item
        Item {
            id: spacerTitleHelp
            anchors.left: conceptText.right
            width: 2000
        }

        // "Help" button
        Button {
            id: helpButton
            text: "Help"
            font.pixelSize: 30
            anchors.left: spacerTitleHelp.right
            anchors.verticalCenter: parent.verticalCenter
        }

        //spacing item
        Item {
            id: spacerHelpSearch
            anchors.left: helpButton.right
            width: 200
        }

        // Search Bar
        TextField {
            id: searchBar
            placeholderText: "Search..."
            width: 500
            height: 80
            anchors.left: spacerHelpSearch.right
            anchors.verticalCenter: parent.verticalCenter
        }

        //spacing item
        Item {
            id: spacerSearchButton
            anchors.left: searchBar.right
            width: 50
        }

        // "Search" button
        Button {
            id: searchButton
            text: "Search"
            font.pixelSize: 30
            anchors.left: spacerSearchButton.right
            anchors.verticalCenter: parent.verticalCenter
        }

        //spacing item
        Item {
            width: 200
            anchors.left: searchButton.right
        }

    }

    // Main Content with three columns
    Row {
        id: mainContentRow
        width: parent.width
        height: parent.height - nameBar.height
        anchors.top: nameBar.bottom

        // Column 1
        Rectangle {
            id: column1Container
            width: mainContentRow.width * 0.25
            height: mainContentRow.height
            color: "#F0EEE9"
        }

        // Column 2
        Rectangle {
            id: column2Container
            width: mainContentRow.width * 0.55
            height: mainContentRow.height
            color: "#F0EEE9"

            Rectangle {
                id: chosenListColumn
                width: mainContentRow.width * 0.3 * 0.003
                height: column2Container.height
                color: "grey"
            }
        }

        // Column 3
        Rectangle {
            id: column3Container
            width: mainContentRow.width * 0.2
            height: mainContentRow.height
            color: "#F0EEE9"

            Rectangle {
                id: pomodoroColumn
                width: column3Container.width * 0.003
                height: column3Container.height
                color: "grey"
            }
        }
    }
}
