import bb.cascades 1.0

Container {
    id: self
    property alias text: labelText.text
    signal clicked
    preferredHeight: 80
    background: imagePD.imagePaint
    leftPadding: 15
    rightPadding: 15
    layout: DockLayout {
    }
    attachedObjects: [
        ImagePaintDefinition {
            id: imagePD
            imageSource: "asset:///images/tag.png.amd"
        }
    ]
    Label {
        id: labelText
        text: "Chave"
        overlapTouchPolicy: OverlapTouchPolicy.Allow
        textStyle.base: SystemDefaults.TextStyles.SubtitleText
        textStyle.color: Color.create("#0073bc")
        verticalAlignment: VerticalAlignment.Center
        horizontalAlignment: HorizontalAlignment.Fill
    }
}
