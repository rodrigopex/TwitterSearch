import bb.cascades 1.0

Page {
    titleBar: TitleBar {
        id: tb
        title: "Twitter search"
        appearance: TitleBarAppearance.Branded
        attachedObjects: [
            OrientationHandler {
                onOrientationAboutToChange: {
                    tb.appearance = (orientation == UIOrientation.Landscape ? TitleBarAppearance.Plain : TitleBarAppearance.Branded)
                }
            }
        ]
    }
    Menu.definition: MenuDefinition {
        actions: ActionItem {
            title: "Clear recents"
            imageSource: "asset:///images/trash.png"
            onTriggered: {
                _controller.clearRecents();
            }
        }
    }
    Container {
        layout: DockLayout {
        }
        Container {
            Container {
                background: Color.create("#f8f8f8")
                topPadding: 20
                bottomPadding: 20
                leftPadding: 20
                rightPadding: 20
                TextField {
                    id: searchKey
                    hintText: "Search"
                    onTextChanging: {
                        _controller.filterRecents(searchKey.text)
                    }
                    onFocusedChanged: {
                        if (focused) {
                            recents.visible = true
                            searchKey.text = ""
                        }
                    }
                    input {
                        submitKey: SubmitKey.Search
                        onSubmitted: {
                            console.log("Loading " + searchKey.text + "...")
                            _controller.searchKey(searchKey.text)
                            loadingPanel.delegateActive = true
                            recents.visible = false
                        }
                    }
                }
                Container {
                    id: recents
                    visible: false
                    onVisibleChanged: {
                        if (visible) _controller.filterRecents(searchKey.text)
                    }
                    Label {
                        text: "Recents"
                        textStyle.fontStyle: FontStyle.Italic
                        textStyle.base: SystemDefaults.TextStyles.SubtitleText
                        textStyle.color: Color.create("#555555")
                    }
                    ListView {
                        id: recentsListView
                        preferredHeight: 82
                        scrollIndicatorMode: ScrollIndicatorMode.None
                        layout: FlowListLayout {
                            orientation: LayoutOrientation.LeftToRight
                        }
                        dataModel: _controller.recentsModel
                        onTriggered: {
                            var key = dataModel.data(indexPath)
                            _controller.searchKey(key)
                            loadingPanel.delegateActive = true
                            searchKey.text = key
                            searchKey.loseFocus()
                            recents.visible = false
                        }
                        listItemComponents: [
                            ListItemComponent {
                                type: ""
                                RecentItem {
                                    id: item
                                    text: ListItemData
                                }
                            }
                        ]
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
                    layout: FlowListLayout {
                    }
                    dataModel: _controller.model
                    listItemComponents: [
                        ListItemComponent {
                            type: "header"
                            Container {
                            }
                        },
                        ListItemComponent {
                            type: "item"
                            Tweet {
                                name: ListItemData.from_user_name
                                twitter: ListItemData.from_user
                                message: ListItemData.text
                                dateString: Qt.formatDate(ListItemData.created_at, "dd MMM")
                            }
                        }
                    ]
                }
            }
        }
        ControlDelegate {
            id: loadingPanel
            delegateActive: false
            function hide() {
                console.log("hiding...")
                loadingPanel.delegateActive = false
            }
            onDelegateActiveChanged: {
                if (active) {
                    _controller.onModelChanged.connect(loadingPanel.hide)
                } else {
                    _controller.onModelChanged.disconnect(loadingPanel.hide)
                }
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
    }
}
