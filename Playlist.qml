import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQml.Models 2.2
import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

Item {
    id: main_item
    property int _index_: 0
    property int change: 0
    property  variant  list_fitler_Table_name :[]
    property  variant  list_fitler_music_playlist_name :[]


    function get_List_of_File_Name(file_name){
        m_List_model.append({"name" : file_name}) ;
    }
    function model_Load() {
        _index_ = 0 ;

        }
    function set_list_path_name(full_name , name , Author , qualification){
        listModel.append({"name" : name, "Author":Author , "INDEX" : _index_,
                            "Full_Name" : full_name , "Quality" : qualification})
        _index_++
    }    

    function clear_Grid_view(check){
        m_List_model.clear() ;
    }
    function clear_list_view(check) {
        listModel.clear() ;
    }
    function filter_Playlist_table(name_of_table) {
        var result = [name_of_table]
       list_fitler_Table_name.push(result)
    }
    function reloaod_playlist_table() {
        return list_fitler_Table_name
    }
    function filter_Playlist_music(full_name , name , Author , qualification) {
        var result = [full_name , name , Author , qualification]
       list_fitler_music_playlist_name.push(result)
        _index_ ++
    }
    function reload_playlist_music() {
        return list_fitler_music_playlist_name
    }
    function reset(i) {
        if(i  == 2){
            _index_ = 0
            list_fitler_Table_name = []
        }
        else if(i == 1) {
            _index_ = 0
             list_fitler_music_playlist_name = []
        }
    }
SwipeView{
    id: swipeView
   anchors.fill: parent
   width: 660
   height:  400
    Item {
        id : item
        width: 660
        height:  400
        Rectangle{
            id : rec_main
            width: 660
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
                    placeholderText: "Search here...."
                    onTextChanged: {
                        w.text_Search_change(text , 2)
                        m_List_model.reload() ;
                    }

                }
            Rectangle{
                width: 100
                height: 25
                color:  Qt.rgba(255, 206, 255, 0.0)


            }
            Rectangle{
              id : _add_Button
              width: 160
              height: 25
              color:  Qt.rgba(255, 206, 255, 0.3)
              radius: 16
              Row{
                  Rectangle{
                      id :rec12
                      width: 40
                      height: 25
                      radius: 5
                      color: Qt.rgba(255, 206, 255, 0.2)
                      Image {
                          id: file_folder123
                          source: "qrc:/Image/Add(1).png"
                          width: 20
                          height: 20
                          anchors.fill: rec12
                          fillMode:  Image.PreserveAspectFit
                      }
                  }
                  Column{
                      Text{
                          text: 'Create new playlist'
                          font.pointSize: 10
                      }
                  }
              }
              MouseArea{
                  id : mouse_area123
                  anchors.fill: parent
                  hoverEnabled  :  true
                  acceptedButtons: Qt.LeftButton | Qt.RightButton
                  cursorShape: Qt.PointingHandCursor
                  onClicked: {

                      w.signal_add_new_playlist(true)
                      console.log(_index_)
                  }
                  onEntered:{
                      parent.color =  Qt.rgba(255, 206, 255, 0.2)}
                  onExited: {
                      parent.color =  Qt.rgba(255, 206, 255, 0.5)
                    }

              }


            }

            }//
            ListModel{
                id : m_List_model
                function reload() {
                    m_List_model.clear() ;
                    _index_ = 0
                    for(var i = 0; i < list_fitler_Table_name.length ; i++) {
                        m_List_model.append({"name" :list_fitler_Table_name[i][0] })
                        _index_ ++ ;
                    }
                    reset(2)
                }
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
                                    text: ' '  + name
                                }
                            }
                        }
                        MouseArea {
                            id : mouse_area
                            anchors.fill: parent
                            hoverEnabled  :  true
                            acceptedButtons: Qt.LeftButton | Qt.RightButton
                             cursorShape: Qt.PointingHandCursor

                            onClicked: {
                                if(mouse.button == Qt.RightButton ) {
                                    contextMenu.x = mouse_area.x+25
                                    contextMenu.y =  mouse_area.y+25
                                    contextMenu.open()

                                }
                                else {
                                    _index_ = 0
                                    w._Get_element_in_file(name)
                                    enabled : swipeView.count-1
                                     swipeView.incrementCurrentIndex() ;
                                }

                            }                          
                            onEntered:{
                                parent.color =  Qt.rgba(255, 206, 255, 0.2)}
                            onExited: {
                                parent.color =  Qt.rgba(255, 206, 255, 0.5)
                              }
                        }
                        Menu{
                            id: contextMenu
                            width: 100
                            height: 75
                             MenuItem {
                                 text: "Rename"
                                 onClicked: {
                                  w.rename_table(name)
                                 }
                             }
                             MenuItem {
                                 text: "Delete"
                                 onClicked: {
                                     w.delete_table(name)
                                 }
                             }

                        }

                    }
                }

                }

            }
        ListModel{
            id : m_List_model1
            }
    }
    Item {
        id: item2
        Rectangle {
            id : main
            width: 660
            height:  400
            color:  Qt.rgba(255, 206, 255, 0.1)


            Row{
                id : text_field_1
                width : 350
                height: 30
                focus:  true
                Keys.onPressed: {
                  if(event.key+1 ==  Qt.Key_Enter) {
                      console.log(searchField.text)
                  }
                }
                    Rectangle{
                    id : bt1
                    width: 50
                    height: 25
                    color:   Qt.rgba(255, 206, 255, 0.5)
                    radius: 5
                    Text {
                        id: tex1
                        text: qsTr("<-Back")
                        anchors.horizontalCenter: bt1.horizontalCenter
                        anchors.verticalCenter: bt1.verticalCenter
                    }
                    MouseArea {
                        id : mouse_area_1
                        anchors.fill: parent
                        hoverEnabled  :  true
                        acceptedButtons: Qt.LeftButton
                         cursorShape: Qt.PointingHandCursor

                        onClicked: {
                           enabled : swipeView.count+1
                            swipeView.decrementCurrentIndex() ;
                            w.reset_datbase("")
                        }
                        onEntered:{
                            parent.color =  Qt.rgba(255, 206, 255, 0.2)}
                        onExited: {
                            parent.color =  Qt.rgba(255, 206, 255, 0.5)
                          }
                    }
                    }
           Button{
               id : _Button_1
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
                   id: image_Search_1
                   source: "qrc:///Image/Search.png"
                   width:  40
                   height:  25
                   anchors.fill: parent.Center
               }
           }
            TextField{
                    id: searchField_1
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
                    placeholderText: "Search here...."
                    onTextChanged: {
                        w.text_Search_change(text,1) ;
                        w.combobox_Text(comboBox.name_box)
                        listModel.reload() ;
                    }
                }
            ComboBox{
                 id : comboBox
                 width: 80
                 height: 25
                 property variant name_box :  "Song"
                 background:Rectangle {
                     color:  Qt.rgba(255, 206, 255, 0.1)
                     radius: 2
                     implicitWidth: 100
                     implicitHeight: 24
                     border.color: "#333"
                     border.width: 1
                 }
                model: ListModel{
                    id : mode_combobox
                    ListElement{Text :"Song"}
                    ListElement{Text :"Artist"}
                    }
                onActivated:  {
                    name_box = comboBox.currentText
                    w.combobox_Text(name_box)
                    searchField.clear() ;
                }
                }

            }
            Component {
                id: listDelWegate
                Item {
                width: 250; height: 50

                    Rectangle{

                        id : rec
                        width:  620
                        height: 45
                        color: Qt.rgba(255, 206, 255, 0.2)
                        radius: 10


                    Row {
                        id :row1

                        Column{
                            Rectangle{
                                id : rec1
                                width: 40
                                height: 40
                                radius: 60
                                color : Qt.rgba(0, 53, 26, 0.0)

                            Image{
                                id: image1
                                source: "qrc:///Image/Disc.png"
                                width: 35
                                height: 35
                                anchors.centerIn: rec1
                                fillMode: Image.PreserveAspectFit
                            }
                            }
                        }
                         Column {

                             width: 200
                             Text { text:' '+name+'  ('+Quality +')' }
                             Text { text:' ' }
                             Text { text: ' '+Author }
                            }
                        }

                     MouseArea{

                         id : mouse_area_2
                         anchors.fill: parent
                         hoverEnabled  :  true
                         acceptedButtons: Qt.LeftButton | Qt.RightButton
                         cursorShape: Qt.PointingHandCursor
                         onClicked: {
                            if(mouse.button == Qt.RightButton ) {
                                contextMenu2.x = mouse.x+10
                                contextMenu2.y =  mouse.y+10
                                contextMenu2.open()
                            }
                            else {
                                console.log("Left")
                            }
                         }

                         onDoubleClicked: {
                              w.check_and_get_List(true)
                          }
                         onEntered:{
                             parent.color =  Qt.rgba(255, 206, 255, 0.5)}
                         onExited: {
                             parent.color =  Qt.rgba(255, 206, 255, 0.2)
                           }
                        }

                     Menu {
                         id : contextMenu2
                             width: 120
                             height: 40

                              MenuItem {
                                  text: "Delete"
                                  onClicked: {
                                      w.delete_music_playlist(name)
                                      listModel.remove(INDEX)
                                  }

                              }

                         }
                         }
                    }

               }///



            }
            ListView {
                  id: listView123
                  anchors.fill: parent
                  anchors.topMargin: 30
                  model: listModel
                  delegate: listDelWegate
                  focus: true
                  clip:  true                  
                  currentIndex: _index_                  

                  Layout.fillWidth: true
                               Layout.fillHeight: true
                               ScrollBar.vertical: ScrollBar {}
               Rectangle{
                                   id : add_button_playlist
                                   width: 32
                                   height: 32
                                   color:  Qt.rgba(255, 206, 255, 0.1)
                                   radius: 15
                                   x:  625
                                   y: 280
                                   Image {
                                       id: image_add
                                       source: "qrc:/Image/Add.png"
                                       width: 32
                                       height: 32
                                        anchors.fill: add_button_playlist
                                   }
                               MouseArea{
                                   id : mouse_area__32
                                   anchors.fill: parent
                                   hoverEnabled  :  true
                                   acceptedButtons:  Qt.LeftButton | Qt.RightButton
                                   cursorShape: Qt.PointingHandCursor
                                   onClicked: {
                                        w.add_Music_in_playlist()
                                   }

                                   onEntered:{
                                       parent.color =  Qt.rgba(255, 206, 255, 0.5)}
                                   onExited: {
                                       parent.color =  Qt.rgba(255, 206, 255, 0.2)
                                     }
                                  }
                               }

            }
            ListModel{
                id: listModel
                property int model_size : listModel.count               
                function reload() {
                    listModel.clear() ;
                    _index_ = 0
                    for(var i = 0; i < list_fitler_music_playlist_name.length ; i++) {
                        listModel.append({"name" : list_fitler_music_playlist_name[i][1], "Author":list_fitler_music_playlist_name[i][2] , "INDEX" : i ,
                                           "Full_Name" : list_fitler_music_playlist_name[i][0] , "Quality" : list_fitler_music_playlist_name[i][3]})
                        _index_ ++ ;
                    }
                    reset(1)
                }              

            }
         }


}
PageIndicator{
    id : pageIndicatorID
    property int channe_1: 0
    anchors.bottom: parent.bottom
    anchors.horizontalCenter:parent.horizontalCenter
    currentIndex: swipeView.currentIndex
    interactive: true
    count : swipeView.count
    onChanne_1Changed: {
        swipeView.view.incrementCurrentIndex()
        }
    }
}


