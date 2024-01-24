//Pomodoro.qml

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import Concept
import CustomControls 1.0


Rectangle {

    id: root

    Rectangle {
        id: studyTimerBlock
        width: root.width
        height: root.height * 0.30
        anchors.top: root.top
        color: Colors.surface1

        /*
        Text {
            id: studyTimerText
            text: "Study Timer"
            font.pixelSize: studyTimerBlock.height * 0.17
            font.family: "Helvetica"
            color: Colors.text

            anchors.centerIn: parent
            //topPadding: root.height * 0.05
            //leftPadding: root.width * 0.40
            //bottomPadding: root.height * 0.05
        }*/
    }

    Rectangle {
        id: timerBlock
        width: root.width
        height: root.height * 0.15
        anchors.top: studyTimerBlock.bottom
        color: "#c4c8cc"

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
                }
                onClicked: myTimerStart.showBreakMenu();
            }
            Rectangle{
                id: spacerButtonsTimerBlock
                color: "white"
                height: studyButton.height
                width: timerBlock.width * 0.003
            }

            Button {
                id: breakButton
                text: "End break"
                font.pixelSize: timerBlock.height * 0.15
                anchors.top: studyButton.top
                width: timerBlock.width / 2 - spacerButtonsTimerBlock.width
                background: Rectangle{
                color: "#738290"
                //id: studyButton
                //text: "Break"
                //font.pixelSize: timerBlock.height * 0.07

                }
                onClicked: myTimerStart.continueTimer();
            }

        }

        // Timer Display
        Text {
            id: timerDisplay
            text: myTimerStart.get_time_string();
            font.pixelSize: timerBlock.height * 0.20
            anchors.centerIn: parent
            
        }
    }

    Connections {
                target: myTimerStart
                onTimeChanged: {
                    timerDisplay.text = myTimerStart.get_time_string();
                }
            }

    Rectangle {
        id: button1
        width: root.width
        height: root.height * 0.05
        anchors.top: timerBlock.bottom

        color: "#c4c8cc"


        Button{
            id: focusPeriodButton
            text: "Set focus period"
            font.pixelSize: timerBlock.height * 0.15
            anchors.centerIn: parent
            //color: "#E1D2B7"
            onClicked: myTimerStart.showTimeMenu();

        }
    }
    Rectangle {
        id: button2
        width: root.width
        height: root.height * 0.05
        anchors.top: button1.bottom

        color: "#c4c8cc"
        Button {
                    id: start
                    text: "Start"
                    font.pixelSize: timerBlock.height * 0.15
                    anchors.centerIn: parent
                    onClicked: myTimerStart.startTheTimer();
                }

    }
    Rectangle {
        id: button3
        width: root.width
        height: root.height * 0.05
        anchors.top: button2.bottom

        color: "#c4c8cc"
        Button{
            id: stop
            text: "End session"
            font.pixelSize: timerBlock.height * 0.15
            anchors.centerIn: parent
            onClicked: {
                myTimerStart.stopTimer();
            }
        }
    }
    Rectangle {
        id: textQuestion
        width: root.width
        height: root.height * 0.05
        anchors.top: button3.bottom

        color: "#c4c8cc"
        Text {
            id: question
            text: qsTr("See your progress here:")
            anchors.centerIn: parent
        }
    }
    Rectangle{
        id: button4
        width: root.width
        height: root.height * 0.05
        anchors.top: textQuestion.bottom

        color: "#c4c8cc"
        Button{
            id: statistics
            text: "Statistics"
            font.pixelSize: timerBlock.height * 0.15
            anchors.centerIn: parent
        }
    }

}
