import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick.Window 2.2
import CustomControls 1.0


Window {
    width: Screen.width
    height: Screen.height
    title: "Concept"
    visible: true

    /*TextEditor{
        id: texteditorWindow

    }*/

    // This is the title bar
    Rectangle {
        id: nameBar
        width: parent.width
        height: parent.height * 0.07 // Set a percentage of the screen height
        color: "#A1B5D8"
        border.color: "grey"
        border.width: 1

        // Title Concept
        Text {
            text: "Concept"
            id: conceptText
            font.pixelSize: nameBar.height * 0.6 // Set a percentage of the nameBar height
            font.family: "Helvetica"
            anchors.left: parent.left
            verticalAlignment: Text.AlignVCenter
            anchors.leftMargin: parent.width * 0.07
        }

        // Spacing item
        Item {
            id: spacerTitleHelp
            anchors.left: conceptText.right
            width: parent.width * 0.45 // Set a percentage of the screen width
        }


        // "Help" button
        MainHelp {
            id: helpItem
            onShowRedSquare: redSquareManager.showRedSquare()
        }



        Button {
            id: helpButton
            text: "Help"
            font.pixelSize: nameBar.height * 0.25
            anchors.left: spacerHelpSearch.right
            anchors.verticalCenter: parent.verticalCenter

            onClicked: {
                    helpItem.showHelpMenu();

                }


        }



        // Spacing item
        Item {
            id: spacerHelpSearch
            anchors.left: searchButton.right
            width: parent.width * 0.07 // Set a percentage of the screen width
        }

        // Search Bar
        TextField {
            id: searchBar
            placeholderText: "Search..."
            width: parent.width * 0.12 // Set a percentage of the screen width
            height: nameBar.height * 0.55 // Set a percentage of the nameBar height
            anchors.left: spacerTitleHelp.right
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
            font.pixelSize: nameBar.height * 0.25 // Set a percentage of the nameBar height
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
            width: parent.width * 0.2
            height: mainContentRow.height
            color: "#F0EEE9"
            // Header for column1 with the name My Lists
            Rectangle {
                id: column1Header
                width: parent.width
                height: parent.height * 0.13
                color: "#ffcc99" // Modify later
                border.color: "grey"
                border.width: 1

                Text {
                    id: myliststext
                    text: "My Lists"
                    font.pixelSize: nameBar.height * 0.4
                    font.family: "Helvetica"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    anchors.centerIn: parent
                }
            }

            // First basic list for column1
            Rectangle {
                id: column1list1
                width: parent.width
                height: parent.height * 0.05
                color: "#ffff99" // Modify later
                border.color: "grey"
                border.width: 1

                // Anchor the top of column1list1 to the bottom of column1Header
                anchors.top: column1Header.bottom
                property bool listNameInputClicked: false

                // Text input for list name
                TextInput {
                    id: listNameInput
                    anchors.fill: parent
                    text: "List Name" // Initial text
                    font.pixelSize: nameBar.height * 0.3
                    font.family: "Helvetica"
                    selectByMouse: true // Allow text selection by mouse
                    color: column1list1.listNameInputClicked ? "blue" : "black"
                    verticalAlignment: Text.AlignVCenter
                    readOnly: !column1list1.listNameInputClicked // Set to true to make it read-only
                    leftPadding: 20

                    // Handle mouse clicks
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            // Handle click event here
                            console.log("List name clicked!")
                            column1list1.listNameInputClicked = true
                        }
                    }

                    // Handle editing finished event
                    onEditingFinished: {
                        // Handle editing finished event here
                        console.log("Editing finished:", listNameInput.text.trimmed())
                        column1list1.listNameInputClicked = false
                    }
                }
            }
            Rectangle {
                id: newListButtonColumn
                width: parent.width
                height: parent.height * 0.05
                color: "#ffcccc" // Modify later
                border.width: 1
                anchors.top: column1list1.bottom
            // "New list" button
                Button {
                    id: newListButton
                    text: "New List"
                    font.pixelSize: nameBar.height * 0.2
                    anchors.horizontalCenter: newListButtonColumn.horizontalCenter
                    anchors.verticalCenter: newListButtonColumn.verticalCenter
                }
            }
        }

        // Column 2
        Rectangle {
            id: column2Container
            width: parent.width * 0.6
            height: mainContentRow.height
            color: "#F0EEE9"

            //header for column2 with 'View' 'Edit' functionnality to add the text editor
            Rectangle{
                id:column2Header
                width: parent.width
                height: parent.height * 0.05
                color: "#A1B5D8" //modify later, for now its to show you new stuff
                border.color: "grey"
                border.width: 1

                Item{
                    id : editview
                    width : editButton.width * 0.07
                    anchors.right : editButton.left
                }

                Item{
                    id : viewnew
                    width : editButton.width * 0.07
                    anchors.right : viewButton.left
                }

                // "Edit" button
                Button {
                    id: editButton
                    text: "Edit"
                    font.pixelSize: column2Header.height * 0.25
                    anchors.right: column2Header.right
                    anchors.verticalCenter: column2Header.verticalCenter
                    height : column2Header.height * 0.95
                }

                // "View" button
                Button {
                    id: viewButton
                    text: "View"
                    font.pixelSize: column2Header.height * 0.25
                    anchors.right: editview.left
                    anchors.verticalCenter: column2Header.verticalCenter
                    height : column2Header.height * 0.95
                }
                // "New" Button
                Button {
                    id: newButton
                    text: "New"
                    font.pixelSize: column2Header.height * 0.25
                    anchors.right: viewnew.left
                    anchors.verticalCenter: column2Header.verticalCenter
                    height : column2Header.height * 0.95
                    onClicked: textEditor.showEditor()



                    Pane {
                        id: redSquareItem
                        objectName: "redSquareItem"
                        visible: false
                        anchors.bottom : newButton.top
                        anchors.horizontalCenter: newButton.horizontalCenter

                        Label {
                            text : qsTr("Here!")
                            anchors.centerIn: parent
                        }

                        background: Rectangle {
                            width: newButton.width
                            height: newButton.height * 0.7
                            color: "red"
                        }

                        Timer {
                            id: hideTimer
                            interval: 7000  // 10 seconds in milliseconds
                            onTriggered: {
                                redSquareItem.visible = false;
                            }
                        }

                        onVisibleChanged: {
                            if (visible) {
                                // Start the timer when the red square becomes visible
                                hideTimer.start();
                            } else {
                                // Stop the timer when the red square is not visible
                                hideTimer.stop();
                            }
                        }
                    }
                }
            }

            Rectangle {
                id: chosenListColumn
                width: pomodoroColumn.width * 0.004
                height: column2Container.height
                color: "grey"
                //MouseArea {
                  //  anchors.fill: parent
                    //cursorShape: Qt.SizeHorCursor // Change cursor to horizontal resize

                    //property real startX: 0
                    //property real startWidth: 0

                    //onPressed: {
                      //  chosenListColumn.startX = mouse.x;
                        //chosenListColumn.startWidth = chosenListColumn.width;
                    //}

                    //onPositionChanged: {
                      //  let deltaX = mouse.x - chosenListColumn.startX;
                      //  let newWidth = chosenListColumn.startWidth + deltaX;

                        // Limit the width to a maximum of 500 pixels
                       // chosenListColumn.width = Math.min(500, Math.max(0, newWidth));
                       // column2Container.width = mainContentRow.width * 0.55 - chosenListColumn.width;
                       // column1Container.width = mainContentRow.width * 0.25;
                    //}

                    //onClicked: {
                        // Add this block to enable continuous resizing
                      //  chosenListColumn.startX = mouse.x;
                        //chosenListColumn.startWidth = chosenListColumn.width;
                    //}
                //}
            }
        }

        // Column 3
        Rectangle {
            id: pomodoroColumn
            width: parent.width * 0.2
            height: mainContentRow.height
            color: "#F0EEE9"

            Rectangle {
                id: column3Container
                width: pomodoroColumn.width * 0.004
                height: pomodoroColumn.height
                color: "grey"
            }

            Rectangle {
                id: spacerTitleBarStudyTimerText
                width: pomodoroColumn.width - column3Container.width
                height: mainContentRow.height * 0.05
                anchors.top: parent.top
                anchors.left:column3Container.right
                color: "#F0EEE9"
            }

            Text {
                text: "Study Timer"
                id: studyTimerText
                font.pixelSize: nameBar.height * 0.4
                font.family: "Helvetica"
                //anchors.left: column3Container.right
                verticalAlignment: pomodoroColumn.AlignVCenter
                anchors.top: spacerTitleBarStudyTimerText.bottom
                leftPadding: pomodoroColumn.width * 0.3
            }

            Rectangle {
                id: spacerStudyTimerTextTimerBlock
                width: pomodoroColumn.width - column3Container.width
                height: mainContentRow.height * 0.05
                anchors.top: studyTimerText.bottom
                anchors.left:column3Container.right
                color: "#F0EEE9"
            }

            Rectangle {
                id: timerBlock
                width: pomodoroColumn.width - column3Container.width
                height: mainContentRow.height * 0.2
                anchors.top: spacerStudyTimerTextTimerBlock.bottom
                anchors.left:column3Container.right
                color: "#C2D8B9"

                Row {
                    //spacing: 0

                    Button {
                        id: studyButton
                        text: "Break"
                        font.pixelSize: timerBlock.height * 0.07
                        width: timerBlock.width / 2
                        background: Rectangle{
                            color: "#738290"
                        //id: studyButton
                        //text: "Break"
                        //font.pixelSize: timerBlock.height * 0.07
                        //onClicked: startTimer(25)
                        }
                    }
                    Rectangle{
                        id: spacerButtonsTimerBlock
                        color: "white"
                        height: studyButton.height
                        width: timerBlock.width * 0.003
                    }

                    Button {
                        id: breakButton
                        text: "Continue"
                        font.pixelSize: timerBlock.height * 0.07
                        anchors.top: studyButton.top
                        width: timerBlock.width / 2 - spacerButtonsTimerBlock.width
                        background: Rectangle{
                            color: "#738290"
                        //id: studyButton
                        //text: "Break"
                        //font.pixelSize: timerBlock.height * 0.07
                        //onClicked: startTimer(25)
                        }
                    }

                }

                // Timer Display
                Text {
                    id: timerDisplay
                    text: "00:00"
                    font.pixelSize: timerBlock.height * 0.16
                    anchors.centerIn: parent
                }

                //Timer {
                    //id: countdownTimer
                    //interval: 1000
                    //onTriggered: updateTimerDisplay()
                //}

                //function startTimer(minutes) {
                    //countdownTimer.stop()
                    //countdownTimer.repeat = minutes * 60 * 1000
                    //countdownTimer.start()
                    //updateTimerDisplay()
                //}

                //function updateTimerDisplay() {
                    //var minutes = Math.floor(countdownTimer.repeat / 60000)
                    //var seconds = Math.floor((countdownTimer.repeat % 60000) / 1000)
                    //timerDisplay.text = Qt.formatDateTime(new Date(0, 0, 0, 0, minutes, seconds), "mm:ss")
                //}

            }
            Rectangle {
                id: button1
                width: pomodoroColumn.width - column3Container.width
                height: mainContentRow.height * 0.08
                anchors.top: timerBlock.bottom
                anchors.left:column3Container.right
                color: "#F0EEE9"

                ///SetFocusPeriod{
                   /// id : focusPeriod}


                Button{
                    id: setFocusPeriod
                    text: "Set focus period"
                    font.pixelSize: timerBlock.height * 0.07
                    anchors.centerIn: parent

                    onClicked : {
                        focusPeriod.showMenu();
                    }

                }
            }
            Rectangle {
                id: button2
                width: pomodoroColumn.width - column3Container.width
                height: mainContentRow.height * 0.08
                anchors.top: button1.bottom
                anchors.left:column3Container.right
                color: "#F0EEE9"
                Button{
                    id: start
                    text: "Start"
                    font.pixelSize: timerBlock.height * 0.07
                    anchors.centerIn: parent
                }
            }
            Rectangle {
                id: button3
                width: pomodoroColumn.width - column3Container.width
                height: mainContentRow.height * 0.08
                anchors.top: button2.bottom
                anchors.left:column3Container.right
                color: "#F0EEE9"
                Button{
                    id: stop
                    text: "Stop"
                    font.pixelSize: timerBlock.height * 0.07
                    anchors.centerIn: parent
                }
            }
            Rectangle {
                id: textQuestion
                width: pomodoroColumn.width - column3Container.width
                height: mainContentRow.height * 0.08
                anchors.top: button3.bottom
                anchors.left:column3Container.right
                color: "#F0EEE9"
                Text {
                    id: question
                    text: qsTr("Are you done with studying? See your progress here:")
                    anchors.centerIn: parent
                }
            }
            Rectangle{
                id: button4
                width: pomodoroColumn.width - column3Container.width
                height: mainContentRow.height * 0.02
                anchors.top: textQuestion.bottom
                anchors.left:column3Container.right
                color: "#F0EEE9"
                Button{
                    id: statistics
                    text: "Statistics"
                    font.pixelSize: timerBlock.height * 0.07
                    anchors.centerIn: parent
                }
            }
        }
    }
}

