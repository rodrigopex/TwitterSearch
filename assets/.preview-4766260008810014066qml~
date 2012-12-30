import bb.cascades 1.0

Container {
    property alias name: userNameLabel.text
    property alias twitter: userTwitterLabel.text
    property alias imageUrl: userNameLabel.text
    property alias dateString: dateLabel.text
    property alias message: textLabel.text
    Container {
        layout: StackLayout {
            orientation: LayoutOrientation.LeftToRight
        }
        Container {
            leftPadding: 10
            rightPadding: 10
            verticalAlignment: VerticalAlignment.Fill
            layout: DockLayout {
            }
            layoutProperties: StackLayoutProperties {
                spaceQuota: 3
            }
            ImageView {
                imageSource: "images/empty_image.png"
                scalingMethod: ScalingMethod.AspectFit
                verticalAlignment: VerticalAlignment.Center
            }
        }
        Container {
            rightPadding: 10
            Container {
                horizontalAlignment: HorizontalAlignment.Fill
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
                Container {
                    verticalAlignment: VerticalAlignment.Center
                    horizontalAlignment: HorizontalAlignment.Fill
                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight
                    }
                    layoutProperties: StackLayoutProperties {
                        spaceQuota: 11
                    }
                    Label {
                        id: userNameLabel
                        text: "Rodrigo Peixoto"
                        textStyle.color: Color.create("#262626")
                        textStyle.base: SystemDefaults.TextStyles.PrimaryText
                        verticalAlignment: VerticalAlignment.Center
                    }
                    Label {
                        id: userTwitterLabel
                        opacity: 0.3
                        text: "@rodrigopex"
                        textStyle.color: Color.create("#262626")
                        textStyle.base: SystemDefaults.TextStyles.SmallText
                        verticalAlignment: VerticalAlignment.Center
                    }
                }
                Container {
                    verticalAlignment: VerticalAlignment.Center
                    layoutProperties: StackLayoutProperties {
                        spaceQuota: 2
                    }
                    Label {
                        id: dateLabel
                        text: "30 Dec"
                        textStyle.color: Color.create("#555555")
                        textStyle.base: SystemDefaults.TextStyles.SubtitleText
                        horizontalAlignment: HorizontalAlignment.Right
                    }
                }
            }
            Label {
                id: textLabel
                text: "Exclusive: Hailo Raising $30M at $140M Valuation for Epic NYC E-Taxi Throwdown With Uber http://dthin.gs/UjgUqV "
                multiline: true
                content.flags: TextContentFlag.ActiveText;
                textFormat: TextFormat.Auto
                textStyle.color: Color.create("#262626")
                textStyle.base: SystemDefaults.TextStyles.SubtitleText
                textStyle.textAlign: TextAlign.Justify
            }
            layoutProperties: StackLayoutProperties {
                spaceQuota: 15
            }
        }
    }
    Divider {
    }
}
