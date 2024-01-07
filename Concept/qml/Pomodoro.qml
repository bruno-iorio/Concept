import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import Concept
import CustomControls 1.0

Rectangle {
    
    id: root
    
    Text {
        id: studyTimerText
        text: "Study Timer"
        font.pixelSize: 40
        font.family: "Helvetica"
        color: "white"
        
        anchors.top: root.top
        topPadding: root.height * 0.05
        leftPadding: root.width * 0.40
        bottomPadding: root.height * 0.05
    }

    Rectangle {
        id: timerBlock
        width: root.width
        height: root.height * 0.15
        anchors.top: studyTimerText.bottom
        color: "#C2D8B9"
        
        Row {
            //spacing: 0
            Button {
                id: studyButton
                text: "Break"
                font.pixelSize: timerBlock.height * 0.15
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
                font.pixelSize: timerBlock.height * 0.15
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
            font.pixelSize: timerBlock.height * 0.20
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
    
    SetFocusPeriod {
        id: focusItem
    }
    
    Rectangle {
        id: button1
        width: root.width
        height: root.height * 0.05
        anchors.top: timerBlock.bottom
        
        color: "#F0EEE9"


        Button{
            id: focusPeriodButton
            text: "Set focus period"
            font.pixelSize: timerBlock.height * 0.15
            anchors.centerIn: parent

            onClicked : {
                focusItem.showMenu();
            }

        }
    }
    Rectangle {
        id: button2
        width: root.width
        height: root.height * 0.05
        anchors.top: button1.bottom
        
        color: "#F0EEE9"
        Button{
            id: start
            text: "Start"
            font.pixelSize: timerBlock.height * 0.15
            anchors.centerIn: parent
        }
    }
    Rectangle {
        id: button3
        width: root.width
        height: root.height * 0.05
        anchors.top: button2.bottom
        
        color: "#F0EEE9"
        Button{
            id: stop
            text: "Stop"
            font.pixelSize: timerBlock.height * 0.15
            anchors.centerIn: parent
        }
    }
    Rectangle {
        id: textQuestion
        width: root.width
        height: root.height * 0.05
        anchors.top: button3.bottom
        
        color: "#F0EEE9"
        Text {
            id: question
            text: qsTr("Are you done with studying? See your progress here:")
            anchors.centerIn: parent
        }
    }
    Rectangle{
        id: button4
        width: root.width
        height: root.height * 0.05
        anchors.top: textQuestion.bottom
       
        color: "#F0EEE9"
        Button{
            id: statistics
            text: "Statistics"
            font.pixelSize: timerBlock.height * 0.15
            anchors.centerIn: parent
        }
    }
    
}