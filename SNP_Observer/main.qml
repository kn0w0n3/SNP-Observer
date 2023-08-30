import QtQuick
import QtQuick.Controls 2.15

Window {
    width: 1280
    height: 720
    visible: true
    title: qsTr("SNP Observer")

    //Main Controller Connections
           Connections {
               target: mainController

               onSelectedFileName2Qml:{
                   fileNameTextEdit.text = s_FileName
               }
               onFileDataComments:{
                   mainTextView.text += fileDataComment + "\n"
               }
               onErrorData:{
                   mainTextView.text += errData = "\n"
               }
           }

        Rectangle {
            id: mainWin
            width: 1280
            height: 720
            color: "#000000"


            Image {
                id: image
                x: 0
                y: 0
                width: 1280
                height: 720
                source: "file:C:/SNP_Observer/images/bg5.png"
                fillMode: Image.PreserveAspectFit

                Image {
                    id: image1
                    x: 445
                    y: 8
                    width: 443
                    height: 73
                    source: "file:C:/SNP_Observer/images/logo.png"
                    fillMode: Image.PreserveAspectFit
                }
            }

            Rectangle {
                id: mainTxtRect
                x: 234
                y: 81
                width: 812
                height: 347
                color: "#000000"
                border.color: "#ffffff"

                ScrollView {
                    id: scrollView
                    x: 4
                    y: 4
                    width: 804
                    height: 339

                    TextArea {
                        id: mainTextView
                        color: "#ffffff"
                        placeholderText: qsTr("Text Area")
                        background: Rectangle {color: "black"}
                    }
                }
            }

            Image {
                id: imgBtnSelectFile
                x: 233
                y: 449
                width: 91
                height: 30
                source: "file:C:/SNP_Observer/images/selectFileBtn.png"
                fillMode: Image.PreserveAspectFit

                MouseArea {
                    id: mouseAreaSelectFIle
                    x: 0
                    y: 0
                    width: 91
                    height: 30
                    onClicked: {
                        mainController.selectAFile()
                    }
                }
            }

            Rectangle {
                id: selectFileRect
                x: 330
                y: 452
                width: 716
                height: 26
                color: "#000000"
                border.color: "#ffffff"

                TextEdit {
                    id: fileNameTextEdit
                    x: 2
                    y: 5
                    width: 709
                    height: 15
                    color: "#ffffff"
                    text: qsTr("")
                    font.pixelSize: 11
                }
            }

            Image {
                id: imgBtnStart
                x: 368
                y: 498
                width: 89
                height: 30
                source: "file:C:/SNP_Observer/images/startBtn.png"
                fillMode: Image.PreserveAspectFit

                MouseArea {
                    id: mouseAreaStartBtn
                    x: 0
                    y: 0
                    width: 89
                    height: 30
                    onClicked: {
                        if (fileNameTextEdit.text === ""){
                            mainTextView.text += "Select a file before proceeding\n"
                        }
                        else{
                            mainController.startParseDataThread()
                        }
                    }
                }
            }
            ComboBox {
                id: selectFormatComboBox
                x: 234
                y: 54
                width: 153
                height: 21
                editable: false
                visible: true
                model: ["Select File Format", "Ancestry", "23andMe"]

                delegate: ItemDelegate {
                    width: selectFormatComboBox.width
                    contentItem: Text {
                        text: selectFormatComboBox.textRole
                              ? (Array.isArray(selectFormatComboBox.model) ? modelData[selectFormatComboBox.textRole] : model[selectFormatComboBox.textRole])
                              : modelData
                        color: "#000000" //Change the text color of the model data in the drop down box.
                        font: selectFormatComboBox.font
                        elide: Text.ElideRight
                        verticalAlignment: Text.AlignVCenter
                    }
                    highlighted: selectFormatComboBox.highlightedIndex === index
                }

                indicator: Canvas {
                    id: canvasselectOutputFormat
                    x: selectFormatComboBox.width - width - selectFormatComboBox.rightPadding
                    y: selectFormatComboBox.topPadding + (selectFormatComboBox.availableHeight - height) / 2
                    width: 12
                    height: 8
                    contextType: "2d"

                    Connections {
                        target: selectFormatComboBox
                        function onPressedChanged() { canvasselectAlgorithm.requestPaint(); }
                    }

                    //This will change the color of the triangle indicator.
                    onPaint: {
                        context.reset();
                        context.moveTo(0, 0);
                        context.lineTo(width, 0);
                        context.lineTo(width / 2, height);
                        context.closePath();
                        context.fillStyle = selectFormatComboBox.pressed ? "#FFFFFF" : "#FFFFFF";
                        context.fill();
                    }
                }
                //The second color is the main color. The first item is what color the changes to once clicked.
                //This will change the text color of main text in the box.
                contentItem: Text {
                    leftPadding: 0
                    rightPadding: selectFormatComboBox.indicator.width + selectFormatComboBox.spacing

                    text: selectFormatComboBox.displayText
                    font: selectFormatComboBox.font
                    color: selectFormatComboBox.pressed ? "#FFFFFF" : "#FFFFFF"
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }

                //This will change the main box background color, border color,  and the border color when pressed.
                //The second color is the main color. The first item is what color the changes to once clicked.
                background: Rectangle {
                    implicitWidth: 120
                    implicitHeight: 40
                    color: "#000000"
                    border.color: selectFormatComboBox.pressed ? "#FFFFFF" : "#FFFFFF"
                    border.width: selectFormatComboBox.visualFocus ? 2 : 1
                    radius: 2
                }

                popup: Popup {
                    y: selectFormatComboBox.height - 1
                    width: selectFormatComboBox.width
                    implicitHeight: contentItem.implicitHeight
                    padding: 1

                    contentItem: ListView {
                        clip: true
                        implicitHeight: contentHeight
                        model: selectFormatComboBox.popup.visible ? selectFormatComboBox.delegateModel : null
                        currentIndex: selectFormatComboBox.highlightedIndex

                        ScrollIndicator.vertical: ScrollIndicator { }
                    }

                    //This will change the color of the drop down Rectangle
                    background: Rectangle {
                        border.color: "#FFFFFF"
                        color: "#FFFFFF"
                        radius: 5
                    }
                }
            }
        }
    }

