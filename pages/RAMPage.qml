
import QtQuick 2.0
import QtQuick.Controls 2.15
import QtCharts 2.15
import QtQuick.Layouts 1.0

Item {

    Rectangle {
        id: rectangle
        color: "#2c313c"
        anchors.fill: parent
        ValueAxis {
            id: axisX
            min: 6
            max: 192
        }
        ValueAxis {
            id: axisY
            min: 0
            max: 30
        }
        ValueAxis {
            id: axisX2
            min: 6
            max: 192
        }
        ValueAxis {
            id: axisY2
            min: 0
            max: 30
        }
        ValueAxis {
            id: axisX3
            min: 6
            max: 192
        }
        ValueAxis {
            id: axisY3
            min: 0
            max: 30
        }
        ValueAxis {
            id: axisX4
            min: 6
            max: 192
        }
        ValueAxis {
            id: axisY4
            min: 0
            max: 30
        }
        ValueAxis {
            id: axisX5
            min: 6
            max: 192
        }
        ValueAxis {
            id: axisY5
            min: 0
            max: 30
        }
        ValueAxis {
            id: axisX6
            min: 6
            max: 192
        }
        ValueAxis {
            id: axisY6
            min: 0
            max: 30
        }
        ValueAxis {
            id: axisX7
            min: 6
            max: 192
        }
        ValueAxis {
            id: axisY7
            min: 0
            max: 30
        }
        ValueAxis {
            id: axisX8
            min: 6
            max: 192
        }
        ValueAxis {
            id: axisY8
            min: 0
            max: 30
        }
        ColumnLayout {
            anchors.fill: parent
            anchors.topMargin: 20
            Rectangle {
                width: 200
                height: 50
                radius: height / 2
                color: "#004DFF"

                anchors.horizontalCenter: parent.horizontalCenter
                MouseArea {
                    id: strtbtn
                    property bool started: false
                    anchors.fill: parent
                    onClicked: {
                        if (!started){
                            intRandRSeries.clear()
                            intRandRWSeries.clear()
                            intSerRSeries.clear()
                            intSerRWSeries.clear()
                            fltRandRSeries.clear()
                            fltRandRWSeries.clear()
                            fltSerRSeries.clear()
                            fltSerRWSeries.clear()
                            startBench()
                            started = true
                        }
                    }

                    Text {
                        id: myText
                        text: "Start"
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
            Text {
                        id: myScore
                        font {
                                        pixelSize: 25
                                        bold: true
                                    }
                        color: "green"
                        Layout.alignment: Qt.AlignHCenter
                    }
            RowLayout {
                id: fltLayout
                ChartView {
                    id: fltSerR
                    antialiasing: true
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    LineSeries {
                        name: "Floating Point Serial Read"
                        id: fltSerRSeries
                        axisX: axisX
                        axisY: axisY
                    }
                }

                ChartView {
                    id: fltSerRW
                    antialiasing: true
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    LineSeries {
                        name: "Floating Point Serial Read/Write"
                        id: fltSerRWSeries
                        axisX: axisX2
                        axisY: axisY2
                    }
                }

                ChartView {
                    id: fltRandR
                    antialiasing: true
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    LineSeries {
                        name: "Floating Point Random Read"
                        id: fltRandRSeries
                        axisX: axisX3
                        axisY: axisY3
                    }
                }

                ChartView {
                    id: fltRandRW
                    antialiasing: true
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    LineSeries {
                        name: "Floating Point Random Read/Write"
                        id: fltRandRWSeries
                        axisX: axisX4
                        axisY: axisY4
                    }
                }
            }

            RowLayout {
                id: intLayout
                ChartView {
                    id: intSerR
                    antialiasing: true
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    LineSeries {
                        name: "Integer Serial Read"
                        id: intSerRSeries
                        axisX: axisX5
                        axisY: axisY5

                    }
                }

                ChartView {
                    id: intSerRW
                    antialiasing: true
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    LineSeries {
                        name: "Integer Serial Read/Write"
                        id: intSerRWSeries
                        axisX: axisX6
                        axisY: axisY6
                    }
                }

                ChartView {
                    id: intRndR
                    antialiasing: true
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    LineSeries {
                        name: "Integer Random Read"
                        id: intRandRSeries
                        axisX: axisX7
                        axisY: axisY7
                    }
                }

                ChartView {
                    id: intRndRW
                    antialiasing: true
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    LineSeries {
                        name: "Integer Random Read/Write"
                        id: intRandRWSeries
                        axisX: axisX8
                        axisY: axisY8
                    }
                }
            }


        }
    }
    Connections{
        target: backend
        function onIntSerRSig(size, speed){
            axisX5.max = size
            axisY5.max = axisY5.max > speed ? axisY5.max : speed
            intSerRSeries.append(size, speed)
        }
        function onIntSerRWSig(size, speed){
            axisX6.max = size
            axisY6.max = axisY6.max > speed ? axisY6.max : speed
            intSerRWSeries.append(size, speed)
        }
        function onIntRandRSig(size, speed){
            axisX7.max = size
            axisY7.max = axisY7.max > speed ? axisY7.max : speed
            intRandRSeries.append(size, speed)
        }
        function onIntRandRWSig(size, speed){
            axisX8.max = size
            axisY8.max = axisY8.max > speed ? axisY8.max : speed
            intRandRWSeries.append(size, speed)
        }
        function onFltSerRSig(size, speed){
            axisX.max = size
            axisY.max = axisY.max > speed ? axisY.max : speed
            fltSerRSeries.append(size, speed)
        }
        function onFltSerRWSig(size, speed){
            axisX2.max = size
            axisY2.max = axisY2.max > speed ? axisY2.max : speed
            fltSerRWSeries.append(size, speed)
        }
        function onFltRandRSig(size, speed){
            axisX3.max = size
            axisY3.max = axisY3.max > speed ? axisY3.max : speed
            fltRandRSeries.append(size, speed)
        }
        function onFltRandRWSig(size, speed){
            axisX4.max = size
            axisY4.max = axisY4.max > speed ? axisY4.max : speed
            fltRandRWSeries.append(size, speed)
        }
        function onScoreSig(score){
            myScore.text = "Score: " + score

            strtbtn.started = false
        }

    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
