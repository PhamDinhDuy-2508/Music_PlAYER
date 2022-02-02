import QtQuick 2.6
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
Item {
    id : main
    property int _index_: 0
    property  variant list_Artist_music_playlist_name : []
    function filter_Playlist_music(full_name , name , Author , qualification) {
        var result = [full_name , name , Author , qualification]
        list_Artist_music_playlist_name.push(result)
        _index_ ++
    }
    function reloaod_playlist_table() {
        return list_fitler_Table_name
    }
    function add_music_artist(full_name , name , Author , qualification,path) {
        listModel_3.append({"name" : name, "Author":Author , "INDEX" : _index_+1,
                                    "Full_Name" : full_name , "Quality" : qualification,"path" : path ,"value": false})
        _index_ ++ ;
    }
    function clear_Artist_music() {
        listModel_3.clear() ;
    }

    function clear(s_ignal){
        listModel.clear()
        _index_ = 0 ;
    }
    function clear_artist(){
          listModel_2.clear() ;
    }

    function  add_Artist (name_of_artist){
        listModel_2.append({"name" :name_of_artist })
    }

    function set_list_path_name(full_name , name , Author , qualification,path){
        console.log(_index_)

        listModel.append({"name" : name, "Author":Author , "INDEX" : _index_+1,
                            "Full_Name" : full_name , "Quality" : qualification,"path" : path ,"value": false})
        _index_++
    }


   Rectangle{
       id : tabview
       width: 661
       height: 371
       color:   Qt.rgba(255, 206, 255, 0.1)
       TabBar{
           id :bar
           x : 0
           y : 370
           height: 20
           background: Rectangle {
               color:  Qt.rgba(255, 206, 255, 0.1)
               radius: 2
               border.width: 1
           }

           TabButton{
               id : music
               width:  330
               height: 20
               text:  " Music "
               onClicked: {
                   listModel_2.clear()
               }
           }
           TabButton {
               id  : tab
               width: 330
               height: 20
               text : " Artist "
               onClicked: {
                   w.signal_Artist_page() ;
               }
           }
       }
       StackLayout{
           anchors.fill:  parent
           currentIndex: bar.currentIndex
           Item {
               id : music_tab
               Rectangle{
                   id : music_rec
                   width:  661
                   height:  370
                   color: Qt.rgba(255, 206, 255, 0.0)
                   Row{
                       id : text_field_1
                       width : 350
                       height: 30
                       focus:  true
                       Keys.onPressed: {
                         if(event.key+1 ==  Qt.Key_Enter) {
                         }
                       }                 


                   Rectangle{
                       width:  630
                       height: 30
                       color : Qt.rgba(255, 206, 255, 0.0)
                   }

                   Rectangle{
                       id : button_rep_main
                       width:  30
                       height: 30
                       color: "lightgreen"
                       radius: 20
                       Image {
                           id: delete_music
                           anchors.fill:  parent
                           source: "qrc:/Image/Option.png"
                           width: 25
                           height: 25
                       }
                        MouseArea{
                            anchors.fill: parent
                            hoverEnabled  :  true
                            acceptedButtons: Qt.LeftButton
                            cursorShape: Qt.PointingHandCursor
                            onEntered:{parent.color =  Qt.rgba(255, 206, 255, 0.4)
                                contextMenu2.close()
                            }
                            onClicked: {
                                contextMenu2.x =  button_rep_main.x+40
                                contextMenu2.y =  button_rep_main.y+20

                                contextMenu2.open()

                            }

                            onExited: {
                                parent.color = "lightgreen"
                                }
                        }
                        Menu {
                            id : contextMenu2
                                width: 120
                                height: 85
                                spacing: 5
                                 MenuItem {
                                     width: 120
                                     height: 30
                                     text: "Play all "
                                     onClicked: {
                                         w.play_all()
                                     }

                                 }
                                 MenuItem {
                                     width: 120
                                     height: 30
                                     text: "Add music"
                                     onClicked: {
                                         w.load_into_libary()
                                     }

                                 }
                                 MenuItem {
                                     width: 120
                                     height: 30
                                     text: "Delete all"
                                     onClicked: {
                                         w.delete_all_music_in_libary("asd")
                                         listModel.clear()
                                         listModel_3.clear()
                                     }

                                 }

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
                               Rectangle {
                                   property bool checked: false
                                   id: check
                                   x : 550
                                   y : 20
                                   width: 20
                                   height: 20
                                   radius: 5
                                   visible: true
                                   onCheckedChanged: {
                                       if(checked == true) {
                                           image_check.sig = true
                                           listModel.add_choice(INDEX)
                                       }
                                       else {
                                           image_check.sig = false
                                           listModel.remove_choice(INDEX)
                                       }
                                   }
                                   Image {
                                       property  bool  sig: false
                                       anchors.fill: parent
                                       width: 40
                                       height: 40
                                       id:  image_check
                                       source: "qrc:/Image/check.jpg"
                                       visible:  sig
                                   }

                                 }


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

                                   }
                                   else {
                                     if (check.checked == true) {
                                         value =  false
                                         listModel.remove_choice(INDEX)

                                         check.checked = value
                                     }
                                     else {
                                         value =  true

                                         check.checked = value
                                     }
                                   }
                                   parent.color = "Lightgreen"

                                }

                                onDoubleClicked: {

                                 }
                                onEntered:{
                                    parent.color =  Qt.rgba(255, 206, 255, 0.5)}
                                onExited: {

                                        if(check.checked == true) {
                                            parent.color = "Lightgreen"

                                        }
                                        else {
                                        parent.color =  Qt.rgba(255, 206, 255, 0.2)
                                        }

                                  }
                               }
                            Rectangle{
                                id : button_rep
                                x : 580
                                y : 15
                                width:  30
                                height: 30
                                color: Qt.rgba(255, 206, 255, 0.1)
                                radius: 20
                                Image {
                                    id: delete_music
                                    anchors.fill:  parent
                                    source: "qrc:/Image/Option.png"
                                    width: 25
                                    height: 25
                                }
                                 MouseArea{
                                     anchors.fill: parent
                                     hoverEnabled  :  true
                                     acceptedButtons: Qt.LeftButton
                                     cursorShape: Qt.PointingHandCursor
                                     onEntered:{parent.color =  Qt.rgba(255, 206, 255, 0.4)
                                         contextMenu.close()
                                     }
                                     onClicked: {
                                         contextMenu.x =  button_rep.x+40
                                         contextMenu.y =  button_rep.y+20

                                         contextMenu.open()

                                     }

                                     onExited: {
                                         parent.color =  Qt.rgba(255, 206, 255, 0.1)
                                         }
                                 }
                            }



                            Menu {
                                id : contextMenu
                                    width: 120
                                    height: 70

                                     MenuItem {
                                         id : item1
                                         width: 120
                                         height:  20
                                         Text {
                                             id: text_del
                                             text: qsTr(" +Delete")
                                             font.family: "Helvetica"
                                             font.pointSize: 10
                                             anchors.fill:  item1.Center
                                         }

                                         onClicked: {
                                             w.delete_music_in_libary(name);
                                             listModel.remove(INDEX-1)  ;
                                         }

                                     }
                                     MenuItem {
                                         width: 120
                                         height:  20


                                         Text {
                                             id: text_add_quueu
                                             text: qsTr(" +Add into queue")
                                             font.family: "Helvetica"
                                             font.pointSize: 10

                                         }
                                         onClicked: {

                                         }
                                     }

                                     MenuItem{
                                         width: 120
                                         height:  20
                                         Text {
                                             id: text_add_play
                                             text: qsTr(" +Play")
                                             font.family: "Helvetica"
                                             font.pointSize: 10
                                         }
                                         onClicked: {
                                             //"name" : name, "Author":Author , "INDEX" : _index_+1,
                                            // "Full_Name" : full_name , "Quality" : qualification,"Path" : path ,"value": false
                                             w.play_music(Full_Name ,name , Author , Quality ,path )

                                         }
                                     }

                                }
                                }
                           }

                      }



                   }
                   ListView {
                         id: listView123
                         anchors.fill: parent
                         anchors.topMargin: 10
                         model: listModel
                         delegate: listDelWegate

                         focus: true
                         clip:  true

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
                       property var  arr :[]
                       function reload() {
                           listModel.clear() ;
                           _index_ = 0
                           for(var i = 0; i < list_Artist_music_playlist_name.length ; i++) {
                               listModel.append({"name" : list_Artist_music_playlist_name[i][1], "Author":list_Artist_music_playlist_name[i][2] , "INDEX" : i ,
                                                  "Full_Name" : list_Artist_music_playlist_name[i][0] , "Quality" : list_Artist_music_playlist_name[i][3]})
                               _index_ ++ ;
                           }
                           reset(1)
                       }
                       function add_choice(i) {
                           arr.push(i)
                           listModel.get(i).value = true
                       }
                        function remove_choice(i) {
                            arr.pop(i)
                            listModel.get(i).value = false
                        }                        

                   }

                }

           Item {

               id : artist_tab
               SwipeView{
                   id : wip
                   width:  663
                   height: 370
                   Item {

                   id : swip1
                   width:  663
                   height: 370
               Rectangle{
                   id : main_2
                   width:  663
                   height: 370
                   color:   Qt.rgba(255, 206, 255, 0.0)

                   Row{
                       id : text_field_2
                       width : 350
                       height: 30
                       focus:  true
                       Keys.onPressed: {
                         if(event.key+1 ==  Qt.Key_Enter) {
                             console.log(searchField.text)
                         }
                       }

                   }
                   Component {
                       id: listDelWegate_2
                       Item {
                       width: 250; height: 50
                           Rectangle{
                               id : rec
                               width:  600
                               height: 45
                               color: Qt.rgba(255, 100, 235, 0.2)
                               radius: 10

                           Row {

                               Column{
                                   Rectangle{
                                       id : rec1
                                       width: 40
                                       height: 40
                                       radius: 60
                                       color :"white"

                                   Image{
                                       id: image1
                                       source: "qrc:///Image/USer.png"
                                       width: 32
                                       height: 32
                                       anchors.centerIn: rec1
                                       fillMode: Image.PreserveAspectFit
                                   }
                                   }
                               }
                                Column {
                                    Text {
                                        id: id_text
                                        text: qsTr(name)
                                    }
                               }
                           }

                            MouseArea{

                                id : mouse_area_2
                                anchors.fill: parent
                                hoverEnabled  :  true
                                acceptedButtons: Qt.LeftButton | Qt.RightButton
                                cursorShape: Qt.PointingHandCursor
                                onDoubleClicked: {
                                    console.log(name)
                                }
                                onClicked: {
                                    w.signal_Artist(name)
                                    wip.incrementCurrentIndex()
                                }

                                onEntered:{
                                    parent.color =  Qt.rgba(255, 206, 255, 0.5)}
                                onExited: {
                                    parent.color =  Qt.rgba(255, 206, 255, 0.2)
                                  }
                               }

                                }
                           }

                      }///

                 }
               ListView{
                   id:listView123_2
                   anchors.fill:  parent
                   model:  listModel_2
                   anchors.topMargin: 10
                   delegate: listDelWegate_2
                   focus: true
                   clip:  true

                   Layout.fillWidth: true
                                Layout.fillHeight: true
                                ScrollBar.vertical: ScrollBar {
                                    ColorAnimation {
                                        from: "black"
                                        to: "black"
                                        duration: 1000
                                    }
                                }
               }
               ListModel{
                   id: listModel_2
               }
     }
                   Item {

                   id : item
                   width:  620
                   height: 370
               Rectangle{
                   id : main_3
                   width:  620
                   height: 370
                   color:   Qt.rgba(255, 206, 255, 0.0)

                   Row{
                       id : text_field_3
                       width : 350
                       height: 30
                       focus:  true
                       Keys.onPressed: {
                         if(event.key+1 ==  Qt.Key_Enter) {
                             console.log(searchField.text)
                         }
                       }
                       Rectangle{
                           width: 570
                           height: 25
                           color:   Qt.rgba(255, 206, 255, 0.0)
                       }

                       Rectangle{
                       id : bt1
                       width: 70
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
                              enabled : wip.count+1
                              w.back_signal()
                               wip.decrementCurrentIndex() ;
                           }
                           onEntered:{
                               parent.color =  Qt.rgba(255, 206, 255, 0.2)}
                           onExited: {
                               parent.color =  Qt.rgba(255, 206, 255, 0.5)
                             }
                       }
                       }

                   Rectangle{
                       width: 180
                       height: 40
                       color: Qt.rgba(0,0,0,0)
                   }

                   }
                   Component {
                       id: listDelWegate_3
                       Item {
                       width: 250; height: 50
                           Rectangle{
                               id : rec
                               width:  500
                               height: 45
                               color: Qt.rgba(255, 100, 235, 0.2)
                               radius: 10

                           Row {

                               Column{
                                   Rectangle{
                                       id : rec1
                                       width: 40
                                       height: 40
                                       radius: 60
                                       color :Qt.rgba(255, 100, 235, 0.2)

                                   Image{
                                       id: image1
                                       source: "qrc:/Image/Disc.png"
                                       width: 38
                                       height: 38
                                       anchors.centerIn: rec1
                                       fillMode: Image.PreserveAspectFit
                                   }
                                   }
                               }
                                Column {

                                        id: id_text
                                        width: 200
                                        Text { text:' '+name+'  ('+Quality +')' }
                                        Text { text:' ' }
                                        Text { text: ' '+Author }

                               }
                           }

                            MouseArea{

                                id : mouse_area_3
                                anchors.fill: parent
                                hoverEnabled  :  true
                                acceptedButtons: Qt.LeftButton | Qt.RightButton
                                cursorShape: Qt.PointingHandCursor
                                onDoubleClicked: {
                                    console.log(name)
                                }
                                onClicked: {
                                    wip.incrementCurrentIndex()
                                   w.signal_Artist(name)
                                }

                                onEntered:{
                                    parent.color =  Qt.rgba(255, 206, 255, 0.5)}
                                onExited: {
                                    parent.color =  Qt.rgba(255, 206, 255, 0.2)
                                  }
                               }
                            Rectangle{
                                id : button_rep
                                x : 460
                                y : 10
                                width:  30
                                height: 30
                                color: Qt.rgba(255, 206, 255, 0.1)
                                radius: 20
                                Image {
                                    id: delete_music_23
                                    anchors.fill:  parent
                                    source: "qrc:/Image/Option.png"
                                    width: 25
                                    height: 25
                                }
                                 MouseArea{
                                     anchors.fill: parent
                                     hoverEnabled  :  true
                                     acceptedButtons: Qt.LeftButton
                                     cursorShape: Qt.PointingHandCursor
                                     onEntered:{parent.color =  Qt.rgba(255, 206, 255, 0.4)
                                         menuconstext2_3.close() ;
                                     }
                                     onClicked: {
                                         menuconstext2_3.x =  button_rep.x+40
                                         menuconstext2_3.y =  button_rep.y+20
                                         menuconstext2_3.open()
                                     }

                                     onExited: {
                                         parent.color =  Qt.rgba(255, 206, 255, 0.1)
                                         }
                                 }
                            }
                           Menu{
                               id : menuconstext2_3
                               width: 80
                               height: 30
                               MenuItem {
                                   width: 80
                                   height:  30

                                   Text {
                                       id: text_add
                                       text: qsTr(" Play")
                                       font.family: "Helvetica"
                                       font.pointSize: 10

                                   }
                                   onClicked: {
                                       w.play_music(Full_Name ,name , Author , Quality ,path )
                                   }
                               }

                           }

                                }
                           }



                      }

                   ///

                 }
               ListView{
                   id:listView123_3
                   anchors.fill:  parent
                   model:  listModel_3
                   anchors.topMargin: 10
                   delegate: listDelWegate_3
                   focus: true
                   clip:  true

                   Layout.fillWidth: true
                                Layout.fillHeight: true
                                ScrollBar.vertical: ScrollBar {
                                    ColorAnimation {
                                        from: "black"
                                        to: "black"
                                        duration: 1000
                                    }
                                }

               }
               ListModel{
                   id: listModel_3
               }
            }
       }

         }

      }
    }
 }










