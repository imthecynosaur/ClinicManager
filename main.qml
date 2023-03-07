import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
//import com.databasehandler 1.0
import com.databasehelper 1.0

ApplicationWindow {
    width: 640
    height: 480
    visible: true

    header: ToolBar {
        Button {
            id: uploader
            text: qsTr("Choose Image...")
            onClicked: fileDialog.open()
        }

        Button {
            id: downloader
            text: qsTr("Choose Image from saved...")
//            onClicked: image.source = handler1.getImageUrl()
            x: 150
        }

        Button {
            id: close
            text: qsTr("close")
            onClicked: image.source = ""
            x: 500
        }

    }

    Image {
        id: image
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
    }

    FileDialog {
        id: fileDialog
        currentFolder: StandardPaths.standardLocations(StandardPaths.PicturesLocation)[0]
        onAccepted:{
//            image.source = selectedFile
//            handler1.setImageUrl(selectedFile)
//            console.log(selectedFile)
            helper1.setImageUrl(selectedFile)
        }
    }

//    DBHandler{
//        id: handler1
//    }


    DBHelper{
        id: helper1
    }
}
