// Default empty project template
import bb.cascades 1.0

// creates one page with a label

Page {
    titleBar: TitleBar {
        title: "Twitter search"
    }
    Container {
        layout: DockLayout {
        }
        ControlDelegate {
            id: loadingPanel
            delegateActive: false
            function hide() {
                console.log("hiding...")
                loadingPanel.delegateActive = false
                _controller.onModelChanged.disconnect(loadingPanel.hide)
            }
            onDelegateActiveChanged: {
                if (active) _controller.onModelChanged.connect(loadingPanel.hide)
            }
            horizontalAlignment: HorizontalAlignment.Center
            verticalAlignment: VerticalAlignment.Center
            sourceComponent: ComponentDefinition {
                Container {
                    layout: DockLayout {
                    }
                    preferredWidth: 230
                    preferredHeight: 300
                    background: Color.create("#77000000")
                    Container {
                        horizontalAlignment: HorizontalAlignment.Center
                        verticalAlignment: VerticalAlignment.Center
                        ActivityIndicator {
                            id: indicator
                            running: true
                            preferredHeight: 200
                        }
                        Label {
                            text: "Loading..."
                            textStyle.color: Color.create("#f8f8f8")
                            textStyle.fontWeight: FontWeight.W500
                        }
                    }
                }
            }
        }
        Container {
            //            background: Color.create("#262626")
            Container {
                background: Color.create("#f8f8f8")
                topPadding: 20
                bottomPadding: 20
                leftPadding: 20
                rightPadding: 20
                TextField {
                    id: searchKey
                    hintText: "Search"
                    input {
                        onSubmitted: {
                            console.log("Loading " + searchKey.text + "...")
                            _controller.searchKey(searchKey.text)
                            loadingPanel.delegateActive = true
                        }
                    }
                }
            }
            Container {
                layout: DockLayout {
                }
                Divider {
                }
                ListView {
                    id: list
                    dataModel: _controller.model
//                    function itemType(data, indexPath) {
//                        return "item";
//                    }
                    listItemComponents: [
                        ListItemComponent {
                            type: "item"
                            StandardListItem {
                                title: ListItemData.from_user
                                description: ListItemData.text
                                status: {
                                    var dat = new Date(ListItemData.created_at)
                                    return Qt.formatDate(dat, "dd MMM")
                                }
                            }
                        }
                    ]
                }
            }
        }
    }
}