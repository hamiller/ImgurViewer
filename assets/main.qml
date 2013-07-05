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
            id: toast
            body: "ImgurLoader by fmi"
            icon: "asset:///images/ic_info.png"
        }
    ]

}
