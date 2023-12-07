import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick.Window 2.2
import Concept

Rectangle {
    width: Screen.width
    height: Screen.height

    // This is the title bar
    Rectangle {
        id: nameBar
        width: parent.width
        height: parent.height * 0.1 // Set a percentage of the screen height
        color: "#A1B5D8"

        // Title Concept
        Text {
            text: "Concept"
            id: conceptText
            font.pixelSize: nameBar.height * 0.6 // Set a percentage of the nameBar height
            font.family: "Helvetica"
            anchors.left: parent.left
            verticalAlignment: Text.AlignVCenter
        }

        // Spacing item
        Item {
            id: spacerTitleHelp
            anchors.left: conceptText.right
            width: parent.width * 0.05 // Set a percentage of the screen width
        }

        // "Help" button
        Button {
            id: helpButton
            text: "Help"
            font.pixelSize: nameBar.height * 0.3 // Set a percentage of the nameBar height
            anchors.left: spacerTitleHelp.right
            anchors.verticalCenter: parent.verticalCenter
        }

        // Spacing item
        Item {
            id: spacerHelpSearch
            anchors.left: helpButton.right
            width: parent.width * 0.02 // Set a percentage of the screen width
        }

        // Search Bar
        TextField {
            id: searchBar
            placeholderText: "Search..."
            width: parent.width * 0.15 // Set a percentage of the screen width
            height: nameBar.height * 0.8 // Set a percentage of the nameBar height
            anchors.left: spacerHelpSearch.right
            anchors.verticalCenter: parent.verticalCenter
        }

        // Spacing item
        Item {
            id: spacerSearchButton
            anchors.left: searchBar.right
            width: parent.width * 0.01 // Set a percentage of the screen width
        }

        // "Search" button
        Button {
            id: searchButton
            text: "Search"
            font.pixelSize: nameBar.height * 0.3 // Set a percentage of the nameBar height
            anchors.left: spacerSearchButton.right
            anchors.verticalCenter: parent.verticalCenter
        }

        // Spacing item
        Item {
            width: parent.width * 0.04 // Set a percentage of the screen width
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
            width: parent.width * 0.25
            height: mainContentRow.height
            color: "#F0EEE9"
        }

        // Column 2
        Rectangle {
            id: column2Container
            width: parent.width * 0.55
            height: mainContentRow.height
            color: "#F0EEE9"

            Rectangle {
                id: chosenListColumn
                width: parent.width * 0.003
                height: column2Container.height
                color: "grey"
            }
        }

        // Column 3
        Rectangle {
            id: column3Container
            width: parent.width * 0.2
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
