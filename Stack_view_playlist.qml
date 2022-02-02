import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQml.Models 2.2
Item {
    id : item
    property variant list_file_name: []
       property string  list
    function test(file_name){
        m_List_model.append({"name" : file_name}) ;
    }
    function set_file_name( file_name){
        list_file_name =  file_name
    }
    function get_size(name) {
        list =  name
    }

    function get_List_of_File_Name(file_name){
        m_List_model.append({"name" : file_name}) ;
    }
    function inset_file_name_into_grid(){
        for(var i = 0; i <= list_file_name.length ; i++){
            m_List_model.append({"name" : list_file_name[i]}) ;
        }
    }

    Rectangle{
        id : rec_main
        width: 700
        height:  400
        color: Qt.rgba(255, 206, 255, 0.1)
        radius: 4
        Row{
            id : text_field
            width : 500
            height: 40
            focus:  true

       Button{
           id : _Button
           width: 40
           height: 25
           background:Rectangle {
               color:  Qt.rgba(255, 206, 255, 0.1)
               radius: 2
               implicitWidth: 100
                implicitHeight: 24
                border.color: "#333"
                 border.width: 1
           }
           Image {
               id: image_Search
               source: "qrc:///Image/Search.png"
               width:  40
               height:  25
               anchors.fill: parent.Center
           }
       }

        TextField{
                id: searchField
                width: 350
                height: 25
                visible: true
                background:Rectangle {
                    color:  Qt.rgba(255, 206, 255, 0.1)
                    radius: 2
                    implicitWidth: 100
                     implicitHeight: 24
                     border.color: "#333"
                      border.width: 1
                }
                placeholderText: "asdasd here...."

            }
        Button {
            id : _add_Button
            width: 40
            height: 25
            background:Rectangle {
                color:  Qt.rgba(255, 206, 255, 0.1)
                radius: 2
                implicitWidth: 100
                 implicitHeight: 24
                 border.color: "#333"
                  border.width: 1
            }
            Image {
                id: add_folder
                source: "qrc:/Image/Add.png"
                width:  40
                height:  25
                anchors.fill: parent.Center
            }
        }
        }
        ListModel{
            id : m_List_model
            }
        GridView{
            id : grid_Model
            anchors.fill: parent
            model: m_List_model
            anchors.topMargin: 40
            anchors.leftMargin: 12
                   cellWidth:   155
                   cellHeight: 45


            delegate:
                Column {
                Rectangle{
                    id :rec_list_model
                    width: 150
                    height: 40
                    color: Qt.rgba(60, 60, 69, 0.5)
                    radius: 10
                    Row{
                        Rectangle{
                            id :rec
                            width: 40
                            height: 40
                            radius: 5
                            color: Qt.rgba(255, 206, 255, 0.1)
                            Image {
                                id: file_folder
                                source: "qrc:///Image/folder.png"
                                width: 40
                                height: 40
                                anchors.fill: rec
                                fillMode:  Image.PreserveAspectFit
                            }

                        }
                        Column{
                            Text{
                                text: ' '
                                font.pointSize: 10
                            }
                            Text {
                                text: ' '  + name                            }
                        }
                    }
                    MouseArea {
                        id : mouse_area
                        anchors.fill: parent
                        hoverEnabled  :  true
                        acceptedButtons: Qt.LeftButton | Qt.RightButton
                         cursorShape: Qt.PointingHandCursor

                        onEntered:{

                            parent.color =  Qt.rgba(255, 206, 255, 0.2)}
                        onExited: {
                            parent.color =  Qt.rgba(255, 206, 255, 0.5)
                          }

                    }
                }

         }



            }

        }
    ListModel{
        id : m_List_model1
        }
   Playlist{

   }
}
