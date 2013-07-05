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
import bb.system 1.0

NavigationPane {
    property string type : "hot"
    property string sort : "viral"
    property int page : 0
    property string sortReddit : "top"
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
        }
    ]

}
