/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Components project on Qt Labs.
**
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions contained
** in the Technology Preview License Agreement accompanying this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
****************************************************************************/

import Qt 4.7
import com.meego.themebridge 1.0

ImplicitSizeItem {
    id: titlebar;
    anchors.left: parent.left;
    anchors.right: parent.right;
    z: 1000;
    property alias showBackButton : escapeButton.back;

    property alias dropShadowHeight: dropShadow.height;
    signal minimize();
    signal quit();
    signal backClicked();

    implicitWidth: meegostyle.preferredWidth
    implicitHeight: meegostyle.preferredHeight

    Style {
        id: meegostyle
        styleClass: "MNavigationBarStyle"
    }

    Background {
        id: background
        anchors.fill: parent
        style: meegostyle
    }

    ScalableImage {
        id: dropShadow
        anchors.top: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        style: meegostyle
        imageProperty: "dropShadowImage"
    }

    HomeButton {
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        onClicked: titlebar.minimize()
    }

    EscapeButton {
        id: escapeButton
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter

        onBackClicked: titlebar.backClicked()
        onCloseClicked: titlebar.quit()
    }
}
