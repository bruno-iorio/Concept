// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

// main theme of colour and fonts we will use in the application
// this is a singleton object that can be accessed from anywhere in the application
// ideally all colours and fonts used in the app should be taken from here and not hardcoded

import QtQuick

pragma Singleton

QtObject {
    property bool isDarkMode: true
    // lightmode colors still need some changes for aesthetics 
    readonly property color background: isDarkMode ? "#292828" : "#FFFFFF"
    readonly property color surface1: isDarkMode ? "#171819" : "#EFEFEF"
    readonly property color surface2: isDarkMode ? "#090A0C" : "#CCCCCC"
    readonly property color text: isDarkMode ? "#D4BE98" : "#333333"
    readonly property color textFile: isDarkMode ? "#E1D2B7" : "#666666"
    readonly property color disabledText: isDarkMode ? "#2C313A" : "#999999"
    readonly property color selection: isDarkMode ? "#4B4A4A" : "#DDDDDD"
    readonly property color active: isDarkMode ? "#292828" : "#FFFFFF"
    readonly property color inactive: isDarkMode ? "#383737" : "#F0F0F0"
    readonly property color folder: isDarkMode ? "#383737" : "#F0F0F0"
    readonly property color icon: isDarkMode ? "#383737" : "#555555"
    readonly property color iconIndicator: isDarkMode ? "#D5B35D" : "#FFA500"
    readonly property color color1: isDarkMode ? "#A7B464" : "#3498DB"
    readonly property color color2: isDarkMode ? "#D3869B" : "#E74C3C"

    /* load fonts from directory */
    readonly property font font: Qt.font({
        family: "Roboto Mono",
        pixelSize: Qt.application.font.pixelSize
    })
    readonly property font largeFont: Qt.font({
        family: "Roboto Mono",
        pixelSize: Qt.application.font.pixelSize * 1.6
    })

    property DirectoryFontLoader directoryFontLoader: DirectoryFontLoader {
        id: directoryFontLoader
    }
}
