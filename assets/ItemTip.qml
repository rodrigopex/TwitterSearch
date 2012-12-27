import bb.cascades 1.0

Container {
    id: self
    property alias text: labelText.text
    signal clicked
    preferredHeight: 81
//    preferredWidth: 100
    layout: DockLayout {
    }
    ImageView {
        property bool click: false
        imageSource: "asset:///images/label.png.amd"
        onClickChanged: {
            if (click) {
                self.scaleX = 0.8
                self.scaleY = 0.8
            } else {
                self.scaleX = 1.0
                self.scaleY = 1.0
            }
        }
        onTouchExit: {
            click = false
        }
        onTouch: {
            if (event.isDown()) {
                click = true
            } else if (click && event.isUp()) {
                click = false
                clicked()
            }
        }
    }
    Label {
        id: labelText
        text: "Chave"
        overlapTouchPolicy: OverlapTouchPolicy.Allow
        textStyle.fontSize: FontSize.XXSmall
        textStyle.color: Color.create("#fafafa")
        textStyle.fontWeight: FontWeight.W600
        verticalAlignment: VerticalAlignment.Center
        horizontalAlignment: HorizontalAlignment.Center
    }
}
