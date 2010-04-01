/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the FOO module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL-ONLY$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/
import Qt 4.7
import Mx 1.0

Item {
    Row {
        id: control
        x: 100
        y: 100

        property int count: 0;

        Button {
            text: "Add button"
            onClicked: {
                var button = createQmlObject("import Mx 1.0; Button { checkable: true; text: 'Button " + control.count + "' }", row);
                control.count += 1;
                group.refresh();
            }
        }

        // ### Not implemented yet...
        // Button {
        //     text: "Remove button"
        //     onClicked: {
        //     }
        // }

        Button {
            text: "Destroy active"
            onClicked: {
                if (group.checkedItem.toString() !== "null") {
                    group.checkedItem.destroy();
                }
            }
        }

        Button {
            id: allowButton
            text: "Allow no active"
            checkable: true
        }
    }

    ButtonGroup {
        id: group
        allowNoChecked: allowButton.checked

        Row {
            id: row
            x: 100
            y: 200
        }
    }

}
