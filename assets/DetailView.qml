import bb.cascades 1.0

Page {
    content: Container {
        id: detailViewContainer
	    property int startX
	    property int startY
	    property real alterX
	    property real alterY
	    property real dragXThreshold: 180
        property real dragYThreshold: 120
        property int indexPath
        property real currentY: 0
        property bool swipeActive: true

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
	        id: scrollView
            scrollViewProperties {
	            scrollMode: ScrollMode.Vertical
	            pinchToZoomEnabled: true
	        }
            onContentScaleChanged: {
                console.log("FMI ############# scale changed:" + contentScale)
                if (contentScale > 1.05) {
                    console.log("FMI ############# deactivate swipe")

                    // we are in zoon mode
                    detailViewContainer.swipeActive = false
                    scrollView.scrollViewProperties.scrollMode = ScrollMode.Both
//                    scrollView.scrollViewProperties.scrollMode : ScrollMode.Both
                }
                else {
                    console.log("FMI ############# activate swipe")
                    detailViewContainer.swipeActive = true
                    scrollView.scrollViewProperties.scrollMode = ScrollMode.Vertical
//                    scrollView.scrollViewProperties.setScrollMode(ScrollMode.Vertical)
                }
                
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

                    onMinContentScaleChanged: {
                        scrollView.scrollViewProperties.minContentScale = minContentScale;
                    }
                    onMaxContentScaleChanged: {
                        scrollView.scrollViewProperties.maxContentScale = maxContentScale;
                    }

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
	        if (swipeActive) {
                if (event.isDown()) {
		            startX = event.windowX
		            startY = event.windowY
		        } else if (event.isUp()) {
		            if (event.windowY < startY) {
		            	alterY = startY - event.windowY
		            }
		            else {
		            	alterY = event.windowY - startY
	                }
	                if (event.windowX < startX) {
	                    alterX = startX - event.windowX
	                } else {
	                    alterX = event.windowX - startX
	                }
	
	                if (startX > event.windowX && alterX > dragXThreshold && alterY < dragYThreshold) {
	                    startX = 0
		                _app.loadNext()
		            } else if (startX < event.windowX && alterX > dragXThreshold && alterY < dragYThreshold) {
	                    startY = 0
		                _app.loadPrev()
		            }
	
	                console.log("startX:" + startX + " event.windowX:" + event.windowX + " alterX:" + alterX + " dragXThreshold:" + dragXThreshold)
	                console.log("startY:" + startY + " event.windowY:" + event.windowY + " alterY:" + alterY + " dragYThreshold:" + dragYThreshold)
	            }
            }
	    }

        ListView {
            id: comments
            visible: false
            
        }
	
		ImageButton {
	        defaultImageSource: "asset:///images/backbutton.png"
	        pressedImageSource: "asset:///images/backbutton.png"
	        disabledImageSource: "asset:///images/backbutton.png"
	        horizontalAlignment: HorizontalAlignment.Left
	        verticalAlignment: VerticalAlignment.Bottom
	
	        onClicked: {
	            navigationPane.pop(navigationPane);
	        }
	    }

        ImageButton {
            defaultImageSource: "asset:///images/commentbutton.png"
            pressedImageSource: "asset:///images/commentbutton.png"
            disabledImageSource: "asset:///images/commentbutton.png"
            horizontalAlignment: HorizontalAlignment.Right
            verticalAlignment: VerticalAlignment.Bottom

            onClicked: {
                comments.visible = true
                _app.loadComments()
            }
        }
    }
}