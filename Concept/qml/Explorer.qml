import QtQuick
import Concept

// Create a list widget that displays the list of notes
ListView {
    id: listView
    anchors.fill: parent
    model: ConceptModel {
        id: conceptModel
    }
    delegate: ConceptDelegate {
        id: conceptDelegate
        width: parent.width
        height: 50
        concept: concept
    }
}
