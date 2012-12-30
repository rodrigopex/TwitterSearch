import bb.cascades 1.0

//Page {
//    Container {

Container {
    preferredHeight: 396
    preferredWidth: 334
    background: Color.create("#555555")
    Container {
        layout: StackLayout {
            orientation: LayoutOrientation.LeftToRight
        }
        preferredHeight: 62
        horizontalAlignment: HorizontalAlignment.Fill
        background: Color.create("#262626")
        leftPadding: 10
        Label {
            id: user
            text: lastTweet.from_user
            textStyle.color: Color.create("#f8f8f8")
            verticalAlignment: VerticalAlignment.Center
        }
        Label {
            id: data
            text: "today"
//            text: {
//                var dat = new Date(lastTweet.created_at)
//                return Qt.formatDate(dat, "dd MMM")
//            }
            textStyle.fontSize: FontSize.XXSmall
            textStyle.color: Color.create("#f8f8f8")
            verticalAlignment: VerticalAlignment.Center
        }
    }
    Container {
        leftPadding: 10
        rightPadding: 10
        Label {
            id: text
            text: lastTweet.text
            multiline: true
            textStyle.textAlign: TextAlign.Justify
            textStyle.color: Color.create("#f8f8f8")
            textStyle.fontSize: FontSize.XSmall
            verticalAlignment: VerticalAlignment.Center
        }
    }
}
//    }
//}
