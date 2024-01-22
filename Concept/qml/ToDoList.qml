import QtQuick
import QtQuick.Effects
import QtQuick.Controls.Basic
import Concept
import CustomControls 1.0

Rectangle {
    id: root

    anchors.fill: parent

    color: Colors.surface1

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
              text: "My Tasks"
              font.pixelSize: column1Header.height * 0.15
              font.family: "Helvetica"
              horizontalAlignment: Text.AlignHCenter
              verticalAlignment: Text.AlignVCenter
              anchors.centerIn: parent
          }
      }

      Rectangle {
          id: list
          anchors.top: column1Header.bottom
          width: parent.width
          height: parent.height * 0.50
          color: "#ffff99" // Modify later
          border.color: "grey"
          border.width: 1

      ListView {
          id: listView

          anchors {
          fill: parent
          margins: 2
          }

          model: fileListModel

          delegate: Rectangle {

              height: 50
              width: column1Header.width * 0.99

              // Anchor the top of list to the bottom of column1Header
                // anchors.top: column1Header.bottom

              TextInput {
                  property bool listNameInputClicked: false

                  id: listNameInput
                  anchors.fill: parent
                  //text: "List Name" // Initial text
                  text: name
                  font.pixelSize: column1Header.height * 0.10
                  font.family: "Helvetica"
                  selectByMouse: true // Allow text selection by mouse
                  color: listNameInput.listNameInputClicked ? "blue" : "black"
                  verticalAlignment: Text.AlignVCenter
                  readOnly: !listNameInput.listNameInputClicked // Set to true to make it read-only
                  leftPadding: 20

                  // Handle mouse clicks
                  MouseArea {
                  anchors.fill: parent
                  onClicked: {
                      // Handle click event here
                      console.log("List name clicked!")
                      listNameInput.listNameInputClicked = true
                      //fileListModel.remove(index)
                      }
                  }

                  // Handle editing finished event
                  onEditingFinished: {
                   // Handle editing finished event here
                      console.log("Editing finished:", listNameInput.text.trimmed())
                      listNameInput.listNameInputClicked = false
                      }
                  }
                  
                  ToolButton {
                    text: "x"
                    anchors.right: parent.right
                    onClicked: {
                        fileListModel.remove(index)
                    }
                  }

          }

          spacing: 4
          cacheBuffer: 50
      }
      }

      Rectangle {
          id: newListButtonColumn
          width: parent.width
          height: parent.height * 0.05
          color: "#ffcccc" // Modify later
          border.width: 1
          anchors.top: list.bottom
      // "Add Task" button
          Button {
              id: newListButton
              text: "Add Task"
              font.pixelSize: newListButtonColumn.height * 0.40
              anchors.horizontalCenter: newListButtonColumn.horizontalCenter
              anchors.verticalCenter: newListButtonColumn.verticalCenter

              MouseArea {
                  anchors.fill: parent
                  onClicked: {
                          // Handle click event here
                          fileListModel.add("")
                      }
                  }

          }
      }
  }
