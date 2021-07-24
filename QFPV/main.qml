import QtQuick 2.4
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.1

import Qt3D.Extras 2.0
import org.freedesktop.gstreamer.GLVideoItem 1.0

ApplicationWindow
{
    id: 	window
    visible: 	true
    color: 	"black"

    property real vx1:	20
    property real vy1:	65
    property real vz1:	 8

    property real vx2:	70
    property real vy2: 200
    property real vz2:	 8

    Item
    {
        anchors.fill: 		parent

        GstGLVideoItem
        {
            id: 		video
            objectName: 	"videoItem"
            anchors.centerIn: 	parent
    	    width: 		1280
    	    height: 		720
        }
    }
}
