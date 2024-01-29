import QtQuick
import QtQuick.Effects
import QtQuick.Controls.Basic
import Concept
import CustomControls 1.0

Rectangle {
    id: root

    anchors.fill: parent

    color: Colors.surface1

      // Header for column1 with the name My Tasks
      Rectangle {
          id: column1Header
          width: parent.width
          height: parent.height * 0.13
          color: Colors.surface1

          Text {
              id: myliststext
              text: "My Tasks"
              font.pixelSize: column1Header.height * 0.15
              font.family: "Helvetica"
              color: Colors.text
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
          color: Colors.surface1

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
              color: Colors.list

              // Anchor the top of list to the bottom of column1Header
                // anchors.top: column1Header.bottom

              TextInput {
                  property bool listNameInputClicked: false

                  id: listNameInput
                  anchors.fill: parent
                  //text: "List Name" // Initial text
                  text: name
                  font.pixelSize: column1Header.height * 0.14
                  font.family: "Helvetica"
                  selectByMouse: true // Allow text selection by mouse
                  color: listNameInput.listNameInputClicked ? Colors.clickedList : Colors.text
                  verticalAlignment: Text.AlignVCenter
                  readOnly: true
                  leftPadding: 20

                  // Handle mouse clicks
                  MouseArea {
                  anchors.fill: parent
                  onDoubleClicked: {
                      // Handle click event here
                      console.log("List name clicked!")
                      listNameInput.readOnly = !listNameInput.readOnly
                      if (!listNameInput.readOnly){
                        listNameInput.forceActiveFocus();
                      }
                      //fileListModel.remove(index)
                      }
                  }

                  // Handle editing finished event
                  onEditingFinished: {
                   // Handle editing finished event here
                      console.log("Editing finished:", listNameInput.text.trim())
                      listNameInput.listNameInputClicked = false;
                      listNameInput.readOnly = true;
                      }
                  onFocusChanged: {
                      if (!listNameInput.focused){
                          console.log("Focus lost:", listNameInput.text.trim())
                          listNameInput.listNameInputClicked = false;
                          listNameInput.readOnly = true;
                      }
                  }
                  Keys.onReturnPressed:{
                      if (!listNameInput.readOnly){
                          console.log("Enter key pressed:", listNameInput.text.trim())
                          listNameInput.listNameInputClicked = false;
                          listNameInput.readOnly = true;
                      }
                  }
                  }
                  
                  ToolButton {
                    id: toolButton
                    text: "x"
                    anchors.right: parent.right
                    contentItem: Text {
                                    color: Colors.text
                                    text: toolButton.text
                                    font.pixelSize: toolButton.height * 0.7
                                }
                    background: Rectangle {
                            color: Colors.list
                        }
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
          color: Colors.surface1
          anchors.top: list.bottom
      // "Add Task" button
          Button {
              id: newListButton
              text: "Add Task"
              anchors.centerIn: parent
              width: parent.width * 0.4
              contentItem: Text {
                              color: Colors.text
                              font.pixelSize: newListButtonColumn.height * 0.4
                              anchors.centerIn: parent
                              text: newListButton.text
                              verticalAlignment: Text.AlignVCenter
                              horizontalAlignment: Text.AlignHCenter
                          }
              background: Rectangle {
                      color: Colors.list
                  }

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
