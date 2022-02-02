import QtQuick 2.0
import QtQuick.Window 2.0
Rectangle{
    id:body
    color: "transparent";
    anchors.centerIn: body
    property int duration_music
    property bool pause : true
    property bool runing: false
    function set_duration(duration1){
      runing =  duration1
    }
    function set_pause(check){
        body.pause =  check
    }
    Image {
        id: name
        source: "qrc:///Image/Disc.png"
        anchors.centerIn:  body
        fillMode: Image.PreserveAspectFit
        width: 250
        RotationAnimation on rotation {
            from: 0
            to: 720
            duration: 10000
            loops:  Animation.Infinite
            running: body.runing
            paused : body.pause
            }
        }
    }



