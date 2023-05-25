import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
Item {
    Rectangle{
        anchors.fill: parent
        color: "#2c313c"
        anchors.margins: 10
        GridLayout {

                anchors.fill: parent
                columns: 2
                rows: 2
                rowSpacing: 20
                columnSpacing: 20
                //spacing: 8

                // Section 1: CPU Information
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "#2c313c"
                    //border.color: "#CCCCCC"
                    //border.width: 1
                    radius: 4
                    Rectangle {
                        width: parent.width * 0.5
                        height: parent.height * 0.12
                        radius: height / 2
                        color: "#DE4C0B"
                        anchors {
                            top: parent.top
                            horizontalCenter: parent.horizontalCenter
                            topMargin: parent.height * 0.03
                        }
                        Text {
                            text: "CPU Information"
                            anchors.centerIn: parent
                            font {
                                            pixelSize: 25
                                            bold: true
                                        }
                            color: "white"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                    }
                    Rectangle {
                        width: parent.width * 0.9
                        height: parent.height * 0.8
                        radius: height / 3
                        color: "#DE4C0B"
                        anchors {
                            bottom: parent.bottom
                            horizontalCenter: parent.horizontalCenter
                            bottomMargin: parent.height * 0.03
                        }
                        Text {
                            text: sinfo.getCPUInformation()
                            anchors.centerIn: parent
                            font {
                                            pixelSize: 20
                                            bold: true
                                        }
                            color: "white"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                }

                // Section 2: RAM Information
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "#2c313c"
                    //border.color: "#CCCCCC"
                    //border.width: 1
                    radius: 4
                    Rectangle {
                        width: parent.width * 0.5
                        height: parent.height * 0.12
                        radius: height / 2
                        color: "#1DBD12"
                        anchors {
                            top: parent.top
                            horizontalCenter: parent.horizontalCenter
                            topMargin: parent.height * 0.03
                        }
                        Text {
                            text: "RAM Information"
                            anchors.centerIn: parent
                            font {
                                            pixelSize: 25
                                            bold: true
                                        }
                            color: "white"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                    }
                    Rectangle {
                        width: parent.width * 0.9
                        height: parent.height * 0.8
                        radius: height / 3
                        color: "#1DBD12"
                        anchors {
                            bottom: parent.bottom
                            horizontalCenter: parent.horizontalCenter
                            bottomMargin: parent.height * 0.03
                        }
                        Text {
                            text: sinfo.getRAMInformation()
                            anchors.centerIn: parent
                            font {
                                            pixelSize: 20
                                            bold: true
                                        }
                            color: "white"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                }

                // Section 3: Hard Disk Information
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "#2c313c"
                    //border.color: "#CCCCCC"
                    //border.width: 1
                    radius: 4
                    Rectangle {
                        width: parent.width * 0.5
                        height: parent.height * 0.12
                        radius: height / 2
                        color: "#1DBD12"
                        anchors {
                            top: parent.top
                            horizontalCenter: parent.horizontalCenter
                            topMargin: parent.height * 0.03
                        }
                        Text {
                            text: "Hard Disk Information"
                            anchors.centerIn: parent
                            font {
                                            pixelSize: 25
                                            bold: true
                                        }
                            color: "white"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                    }
                    Rectangle {
                        width: parent.width * 0.9
                        height: parent.height * 0.8
                        radius: height / 3
                        color: "#1DBD12"
                        anchors {
                            bottom: parent.bottom
                            horizontalCenter: parent.horizontalCenter
                            bottomMargin: parent.height * 0.03
                        }
                        Text {
                            text: sinfo.getHardDiskInformation()
                            anchors.centerIn: parent
                            font {
                                            pixelSize: 20
                                            bold: true
                                        }
                            color: "white"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                }

                // Section 4: GPU Information
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "#2c313c"
                    //border.color: "#CCCCCC"
                    //border.width: 1
                    radius: 4
                    Rectangle {
                        width: parent.width * 0.5
                        height: parent.height * 0.12
                        radius: height / 2
                        color: "#DE4C0B"
                        anchors {
                            top: parent.top
                            horizontalCenter: parent.horizontalCenter
                            topMargin: parent.height * 0.03
                        }
                        Text {
                            text: "GPU Information"
                            anchors.centerIn: parent
                            font {
                                            pixelSize: 25
                                            bold: true
                                        }
                            color: "white"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                    }
                    Rectangle {
                        width: parent.width * 0.9
                        height: parent.height * 0.8
                        radius: height / 3
                        color: "#DE4C0B"
                        anchors {
                            bottom: parent.bottom
                            horizontalCenter: parent.horizontalCenter
                            bottomMargin: parent.height * 0.03
                        }
                        Text {
                            text: sinfo.getGPUInformation()
                            anchors.centerIn: parent
                            font {
                                            pixelSize: 20
                                            bold: true
                                        }
                            color: "white"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                }
            }
    }
    Connections {
        target: sinfo
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:800}
}
##^##*/
