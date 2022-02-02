import QtQuick 2.0

Item {
    id : item
    property variant list_file_name: []
    function get_List_of_File_Name(file_name){
        list_file_name.push(file_name) ;
    }
    Rectangle{
        id : rec_main
        width: 700
        height:  100
        color: Qt.rgba(255, 206, 255, 0.2)
        radius: 4
        ListModel{
            id : lST_Model
        }
        GridView{
            id : grid_Model

        }
    }

}

