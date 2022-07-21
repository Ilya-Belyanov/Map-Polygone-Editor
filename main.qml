import QtQuick 2.15
import QtQuick.Window 2.15

import QtLocation 5.6
import QtPositioning 5.6

//import "."

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Polygone Editor")

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
        center: QtPositioning.coordinate(59.9386, 30.3141)
        zoomLevel: 12

        MapItemView {
            id: area
            model: polygonemodel
            delegate: Component {
                MapPolygon {
                    color: 'green'
                    path:  polygonemodel.coordinates
                    width: 25;
                }
            }
        }

        MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                propagateComposedEvents: true

                onClicked: {
                    console.log(map.toCoordinate(Qt.point(mouse.x,mouse.y)))
                    if(!polygonemodel.hasCatchedCoordinate)
                        polygonemodel.addCoordinate(map.toCoordinate(Qt.point(mouse.x,mouse.y)))
                    polygonemodel.resetCatchedCoordinate()
                }
                onPressed: {
                        //mouse.accepted = false
                    console.log("Pressed", mouseX)
                    polygonemodel.catchCloseCoordinate(map.toCoordinate(Qt.point(mouse.x,mouse.y)))
                    console.log("Catched", polygonemodel.hasCatchedCoordinate())
                }
                onReleased: {
                        //mouse.accepted = false
                    console.log("Released", mouseX)
                    }
                onPositionChanged:{
                    console.log("PositionChanged", mouseX)
                    console.log("bool ", polygonemodel.hasCatchedCoordinate)
                    if(polygonemodel.hasCatchedCoordinate)
                        polygonemodel.moveCatchedCoordinate(map.toCoordinate(Qt.point(mouse.x,mouse.y)))
                }
            }
    }
}
