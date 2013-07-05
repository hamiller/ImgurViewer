import bb.cascades 1.0
import bb.system.SystemPrompt 1.0
import bb.system.SystemToast 1.0
import bb.system.SystemDialog 1.0
import bb.system 1.0

Page {
    content: Container {
        background: Color.Black
        ListView {
            id: suredditEntries
            dataModel: _app.modelSubreddit

            listItemComponents: [
                ListItemComponent {
                    type: "header"

                    Label {
                        text: "Subreddits"
                    }
                },
                ListItemComponent {
                    type: "item"

	                StandardListItem {
	                    id: subredditItem
	                    title: ListItemData.title

	                    contextActions: ActionSet {
	                        title: "Subreddit Actions"

	                        ActionItem {
	                            title: "Open"
	                            imageSource: "asset:///images/ic_next.png"
	                            onTriggered: {
	                                subredditItem.ListItem.view.subRedditLoad(subredditItem.title)
	                            }
	                        }
	                        ActionItem {
	                            title: "Edit"
	                            imageSource: "asset:///images/ic_edit.png"
	                            onTriggered: {
	                                subredditItem.ListItem.view.subRedditEdit(subredditItem.title)
	                            }
	                        }
	                        ActionItem {
	                            title: "Delete"
	                            imageSource: "asset:///images/ic_delete.png"
	                            onTriggered: {
	                                subredditItem.ListItem.view.subRedditDelete(subredditItem.title)
	                            }
	                        }

	                    }
	                }

                }
        
	        ]
            
            function subRedditLoad(selectedItemTitle) {
                selectecSubreddit = selectedItemTitle
                _app.loadSubreddit(selectecSubreddit, sortReddit, page)
                navigationPane.push(navigationPaneSubreddit);
            }
            function subRedditEdit(selectedItemTitle) {
                promptEdit.currentItemTitle = selectedItemTitle
                promptEdit.show()
            }
            function subRedditDelete(selectedItemTitle) {
                dialog.currentItemTitle = selectedItemTitle
                dialog.show()
            }
            onTriggered: {
                var selectedItem = dataModel.data(indexPath)
                subRedditLoad(selectedItem.title)
            }
        }

        Container {
            layout: StackLayout {
                orientation: LayoutOrientation.LeftToRight
            }
            verticalAlignment: VerticalAlignment.Bottom
            ImageButton {
                defaultImageSource: "asset:///images/backbutton.png"
                pressedImageSource: "asset:///images/backbutton.png"
                disabledImageSource: "asset:///images/backbutton.png"
                onClicked: {
                    _app.loadGallery(type, sort, page)
                    navigationPane.pop(navigationPane);
                }
            }

            DropDown {
                preferredWidth: 50
                id: redditSort
                title: "Sort"
                Option {
                    text: "Top"
                    value: "top"
                }
                Option {
                    text: "Time"
                    value: "time"
                }
                onSelectedIndexChanged: {
                    sortReddit = selectedValue
                }
            }

            Button {
                text: "Add entry"
                imageSource: "asset:///images/ic_add.png"
                onClicked: {
                    promptCreate.show()
                }
            }

        }
    }
    attachedObjects: [
        SystemPrompt {
            property string currentItemTitle: ""
            id: promptEdit
            title: "Edit entry"
            confirmButton.label: "Ok"
            confirmButton.enabled: true
            cancelButton.label: "Cancel"
            cancelButton.enabled: true
            onFinished: {
                if (result == SystemUiResult.ConfirmButtonSelection) {
                	_app.subRedditEdit(currentItemTitle, inputFieldTextEntry())
                }
            }
        },
        SystemPrompt {
            id: promptCreate
            title: "Create entry"
            confirmButton.label: "Ok"
            confirmButton.enabled: true
            cancelButton.label: "Cancel"
            cancelButton.enabled: true
            onFinished: {
                if (result == SystemUiResult.ConfirmButtonSelection) {
                	_app.subRedditCreate(inputFieldTextEntry())
                }
            }
        },
        SystemDialog {
            property string currentItemTitle: ""
            id: dialog
            title: "Delete entry"
            body: "Delete this entry?"
            confirmButton.label: "Yes"
            confirmButton.enabled: true
            cancelButton.label: "No"
            cancelButton.enabled: true
            onFinished: {
                var x = result;
                if (x == SystemUiResult.ConfirmButtonSelection) {
                	_app.subRedditDelete(currentItemTitle)
                }
            }
        }
    ]

}