import bb.cascades 1.0
import bb.system 1.0

Page {
    content: Container {
        background: Color.Black
        ListView {
            id: suredditEntries
            dataModel: XmlDataModel {
                source: "models/subreddits.xml"
            }

            listItemComponents: ListItemComponent {
                type: "listItem"
                StandardListItem {
                    id: subredditItem

                    title: ListItemData.title
                    contextActions: ActionSet {
                        title: "Subreddit Actions"

                        ActionItem {
                            title: "Open"
                            imageSource: "asset:///images/ic_next.png"
                            onTriggered: {
                                var selectedItem = subredditItem.ListItem.indexPath;
                                subredditItem.ListItem.view.subRedditLoad(selectedItem)
                            }
                        }
                        ActionItem {
                            title: "Edit"
                            imageSource: "asset:///images/ic_edit.png"
                            onTriggered: {
                                var selectedItem = subredditItem.ListItem.indexPath;
                                subredditItem.ListItem.view.subRedditEdit(selectedItem)
                            }
                        }
                        ActionItem {
                            title: "Delete"
                            imageSource: "asset:///images/ic_delete.png"
                            onTriggered: {
                                var selectedItem = subredditItem.ListItem.indexPath;
                                subredditItem.ListItem.view.subRedditDelete(selectedItem)
                            }
                        }

                    }
                }
            }
            function subRedditLoad(selectedItem) {
                _app.loadSubreddit(selectedItem.title, sortReddit, page)
                navigationPane.push(navigationPaneSubreddit);
            }
            function subRedditEdit(selectedItem) {
                console.log("Edit " + selectedItem.title)
                //                        dialog.currentItemTitle = selectedItem.title
                prompt.show()
            }
            function subRedditDelete(selectedItem) {
                //                        dialog.currentItemTitle = selectedItem.title
                dialog.show()
            }
            onTriggered: {
                var selectedItem = dataModel.data(indexPath)
                subRedditLoad(selectedItem)
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
                    _app.subRedditCreate()
                }
            }

        }
    }
    attachedObjects: [
        SystemPrompt {
            property string currentItemTitle: ""
            id: prompt
            title: "Edit entry"
            modality: SystemUiModality.Application
            confirmButton.label: "Ok"
            confirmButton.enabled: true
            cancelButton.label: "Cancel"
            cancelButton.enabled: true
            onFinished: {
                if (result == SystemUiResult.ConfirmButtonSelection) {
                    console.log("Edit " + currentItemTitle + " into " + inputFieldTextEntry)
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
                    console.log("Delete " + currentItemTitle)
                }
            }
        }
    ]

}