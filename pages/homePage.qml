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
                    color: "#FFFFFF"
                    border.color: "#CCCCCC"
                    border.width: 1
                    radius: 4
                    Text {
                                    anchors {
                                        top: parent.top
                                        horizontalCenter: parent.horizontalCenter
                                        topMargin: 10
                                    }
                                    font {
                                        pixelSize: 24
                                        bold: true
                                    }
                                    text: "CPU Information"
                                }

                                Text {
                                    anchors.centerIn: parent
                                    font.pixelSize: 20
                                    text: sinfo.getCPUInformation()
                                }
                }

                // Section 2: RAM Information
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "#FFFFFF"
                    border.color: "#CCCCCC"
                    border.width: 1
                    radius: 4
                    Text {
                            anchors {
                                top: parent.top
                                horizontalCenter: parent.horizontalCenter
                                topMargin: 10
                            }
                            font {
                                pixelSize: 24
                                bold: true
                            }
                            text: "RAM Information"
                        }
                    Text {
                        anchors.centerIn: parent
                        font.pixelSize: 20
                        text: sinfo.getRAMInformation()
                    }
                }

                // Section 3: Hard Disk Information
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "#FFFFFF"
                    border.color: "#CCCCCC"
                    border.width: 1
                    radius: 4
                    Text {
                            anchors {
                                top: parent.top
                                horizontalCenter: parent.horizontalCenter
                                topMargin: 10
                            }
                            font {
                                pixelSize: 24
                                bold: true
                            }
                            text: "Hard Disk Information"
                        }
                    Text {
                        anchors.centerIn: parent
                        font.pixelSize: 20
                        text: sinfo.getHardDiskInformation()
                    }
                }

                // Section 4: GPU Information
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "#FFFFFF"
                    border.color: "#CCCCCC"
                    border.width: 1
                    radius: 4
                    Text {
                            anchors {
                                top: parent.top
                                horizontalCenter: parent.horizontalCenter
                                topMargin: 10
                            }
                            font {
                                pixelSize: 24
                                bold: true
                            }
                            text: "GPU Information"
                        }
                    Text {
                        anchors.centerIn: parent
                        font.pixelSize: 20
                        text: sinfo.getGPUInformation()
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
