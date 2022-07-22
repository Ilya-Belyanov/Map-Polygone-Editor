import QtQuick 2.15
import QtQuick.Window 2.15

import QtLocation 5.6
import QtPositioning 5.6

import "."

Window {
    width: 600
    height: 600
    maximumHeight: height
    maximumWidth: width
    minimumHeight: height
    minimumWidth: width
    visible: true
    title: qsTr("Polygone Editor")

    PolygoneEditor{
        id: polygoneEditor
        anchors.fill: parent
    }
}
