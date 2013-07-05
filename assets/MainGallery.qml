import bb.cascades 1.0

Page {
	actionBarVisibility: ChromeVisibility.Visible
    onCreationCompleted: {
    	_app.loadGallery(type, sort, page)
    }
	Container {
	    background: Color.Black
	
	    // The ListView that shows the progress of loading and result images
	    ListView {
	        layout: GridListLayout {
	        }
	        visible: true
	        dataModel: _app.model
	
	        // add action for loading additional data after scrolling to bottom
	        attachedObjects: [
	            ListScrollStateHandler {
	                id: scrollStateHandler
	                onAtEndChanged: {
	                    if (scrollStateHandler.atEnd) {
	                        _app.listBottomReached();
	                    }
	                }
	            }
	        ]
	        listItemComponents: ListItemComponent {
	            Container {
	                preferredHeight: 500
	                preferredWidth: 768
	                layout: DockLayout {
	                }
	
	                // The ActivityIndicator that is only active and visible while the image is loading
	                ActivityIndicator {
	                    horizontalAlignment: HorizontalAlignment.Center
	                    verticalAlignment: VerticalAlignment.Center
	                    preferredHeight: 300
	                    visible: ListItemData.loading
	                    running: ListItemData.loading
	                }
	
	                // The ImageView that shows the loaded image after loading has finished without error
	                ImageView {
	                    preferredHeight: 300
	                    scalingMethod: ScalingMethod.AspectFill
	                    image: ListItemData.image
	                    visible: ! ListItemData.loading && ListItemData.label == "" && ListItemData.image != 0
	                }
	
	                // The Label that shows a possible error message after loading has finished
	                Label {
	                    horizontalAlignment: HorizontalAlignment.Center
	                    verticalAlignment: VerticalAlignment.Center
	                    preferredWidth: 500
	                    visible: ! ListItemData.loading && ! ListItemData.label == ""
	                    text: ListItemData.label
	                    multiline: true
	                }
	            }
	        }
	        onTriggered: {
	            var curr_item = dataModel.data(indexPath)
	            _app.loadBigImage(indexPath)
	            navigationPane.push(pgDetail)
	        }
	
	    }
	    Container {
	        layout: StackLayout {
	            orientation: LayoutOrientation.LeftToRight
	        }
	        DropDown {
	            preferredWidth: 100
	            id: galleryType
	            title: "Section"
	            Option {
	                text: "Hot"
	                value: "hot"
	            }
	            Option {
	                text: "Top"
	                value: "top"
	            }
	            Option {
	                text: "New"
	                description: "Better be careful..."
	                value: "new"
	            }
	            onSelectedIndexChanged: {
	                type = selectedValue
	                _app.loadGallery(type, sort, page)
	            }
	        }
	        DropDown {
	            preferredWidth: 50
	            id: gallerySort
	            title: "Sorting"
	            Option {
	                text: "Viral"
	                value: "viral"
	            }
	            Option {
	                text: "Time"
	                value: "time"
	            }
	            onSelectedIndexChanged: {
	                console.log("TYPE SelectedIndex was changed to " + selectedIndex);
	                sort = selectedValue
	                _app.loadGallery(type, sort, page)
	            }
	        }
	        Button {
	            text: "r"
	            preferredWidth: 50
	            onClicked: {
	                navigationPane.push(pgSubreddit)
	            }
	        }
	        Label {
	            preferredWidth: 200
	            preferredHeight: 50
	            text: page
	            textStyle.textAlign: TextAlign.Center
	            verticalAlignment: VerticalAlignment.Center
	            //	                    topMargin: 10
	
	        }
	        Button {
	            text: "+"
	            preferredWidth: 100
	            onClicked: {
	                page ++
	                _app.loadGallery(type, sort, page)
	            }
	        }
	        Button {
	            text: "-"
	            preferredWidth: 100
	            onClicked: {
	                if (page > 0) {
	                    page --
	                    _app.loadGallery(type, sort, page)
	                }
	            }
	        }
	    }
	}
}