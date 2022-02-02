import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQml.Models 2.2

Rectangle{
    id : main
    color:  Qt.rgba(255, 206, 255, 0.1)
    property  variant  list_table: []
    function slot_clear_list(_signal) {
        listModel.clear() ;
    }
    function load_table(name_of_table){
        listModel.append({"name" : name_of_table})

    }
    Component{
        id : listDel
        Rectangle{
            width:  341
            height:  45
            color:  Qt.rgba(255,205,255,0.1)
            radius: 15
            Row{
                id : row
                Rectangle {
                    id  : rec1
                    width: 40
                    height: 40
                    radius: 60
                    color : Qt.rgba(0, 53, 26, 0.1)
                    Image {
                        id: image1
                        width : 35
                        height:  35
                        anchors.centerIn: rec1
                        source: "qrc:/Image/Favorite.png"
                    }

                }
                Column{
                    width:  200
                    Text { text:' '+name }
                }
                Column{}
        }
            MouseArea{
                id : mouse_area
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                hoverEnabled  :  true
                onClicked: {
                    w.signal_name_of_table(name)
                }
                onEntered:{
                    parent.color =  Qt.rgba(255, 206, 255, 0.5)}
                onExited: {
                    parent.color =  Qt.rgba(255, 206, 255, 0.1)
                  }
            }
        }

    }
    ListView{
        id : listView123
        anchors.fill: parent
        anchors.topMargin: 10
        model: listModel
        delegate: listDel
        focus: true
        clip : true
        spacing:  5
    }
    ListModel{
        id : listModel
    }


}
