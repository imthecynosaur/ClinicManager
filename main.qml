import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import com.databasehelper 1.0

Window {
    minimumHeight: 480
    maximumHeight: 480
    minimumWidth: 640
    maximumWidth: 640
    visible: true

    Column {
        id: leftColumn
        x: 0
        y: 0
        width: 149
        height: 480

        Rectangle {
            id: rectangle
            color: "#e0e0e0"
            border.color: "#a3a3a3"
            border.width: 0
            anchors.fill: parent

            Column {
                id: infoColumn
                x: 22
                y: 45
                width: 102
                height: 171
                spacing: 10

                Label {
                    id: label1
                    text: qsTr("ID")
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 147
                }


                Rectangle {
                    id: rectangle1
                    width: 100
                    height: 24
                    color: "#ffffff"
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 121

                    TextInput {
                        id: userID
                        text: qsTr("")
                        anchors.fill: parent
                        font.pixelSize: 12
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        clip: true
                    }
                }

                Label {
                    id: label2
                    text: qsTr("First Name")
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 88
                }

                Rectangle {
                    id: rectangle2
                    width: 100
                    height: 24
                    color: "#ffffff"
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 61

                    TextInput {
                        id: firstName
                        text: qsTr("")
                        anchors.fill: parent
                        font.pixelSize: 12
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        clip: true
                    }

                }

                Label {
                    id: label3
                    text: qsTr("Last Name")
                    anchors.bottom: parent.bottom
                    horizontalAlignment: Text.AlignLeft
                    anchors.bottomMargin: 28
                }

                Rectangle {
                    id: rectangle3
                    width: 100
                    height: 24
                    color: "#ffffff"
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 1

                    TextInput {
                        id: lastName
                        x: 0
                        y: 0
                        text: qsTr("")
                        anchors.fill: parent
                        font.pixelSize: 12
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        clip: true
                    }
                }



            }
        }
    }

    Column {
        id: column
        x: 20
        y: 368
        width: 109
        height: 64
        spacing: 5

        Button {
            id: create
            width: 110
            height: 30
            text: qsTr("Create user")
            icon.color: "#000000"
            font.pointSize: 11
            flat: false
            onClicked: {
                helper.insertIntoTable(userID.text, firstName.text, lastName.text, image.source)
                userID.text = ""
                firstName.text = ""
                lastName.text = ""
                image.source = "file:///D:/C++/Qt projects/cmakeTest/clinicTest/resources/user.svg"
            }
        }

        Button {
            id: find
            width: 110
            height: 30
            text: qsTr("Find user")
            font.pointSize: 11
            highlighted: false
            onClicked: {
                image.source = "file:///" + helper.creatImageFromData(userID.text)
                firstName.text = helper.getFirstName(userID.text)
                lastName.text = helper.getLastName(userID.text)
            }
        }
    }

    FileDialog {
        id: fileDialog
        currentFolder: StandardPaths.standardLocations(StandardPaths.PicturesLocation)[0]
        onAccepted:{
                        image.source = selectedFile
        }
    }

    Rectangle {
        id: imageContainer
        x: 149
        y: 0
        width: 491
        height: 345
        color: "#ffffff"
        border.color: "#ffffff"

        Image {
            id: image
            anchors.fill: parent
            source: "file:///D:/C++/Qt projects/cmakeTest/clinicTest/resources/user.svg"
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            anchors.leftMargin: 0
            anchors.topMargin: 0
            transformOrigin: Item.Center
            fillMode: Image.PreserveAspectFit
            sourceSize.width: parent.width
            sourceSize.height: parent.height
        }
    }

    Row {
        id: row
        x: 310
        y: 408
        width: 169
        height: 24
        spacing: 22

        Rectangle {
            id: rectangle4
            width: 74
            height: 26
            color: "#ffffff"
            border.width: 1

            Button {
                id: browse
                text: qsTr("Browse")
                anchors.fill: parent
                flat: true
                onClicked: fileDialog.open()
            }
        }

        Rectangle {
            id: rectangle5
            width: 74
            height: 26
            color: "#ffffff"
            border.width: 1
            Button {
                id: close
                text: qsTr("close")
                anchors.fill: parent
                flat: true
                onClicked:
                {
                    userID.text = ""
                    firstName.text = ""
                    lastName.text = ""
                    image.source = "file:///D:/C++/Qt projects/cmakeTest/clinicTest/resources/user.svg"
                }

            }
        }
    }

    DBHelper{
        id: helper
    }



}


