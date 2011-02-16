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

#include "utils.h"

#include <QApplication>
#include <QSettings>
#include <QFileInfo>
#include <QDebug>
#include <QDir>

#ifdef Q_OS_SYMBIAN
static const QStringList QML_PATHS = QStringList() << "e:/qmlc" << "c:/data/qmlc";
#else
static const QStringList QML_PATHS = QStringList() << "qmlc/";
#endif

FileAccess::FileAccess(QObject *parent) : QObject(parent)
{
}

QStringList FileAccess::qmlFileNames(const QString &path) const
{
    QStringList filePaths;
    QList<QFileInfo> entries = QDir(path).entryInfoList(QStringList("*.qml"), QDir::Files);
    foreach (const QFileInfo &info, entries)
        filePaths += info.fileName();
    filePaths.replaceInStrings(".qml", "");
    return filePaths;
}

QStringList FileAccess::qmlFilePaths(const QString &path) const
{
    QStringList filePaths;
    QList<QFileInfo> entries = QDir(path).entryInfoList(QStringList("*.qml"), QDir::Files);
    foreach (const QFileInfo &info, entries)
        filePaths += info.absoluteFilePath();
    return filePaths;
}

QStringList FileAccess::qmlPaths() const
{
    QStringList paths;
    foreach (const QString &path, QML_PATHS) {
        QDir dir;
        if (!dir.exists(path) && !dir.mkdir(path))
            qWarning() << "Creation of " << path << " failed";
        else
            paths += path;
    }
    return paths;
}

Settings::Settings(QObject *parent) : QObject(parent)
{
}

void Settings::setOrientation(int orientation) {
    QFileInfo info(QApplication::applicationFilePath());
    QSettings settings("Nokia", info.baseName());
    settings.setValue("orientation", orientation);
}

int Settings::orientation() const {
    QFileInfo info(QApplication::applicationFilePath());
    QSettings settings("Nokia", info.baseName());
    return settings.value("orientation").toInt();
}
