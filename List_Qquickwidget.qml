import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQml.Models 2.2
Rectangle {
    id : main
    width: 250
    height: 300
    color:  Qt.rgba(255, 206, 255, 0.1)
    property  variant  list_path_name :[]
    property variant  name_of_music
    property int _index_
    property  int _size
    property int key_next
    property bool signal_Play_Pause :false
    property int  to_val: 360
    property int  from_val: 0
    property  variant  signalss
    property  variant  list_fitler_name_temp :[]
     property  variant  list_fitler_name :[]
    property  variant  model_list_name :[]
    property variant present_name_music
    property int indexx :-1


    function get_sgnal_play_or_pause(signals){
       signal_Play_Pause =  signals
    }
    function get_SIGNAL(){
        return signal_Play_Pause
    }
    function find(model, criteria) {
      for(var i = 0; i < model.count; ++i) if (criteria(model.get(i))) return model.get(i)
      return null
    }   
    function get_name_of_music(music) {
        name_of_music =  music
        present_name_music =  music
        find(listModel , function(item){
            if( item.Full_Name == name_of_music){
               key_next = item.INDEX
            }})
    }
    function clear_list_music(chck){
        _index_ = 0
        listModel.clear()
    }

    function find_name(name1) {
        find(listModel , function(item){
          if(item.name == name1)  {
          }
        })
    }
    function get_result(full_name , name , Author , qualification){
         var result = [full_name , name , Author , qualification]
        list_fitler_name.push(result)
    }
    function get_size(size){
        _size   = size
        console.log(size)
    }
    function load() {
        return  list_fitler_name
    }
    function reset(){
        list_fitler_name = []
    }
    function model_Load() {
        _index_ = 0 ;
        for(var i = 0; i < model_list_name.length ; i++) {
            listModel.append({"name" : model_list_name[i][1], "Author":model_list_name[i][2] , "INDEX" : _index_ ,
                               "Full_Name" : model_list_name[i][0] , "Quality" : model_list_name[i][3]})
            _index_ ++

        }
        _size = model_list_name.length ;
        }

    function set_list_path_name(full_name , name , Author , qualification){
         listModel.append({"name" : name, "Author":Author , "INDEX" : _index_ ,
                              "Full_Name" : full_name , "Quality" : qualification})       
        _index_ +=1
        var result = [full_name , name , Author , qualification]
        model_list_name.push(result) ;

    }
    function restart_Fitler_list(arf1) {
        _index_  = 0 ;
       listModel.clear();
    }

    function filter_List(full_name , name , Author , qualification, size,sig) {
       listModel.append({"name" : name, "Author":Author , "INDEX" : _index_ ,
                          "Full_Name" : full_name , "Quality" : qualification})
        _index_ +=1
        //console.log(list_fitler_name_temp.length)
    }
    Row{
        id : text_field
        width : 350
        height: 30
        focus:  true
        Keys.onPressed: {
          if(event.key+1 ==  Qt.Key_Enter) {
              console.log(searchField.text)
          }
        }
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
                w.text_Search_change(text,0) ;
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
    Rectangle{
        width:  90
        height: 30
        color: Qt.rgba(255, 206, 255, 0.0)
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
                 height: 120
                 spacing: 0

                  MenuItem {
                      width: 120
                      height: 30
                      text: "Add into list"
                      onClicked: {
                          w.add_list() ;
                      }

                  }
                  MenuItem {
                      width: 120
                      height: 30
                      text: "Add into playlist"
                      onClicked: {
                          w.save_music_in_playlist() ;
                      }

                  }
                  MenuItem {
                      width: 120
                      height: 30
                      text: "Save all"
                      onClicked: {
                          w.save_list() ;
                      }

                  }
                  MenuItem {
                      width: 120
                      height: 30
                      text: "Delete All"
                      onClicked: {
                          listModel.clear() ;
                          w.delete_all() ;
                      }
                  }

             }

    }

    }

    Component {
        id: listDelWegate
        Item {
        property variant check1 : _size
        width: 250; height: 50
        onCheck1Changed: {
            listModel.find_item(present_name_music)
        }
            Rectangle{
                property  int check : key_next
                property int  count
                id : rec
                width:  550
                height: 45
                color: Qt.rgba(255, 206, 255, 0.1)
                radius: 10
                function find_by_name(check) {
                    find(listModel , function(item){
                        if( item.INDEX == check){
                           key_next = item.INDEX
                            rec.color =   Qt.rgba(255, 206, 255, 0.9)
                        }})
                }

            Row {
                id :row
                Rectangle{
                    property  int check : key_next
                    property bool signal: false
                    property variant check1 : _size
                    id : rec1
                    width: 40
                    height: 40
                    radius: 60
                    color : Qt.rgba(0, 53, 26, 0.1)
                    onCheckChanged: {
                        if(check == -1) {
                        }
                        else {
                          if(check == INDEX)   {
                              // This is available in all editors.
                               rec.color =  "lightgreen"
                               rec1.color =  'white'
                              image1.source = "qrc:///Image/listen.png"
                              image1._signal_play =  true


                          }
                          else {
                              rec.color =   Qt.rgba(255, 206, 255, 0.1)
                               rec1.color =  Qt.rgba(0, 53, 26, 0.1)
                              image1.source = "qrc:///Image/Disc.png"
                              image1._signal_play =  false
                        }
                        }
                    }

                Image {
                     property  int check : key_next
                     property  bool _signal_play :     signal_Play_Pause
                    property bool _signal_stop : false
                    id: image1
                    source: "qrc:///Image/Disc.png"
                    width: 35
                    height: 35
                    anchors.centerIn: rec1
                    fillMode: Image.PreserveAspectFit
                    smooth: true                    
                    RotationAnimation on rotation {
                        id : rota
                        from: 0
                        to : 360
                        duration: 10000
                        loops:  Animation.Infinite
                        running: image1._signal_play

                        alwaysRunToEnd: false
                    }

                   onCheckChanged: {
                        to_val = 360
                      if(check != -1){

                      if(check == INDEX ){
                           if(signal_Play_Pause == false) {
                                image1.source = "qrc:///Image/listen.png"
                               image1._signal_play =  true
                           }
                           else {
                                image1._signal_play = false
                           }
                       }
                       else  {
                         image1._signal_play =  false
                          listView123.currentIndex = check
                           image1.source = "qrc:///Image/Disc.png"

                       }

                   }
                   }
                }
                }
             Column {
                 width: 200
                 Text { text:' '+name+'  ('+Quality +')' }
                 Text { text:' ' }
                 Text { text: ' '+Author }                                 
                }
             Column{}
            }
            MouseArea{
                id : mouse_area

                anchors.fill: parent
                hoverEnabled  :  true
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                cursorShape: Qt.PointingHandCursor
                property int check_mouse: key_next

                onDoubleClicked: {
                    w.connect_qml(Full_Name)
                    image1.source = "qrc:///Image/listen.png"
                    image1._signal_play =  true
                    rec1.color =  'white'
                }
                onCheck_mouseChanged: {
                    if(check_mouse == -1) {
                    }
                    else {
                      if(check_mouse == INDEX)   {
                      }
                      else {
                      }
                    }
                }


                onClicked   : {

                    if(mouse.button == Qt.RightButton ) {
                    }
                    else {
                    }
                }
                onEntered:{parent.color =  Qt.rgba(255, 206, 255, 0.4)
                    contextMenu.close()

                }
                onExited: {
                    contextMenu.close()
                    if(key_next == INDEX) {
                        parent.color =  "lightgreen"
                    }
                    else {

                      parent.color =  Qt.rgba(255, 206, 255, 0.1)
                    }
                    }
            }
            Menu {
                id : contextMenu
                    width: 120
                    height: 70
                    spacing: 0
                     MenuItem {
                         text: "Delete"
                         onClicked: {
                             w.delete_in_main_list(name)
                             listModel.remove(INDEX)
                         }
                     }
                     MenuItem {
                         text: "Add into playlist"
                         onClicked: {
                             w.add_Music_into_playlist(name)
                         }

                     }
                }

            Rectangle{
                id : button_rep
                x : 515
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

        }//

       }
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
          onCountChanged: {
              if(_index_ != 0){
              }
          }         
          onContentYChanged: {
              if(contentY < -100) {
                  searchField.visible =  true
                   timer.running = true;
              }
          }

          Layout.fillWidth: true
                       Layout.fillHeight: true
                       ScrollBar.vertical: ScrollBar {}

    }
    Timer{
           id: timer; running: false; interval: 7000; repeat: false
       }
    DelegateModel{
        id : delegate
    }

    ListModel{
        id: listModel
        property int model_size : listModel.count        
        function reload() {
            listModel.clear() ;
            _index_ = 0
            for(var i = 0; i < list_fitler_name.length ; i++) {
                listModel.append({"name" : list_fitler_name[i][1], "Author":list_fitler_name[i][2] , "INDEX" : i
                                     ,
                                   "Full_Name" : list_fitler_name[i][0] , "Quality" : list_fitler_name[i][3]})
                _index_ ++ ;
            }
            reset()                 
        }
        function find_item(name_music){
            name_of_music = name_music
            find(listModel , function(item){
                if( item.Full_Name == name_of_music){
                   key_next = item.INDEX
                }
                else {
                    key_next = -1
                }

            })
        }

    }

}
