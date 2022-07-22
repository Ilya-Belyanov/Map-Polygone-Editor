import QtQuick 2.0

import QtLocation 5.6
import QtPositioning 5.6

Item {
    Plugin {
        id: osmMapPlugin
        name: "osm"

        PluginParameter {
                    name: "osm.mapping.providersrepository.disabled"
                    value: "true"
                }
        PluginParameter {
                    name: "osm.mapping.cache.directory"
                    value: "./mapCache/osm"
                }

        PluginParameter {
                    name: "osm.mapping.providersrepository.address"
                    value: "http://maps-redirect.qt.io/osm/5.15/"
                }
        PluginParameter {
                    name: "osm.useragent";
                    value: "PolygoneEditor"
                }
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: osmMapPlugin
        gesture.enabled: false
        center: QtPositioning.coordinate(59.9386, 30.3141) // СПБ
        zoomLevel: 12

        MapPolygon {
            color: 'white'
            path:  polygonemodel.coordinates
            width: 30;
        }

        MapItemView {
            id: area_circle
            model: polygonemodel
            delegate: Component {
                MapCircle{
                    required property real lat
                    required property real lon
                    required property bool is_catched
                    border.color: is_catched ? "red": "green"
                    color: "black"
                    border.width: 1
                    center: QtPositioning.coordinate(lat, lon)
                    radius: 50
                }
            }
        }

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            propagateComposedEvents: true
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            property int lastPressedButtons
            onClicked: {
                if(lastPressedButtons & Qt.RightButton)
                    return
                if(!polygonemodel.hasCatchedCoordinate)
                    polygonemodel.addCoordinate(map.toCoordinate(Qt.point(mouse.x,mouse.y)))
                polygonemodel.resetCatchedCoordinate()
            }
            onPressed: {
                lastPressedButtons = pressedButtons
                if(lastPressedButtons & Qt.LeftButton)
                    polygonemodel.catchCloseCoordinate(map.toCoordinate(Qt.point(mouse.x,mouse.y)))
            }
            onReleased: {
                if(lastPressedButtons & Qt.RightButton)
                    polygonemodel.removeCloseCoordinate(map.toCoordinate(Qt.point(mouse.x,mouse.y)))
                }
            onPositionChanged:{
                if(polygonemodel.hasCatchedCoordinate && (lastPressedButtons & Qt.LeftButton))
                    polygonemodel.moveCatchedCoordinate(map.toCoordinate(Qt.point(mouse.x,mouse.y)))
            }
        }
    }
}
