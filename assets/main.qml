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
    property string type : "top"
    property int page : 0
    backButtonsVisible: false
    id: navigationPane
    firstPage: Page {
        actionBarVisibility: ChromeVisibility.Visible
        Container {
            background: Color.Black

            
            // The button to start the loading of the images
//	        Button {
//	            horizontalAlignment: HorizontalAlignment.Center
//	            verticalAlignment: VerticalAlignment.Center
//	
//	            text: qsTr("Load gallery")
//	
//	            onClicked: {
////	                _app.loadImages()
//                    _app.loadGallery("top", "1")
//                    visible = false
//	                listView.visible = true
//	            }
//	        }
	        // The ListView that shows the progress of loading and result images
	        ListView {
	            id: listView
                layout: GridListLayout {}	
	            visible: true
	            dataModel: _app.model
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
                    // open page for picture
                    openPicture(curr_item)
                }
                
	        }
            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
                DropDown {
                    preferredWidth: 300
                    id: galleryType
                    selectedIndex: 0
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
                        //                    console.log("FMI ########################## changed something...")
                        type = selectedValue
                        _app.loadGallery(type, page)
                    }
                }
                Label {
                    preferredWidth: 200
                    text: "Page " + page
                    textStyle.textAlign: TextAlign.Center

                }
                Button {
                    text: "+"
                    preferredWidth: 100
                    onClicked: {
                        page++
                        _app.loadGallery(type, page)
                    }
                }
                Button {
                    text: "-"
                    preferredWidth: 100
                    onClicked: {
                        if (page > 0) {
                        	page --
                        	_app.loadGallery(type, page)
                        }
                    }
                }
            }
        }
        
	}
    
    // other views
    attachedObjects: [
        // view for specific picture
        ComponentDefinition {
            id: detailedPictureView
            content: Page {
                id: pgDetail
                paneProperties: NavigationPaneProperties {
                    backButton: ActionItem {
                        onTriggered: {
                            navigationPane.pop();
                        }
                    }
                }
                content: Container {
                    property int positionX
                    property int positionY
                    property int indexPath
                    layout: DockLayout {}
                    //                    ActivityIndicator {
//                        horizontalAlignment: HorizontalAlignment.Center
//                        verticalAlignment: VerticalAlignment.Center
//                        preferredHeight: 300
//                        visible: _app.image.loading
//                        running: _app.image.loading
//                    }
                    
                    Container {
                        bottomPadding: 25
                        horizontalAlignment: HorizontalAlignment.Center
                        verticalAlignment: VerticalAlignment.Bottom
                        ProgressIndicator {
                            id: progressIndicator
                            opacity: 0
                        }
                    }
                    
                    WebView {
                        id: webviewProvider
                        url: _app.imageUrl
                        visible: _app.type > 0
                        enabled: _app.type > 0

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

                    ImageView {
                        id: imgView
                        objectName: "imgView"
                        loadEffect: ImageViewLoadEffect.FadeZoom
                        scalingMethod: ScalingMethod.AspectFill
                        image: _app.image
                        visible: _app.type == 0
                        enabled: _app.type == 0
                    }
                    Container {
                        
                        leftPadding: 20
                        background: Color.Black
                        Label {
                            id: pictureTitle
                            multiline: true
                            text: _app.imageTitle
                            textStyle.color: Color.White
                        }
                    }
                    onTouch: {
                        if (event.isDown()) {
                            positionX = event.windowX
                            positionY = event.windowY
                        } else if (event.isUp()) {
                            if (positionX > event.windowX) {
                                positionX = 0
                                _app.loadNext();
                            } else if (positionX < event.windowX) {
                                positionX = 0
                            } else if (positionX == event.windowX && positionY == event.windowY) {
                                pictureTitle.visible = !pictureTitle.visible
                            }
                        }
                    }
                }
            }
        }
    ]

    function openPicture(item) {
        // show detail page
        var page = detailedPictureView.createObject();
        navigationPane.push(page);
    }

}
