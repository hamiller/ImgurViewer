import bb.cascades 1.0

Page {
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
	}
}