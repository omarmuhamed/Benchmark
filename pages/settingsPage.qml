import QtQuick 2.0
import QtQuick.Controls 2.15

Item {
    Rectangle {
        id: rectangle
        color: "#2c313c"
        anchors.fill: parent

        Label {
            id: label
            //x: 302
            y: 40
            color: "#ffffff"
            text: qsTr("CO-OP RAM Benchmark Suite")
            //anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 18
            font.bold: true
        }
        Label {
            id: label2
            color: "#ffffff"
            text: qsTr("CO-OP RAM Benchmark Suite is a powerful tool developed by to evaluate and measure RAM performance. \nIt includes sequential/random read/write tests, memory stability evaluation, and throughput/latency measurements.
\nFeatures:\n
Sequential/Random Read/Write Tests\n
Memory Stability Evaluation\n
Throughput and Latency Measurements\n
Score Calculation\n
System Requirements:\n
Windows 7 or later\n
Minimum 2 GB RAM\n
Dual-core processor or higher\n
DirectX 9 or later graphics\n
")
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 14
        }
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:800}
}
##^##*/
