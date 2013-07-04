/* Copyright (c) 2012 Research In Motion Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import bb.cascades 1.0

NavigationPane {
    property string type : "hot"
    property string sort : "viral"
    property int page : 0
    property string sortReddit : "top"
    property bool isReddit : false
    backButtonsVisible: false
    peekEnabled: false
    id: navigationPane
    firstPage: Page {
        actionBarVisibility: ChromeVisibility.Visible
        onCreationCompleted: {
            _app.loadGallery(type, sort, page)
        }
        Container {
            background: Color.Black

	        // The ListView that shows the progress of loading and result images
	        ListView {
	            id: listView
                layout: GridListLayout {}	
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
	                type: ""
	                Container {
	                    preferredHeight: 500
	                    preferredWidth: 768
	                    layout: DockLayout {}
	                    
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
	                        visible: !ListItemData.loading && ListItemData.label == "" && ListItemData.image != 0
                        }
	
	                    // The Label that shows a possible error message after loading has finished
	                    Label {
	                        horizontalAlignment: HorizontalAlignment.Center
	                        verticalAlignment: VerticalAlignment.Center
	                        preferredWidth: 500
	                        visible: !ListItemData.loading && !ListItemData.label == ""
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
                    title: type
                    Option {
                        text: "hot"
                        value: "hot"
                    }
                    Option {
                        text: "top"
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
                    title: sort
                    Option {
                        text: "viral"
                        value: "viral"
                    }
                    Option {
                        text: "time"
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
                    text: page
                    textStyle.textAlign: TextAlign.Center
                    verticalAlignment: VerticalAlignment.Center
                }
                Button {
                    text: "+"
                    preferredWidth: 100
                    onClicked: {
                        page++
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
    
    // other views
    attachedObjects: [
        // view for specific picture
        Page {
            id: pgDetail
            content: Container {
                property int positionX
                property int positionY
                property int indexPath
                property real dragThreshold: 40
                property real currentY: 0
                
                layout: DockLayout {}

                Container {
                    bottomPadding: 25
                    horizontalAlignment: HorizontalAlignment.Center
                    verticalAlignment: VerticalAlignment.Bottom
                    ProgressIndicator {
                        id: progressIndicator
                        opacity: 0
                    }
                }

                ScrollView {
                    scrollViewProperties {
                        scrollMode: ScrollMode.Vertical
                        pinchToZoomEnabled: true
                    }

                    Container {
                        horizontalAlignment: HorizontalAlignment.Center
                        background: Color.Black
                        Label {
                            id: pictureTitle
                            multiline: true
                            text: _app.imageTitle
                            textStyle.color: Color.White
                        }
                    
	                    WebView {
		                    id: webviewProvider
		                    html: _app.html
		                    enabled: true
		                    visible: true
	
	                        onLoadProgressChanged: {
	                            // Update the ProgressBar while loading.
		                        progressIndicator.value = loadProgress / 100.0
		                    }
		                    onLoadingChanged: {
		                        if (loadRequest.status == WebLoadStatus.Started) {
		                            // Show the ProgressBar when loading started.
		                            progressIndicator.opacity = 1.0
		                        } else if (loadRequest.status == WebLoadStatus.Succeeded) {
		                            // Hide the ProgressBar when loading is complete.
		                            progressIndicator.opacity = 0.0;
		                        } else if (loadRequest.status == WebLoadStatus.Failed) {
		                            // If loading failed, fallback to inline HTML, by setting the HTML property directly.
		                            html = "<html><head><title>Fallback HTML on Loading Failed</title><style>* { margin: 0px; padding 0px; }body { font-size: 48px; font-family: monospace; border: 1px solid #444; padding: 4px; }</style> </head> <body>Oh ooh, loading of the URL that was set on this WebView failed. Perhaps you are not connected to the Internet?</body></html>"
		                            progressIndicator.opacity = 0.0
		                        }
		                    }
		                }
		            }
	            }
                
                onTouch: {
                    if (event.isDown()) {
                        positionX = event.windowX
                        positionY = event.windowY
                    } else if (event.isUp()) {
                        if (event.windowY < positionY) {
                        	currentY = positionY - event.windowY;
                        }
                        else {
                        	currentY = event.windowY - positionY
                        }
                        
                        if (positionX > event.windowX && currentY < dragThreshold) {
                            positionX = 0
                            _app.loadNext()
                        } else if (positionX < event.windowX && currentY < dragThreshold) {
                            positionX = 0
                            _app.loadPrev()
                        } else if (positionX == event.windowX && positionY == event.windowY) {
                            pictureTitle.visible = !pictureTitle.visible
                        }
                    }
                }

				Container {
                    horizontalAlignment: HorizontalAlignment.Left
                    verticalAlignment: VerticalAlignment.Bottom
                    
                    ImageView {
                        imageSource: "asset:///images/backbutton.png"
                        verticalAlignment: verticalAlignment.Center
                        onTouch: {
	                    	if (event.isUp()) {
	                    	    isReddit = false;
	                        	navigationPane.pop(navigationPane);
	                        }
	                    }
	                }
				}
            
            }
        },
        
        Page {
            id: pgSubreddit
            content: Container {
                background: Color.Black
                ListView {
                    dataModel: XmlDataModel {
                        source: "models/subreddits.xml"
                    }
                    onTriggered: {
                        var selectedItem = dataModel.data(indexPath);
                        _app.loadSubreddit(selectedItem.title, sortReddit, page)
                        isReddit = true
                        navigationPane.pop(navigationPane);
                    }
                }
                
                Container {
                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight
                    }
                    horizontalAlignment: HorizontalAlignment.Left
                    verticalAlignment: VerticalAlignment.Bottom
                    ImageView {
                        imageSource: "asset:///images/backbutton.png"
                        verticalAlignment: verticalAlignment.Center
                        onTouch: {
                            if (event.isUp()) {
                                navigationPane.pop(navigationPane);
                            }
                        }
                    }
                    DropDown {
                        preferredWidth: 50
                        id: redditSort
                        title: sortReddit
                        Option {
                            text: "top"
                            value: "top"
                        }
                        Option {
                            text: "time"
                            value: "time"
                        }
                        onSelectedIndexChanged: {
                            sortReddit = selectedValue
                        }
                    }

                }
            }
       
        }
    ]

}
