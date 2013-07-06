import bb.cascades 1.0
import bb.system 1.0
import bb.system.SystemPrompt 1.0
import bb.system.SystemToast 1.0
import bb.system.SystemDialog 1.0

NavigationPane {
    property string type : "hot"
    property string sort : "viral"
    property int page : 0
    property string sortReddit : "top"
    property string selectecSubreddit: ""

    Menu.definition: MenuDefinition {
        actions: [
            ActionItem {
                title: "Info"
                imageSource: "images/ic_info.png"
                onTriggered: {
                    infoDialog.show()
                }
            }
//            ,
//            ActionItem {
//                title: "Settings"
//                imageSource: "images/actionTwoIcon.png"
//                onTriggered: {
//                    textField.text = "Action 2 selected!"
//                }
//            }
        ]
    } 
    
    backButtonsVisible: false
    peekEnabled: false
    id: navigationPane
    firstPage: MainGallery {
         id: listViewMainGallery
	}
    
    // other views
    attachedObjects: [
        // view for specific picture
        DetailView {
            id: pgDetail
        },
        
        SubredditList {
         	id: pgSubreddit
        },
        
        SubredditGallery {
            id: navigationPaneSubreddit
        },
        
        SystemToast {
            id: startToast
            body: "ImgurLoader by fmi"
            icon: "asset:///images/ic_info.png"
        },

        SystemDialog {
            id: infoDialog
            title: "ImguViewer Info"
            body: "Usage:\n\nSwipe left or right to display next/previous picture.\nIf pinch to zoom is used, swipe is deactivated. To enable it again, zoom out.\n\n© Florian Miess"
            confirmButton.label: "Ok"
            // Hide the cancel button by assigning a QString::null object
            cancelButton.label: objectName
        }
    ]

}
