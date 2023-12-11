import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Basic

import com.algorithm.enum 1.0
import com.animation.enum 1.0

ApplicationWindow {
    id: main_window
    visible: true
    minimumWidth: 1000
    maximumWidth: 1000
    minimumHeight: 800
    maximumHeight: 800
    title: "Bezier Spinning"

    readonly property int offset: 6
    readonly property int boxWidth: 180

    Connections {
        target: SceneManager
        function onSceneChanged() {
            scene.reload();
        }
        function onImageChanged() {
            image.reload();
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "lightgrey"

        Row {
            anchors.fill: parent
            anchors.margins: 5
            spacing: 5

            Rectangle {
                width: 195
                height: parent.height
                color: "deepskyblue"

                Column {
                    padding: 7
                    spacing: 20

                    GroupBox {
                        focus: false
                        spacing: 5
                        title: "Number of points (3 - 20)"
                        implicitWidth: boxWidth

                        Row {
                            focus: false
                            spacing: 5
                            TextField {
                                id: pointsTextField
                                height: 30
                                width: 75
                            }
                            Button {
                                height: 30
                                width: 75
                                text: "Generate"
                                onClicked: {
                                    SceneManager.generate(pointsTextField.text);
                                }
                            }
                        }
                    }

                    CheckBox {
                        text: "Visible polyline"
                        checked: true
                        onClicked: {
                            SceneManager.isPolylineVisible = !SceneManager.isPolylineVisible;
                        }
                    }

                    GroupBox {
                        focus: false
                        spacing: 5
                        title: "Image"
                        implicitWidth: boxWidth

                        Row {
                            focus: false
                            spacing: 10
                            Image {
                                id: image
                                width: 100
                                height: 100
                                source: "image://ImageProvider/image"
                                cache: false

                                function reload() {
                                    var oldSource = image.source;
                                    image.source = "";
                                    image.source = oldSource;
                                }
                            }
                            Button {
                                text: "Load"
                                height: 25
                                width: 50
                                y: parent.y + parent.height / 2 - 10
                                onClicked: {
                                    SceneManager.load();
                                }
                            }
                        }
                    }

                    GroupBox {
                        focus: false
                        spacing: 5
                        title: "Algorithm"
                        implicitWidth: boxWidth

                        Column {
                            focus: false
                            spacing: 5

                            RadioButton {
                                text: "Naive"
                                checked: true
                                onClicked: {
                                    SceneManager.algorithm = Algo.Naive;
                                }
                            }
                            RadioButton {
                                text: "Triple Shear"
                                onClicked: {
                                    SceneManager.algorithm = Algo.Shear;
                                }
                            }
                        }
                    }

                    GroupBox {
                        focus: false
                        spacing: 5
                        title: "Animation"
                        implicitWidth: boxWidth

                        Column {
                            focus: false
                            spacing: 5

                            RadioButton {
                                text: "Rotation in place"
                                checked: true
                                onClicked: {
                                    SceneManager.animation = Anim.Rotation;
                                }
                            }
                            RadioButton {
                                text: "Moving on the curve"
                                onClicked: {
                                    SceneManager.animation = Anim.Moving;
                                }
                            }
                            Row {
                                focus: false
                                spacing: 5
                                Button {
                                    height: 30
                                    width: 75
                                    text: "Play"
                                    onClicked: {
                                        SceneManager.isPlaying = true;
                                    }
                                }
                                Button {
                                    height: 30
                                    width: 75
                                    text: "Pause"
                                    onClicked: {
                                        SceneManager.isPlaying = false;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            Image {
                id: scene
                width: parent.width - 200
                height: parent.height
                source: "image://SceneProvider/scene"
                cache: false
                focus: true

                function reload() {
                    var oldSource = scene.source;
                    scene.source = "";
                    scene.source = oldSource;
                }

                MouseArea {
                   id: mouseArea
                   anchors.fill: parent
                   hoverEnabled: true

                    onPressed: {
                       SceneManager.checkPoints(mouseArea.mouseX + offset, mouseArea.mouseY + offset);
                       SceneManager.startDragging();
                    }
                    onReleased: {
                        if (SceneManager.isDragging) {
                            SceneManager.stopDragging();
                        }
                    }
                    onPositionChanged: {
                        if (SceneManager.isDragging) {
                            SceneManager.movePoint(mouseArea.mouseX + offset, mouseArea.mouseY + offset);
                        }
                    }
                }
            }
        }
    }
}
