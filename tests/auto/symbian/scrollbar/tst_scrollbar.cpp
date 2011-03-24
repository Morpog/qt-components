/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
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
//For qDebug
//#define QT_COMP_SCROLLBAR_UNIT_TEST_TRACES

#include <QtTest/QTest>
#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeComponent>
#ifdef QT_COMP_SCROLLBAR_UNIT_TEST_TRACES
#include <QtCore/QDebug>
#endif //QT_COMP_SCROLLBAR_UNIT_TEST_TRACES
#include "tst_quickcomponentstest.h"

static const QByteArray QT_COMP_IMPORT_STRING_SYMBIAN = "import com.nokia.symbian 1.0\n";

static void failIfWarnings(QtMsgType type, const char *msg)
{
    Q_UNUSED(msg);
    switch (type) {
    case QtDebugMsg:
        break;
    case QtWarningMsg:
    case QtCriticalMsg:
    case QtFatalMsg:
        QFAIL("NO invoke of any QWARN, QCRITICAL nor QFATAL messages should occur.");
    }
}

class tst_scrollbar : public QObject
{
    Q_OBJECT

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private slots:
    //symbian specific tests
    void testValidScrollBar();
    void testValidScrollBar_data();
    void testScrollBarWithInvalidFlickable();
    void testScrollBarLoadingWithNoParams();
    void testPropertiesScrollBar();
    //Common API component tests
    void testValidScrollDecorator_data();
    void testValidScrollDecorator();
    void testScrollDecoratorWithInvalidFlickable();
    void testScrollDecoratorLoadingWithNoParams();
    void testPropertiesScrollDecorator();

private:
    //common function for ScrollDecorator and ScrollBar
    void checkProperties(const QMetaProperty &property, QObject *obj, int *propertyCount);
    void testValid();

private:
    QDeclarativeEngine engine;
};

void tst_scrollbar::initTestCase()
{
    engine.addImportPath(Q_COMPONENTS_BUILD_TREE"/imports");
}

void tst_scrollbar::cleanupTestCase()
{
}

void tst_scrollbar::init()
{
}

void tst_scrollbar::cleanup()
{
}

void tst_scrollbar::checkProperties(const QMetaProperty &property, QObject *obj, int *propertyCount)
{
    if (property.name() == QString("flickableItem")) {
        (*propertyCount)++;
#ifdef QT_COMP_SCROLLBAR_UNIT_TEST_TRACES
        qDebug() << "default (flickableItem) = " << property.read(obj).toString();
#endif //QT_COMP_SCROLLBAR_UNIT_TEST_TRACES
        QVERIFY(property.read(obj).toString().isNull());
    }
    if (property.name() == QString("policy")) {
        (*propertyCount)++;
#ifdef QT_COMP_SCROLLBAR_UNIT_TEST_TRACES
        qDebug() << "default (policy) = (Symbian.ScrollBarWhenScrolling) " << property.read(obj).toString();
#endif //QT_COMP_SCROLLBAR_UNIT_TEST_TRACES
        QCOMPARE(property.read(obj).toInt(), 1);
        property.write(obj, 0);
        QCOMPARE(property.read(obj).toInt(), 0);
#ifdef QT_COMP_SCROLLBAR_UNIT_TEST_TRACES
        qDebug() << "modified (policy) = " << property.read(obj).toString();
#endif //QT_COMP_SCROLLBAR_UNIT_TEST_TRACES
    }
    if (property.name() == QString("interactive")) {
        (*propertyCount)++;
        property.write(obj, true);
        QCOMPARE(property.read(obj).toBool(), true);
        property.write(obj, false);
        QCOMPARE(property.read(obj).toBool(), false);
#ifdef QT_COMP_SCROLLBAR_UNIT_TEST_TRACES
        qDebug() << "modified (interactive) = " << property.read(obj).toBool();
#endif //QT_COMP_SCROLLBAR_UNIT_TEST_TRACES
    }
    if (property.name() == QString("position")) {
        (*propertyCount)++;
        const qreal value = 0.8;
        property.write(obj, value);
        QCOMPARE(property.read(obj).toReal(), value);
#ifdef QT_COMP_SCROLLBAR_UNIT_TEST_TRACES
        qDebug() << "modified (position) = " << property.read(obj).toString();
#endif //QT_COMP_SCROLLBAR_UNIT_TEST_TRACES
    }
    if (property.name() == QString("pageSize")) {
        (*propertyCount)++;
        const qreal value = 0.8;
        property.write(obj, value);
        QCOMPARE(property.read(obj).toReal(), value);
#ifdef QT_COMP_SCROLLBAR_UNIT_TEST_TRACES
        qDebug() << "modified (pageSize) = " << property.read(obj).toString();
#endif //QT_COMP_SCROLLBAR_UNIT_TEST_TRACES
    }
    if (property.name() == QString("orientation")) {
        (*propertyCount)++;
#ifdef QT_COMP_SCROLLBAR_UNIT_TEST_TRACES
        qDebug() << "default (orientation) = " << property.read(obj).toString();
#endif //QT_COMP_SCROLLBAR_UNIT_TEST_TRACES
        QCOMPARE(property.read(obj).toInt(), int(Qt::Vertical));
        property.write(obj, Qt::Horizontal);
        QCOMPARE(property.read(obj).toInt(), int(Qt::Horizontal));
#ifdef QT_COMP_SCROLLBAR_UNIT_TEST_TRACES
        qDebug() << "modified (orientation) = " << property.read(obj).toString();
#endif //QT_COMP_SCROLLBAR_UNIT_TEST_TRACES
    }
    if (property.name() == QString("implicitWidth")) {
        (*propertyCount)++;
        //check for default value is something 'draggable' for the tool
#ifdef QT_COMP_SCROLLBAR_UNIT_TEST_TRACES
        qDebug() << "default (implicitWidth) = " << property.read(obj).toString();
#endif //QT_COMP_SCROLLBAR_UNIT_TEST_TRACES
        QVERIFY(!property.read(obj).isNull());
    }
    if (property.name() == QString("implicitHeight")) {
        (*propertyCount)++;
        //check for default value is something 'draggable' for the tool
#ifdef QT_COMP_SCROLLBAR_UNIT_TEST_TRACES
        qDebug() << "default (implicitHeight) = " << property.read(obj).toString();
#endif //QT_COMP_SCROLLBAR_UNIT_TEST_TRACES
        QVERIFY(!property.read(obj).isNull());
    }
}

void tst_scrollbar::testValid()
{
    QFETCH(QByteArray, qml);
    QFETCH(bool, isValid);
    QDeclarativeComponent c(&engine);
    c.setData(qml, QUrl());
    QCOMPARE(c.isReady(), isValid);
}

void tst_scrollbar::testScrollBarWithInvalidFlickable()
{
    QByteArray qml = "import Qt 4.7\n"
                     +QT_COMP_IMPORT_STRING_SYMBIAN
                     +"Item {\n"
                     +"    id: root\n"
                     +"    Rectangle { id: rect }\n"
                     +"    ScrollBar { flickableItem: rect }\n"
                     +"}";
    QTest::ignoreMessage(QtWarningMsg, "<Unknown File>:6: Unable to assign QObject* to QDeclarativeFlickable*");
    QObject *obj = tst_quickcomponentstest::createComponentFromString(qml, 0)->children().value(1);//QDeclarativeComponent.create should invoke expected QWARN
    delete obj;
}

void tst_scrollbar::testScrollBarLoadingWithNoParams()
{
    QByteArray qml = "import Qt 4.7\n"
                     +QT_COMP_IMPORT_STRING_SYMBIAN
                     +"ScrollBar {\n"
                     +"}";
    QtMsgHandler orig = qInstallMsgHandler(failIfWarnings);
    QString errors;
    QObject *obj = tst_quickcomponentstest::createComponentFromString(qml, &errors)->children().value(1);
    QVERIFY2(obj, qPrintable(errors));
    qInstallMsgHandler(orig);
    delete obj;
}

void tst_scrollbar::testValidScrollBar_data()
{
    QTest::addColumn<QByteArray>("qml");
    QTest::addColumn<bool>("isValid");
    QByteArray oneDefaultScrollbarWithListView = "import Qt 4.7\n"
                                                 +QT_COMP_IMPORT_STRING_SYMBIAN
                                                 +"Item {\n"
                                                 +"    id: root\n"
                                                 +"    ListView { id: flickableArea }\n"
                                                 +"    ScrollBar { flickableItem: flickableArea }\n"
                                                 +"}";
    QByteArray oneDefaultScrollbarWithGridView= "import Qt 4.7\n"
                                                +QT_COMP_IMPORT_STRING_SYMBIAN
                                                +"Item {\n"
                                                +"    id: root\n"
                                                +"    GridView { id: flickableArea }\n"
                                                +"    ScrollBar { flickableItem: flickableArea }\n"
                                                +"}";
    QByteArray oneDefaultScrollbarWithFlickable = "import Qt 4.7\n"
                                                  +QT_COMP_IMPORT_STRING_SYMBIAN
                                                  +"Item {\n"
                                                  +"    id: root\n"
                                                  +"    Flickable { id: flickableArea }\n"
                                                  +"    ScrollBar { flickableItem: flickableArea }\n"
                                                  +"}";
    QByteArray nonInteractiveScrollbar = "import Qt 4.7\n"
                                         +QT_COMP_IMPORT_STRING_SYMBIAN
                                         +"Item {\n"
                                         +"    id: root\n"
                                         +"    Flickable { id: flickableArea }\n"
                                         +"    ScrollBar { interactive: false; flickableItem: flickableArea }\n"
                                         +"}";
    QByteArray interactiveScrollbar = "import Qt 4.7\n"
                                      +QT_COMP_IMPORT_STRING_SYMBIAN
                                      +"Item {\n"
                                      +"    id: root\n"
                                      +"    Flickable { id: flickableArea }\n"
                                      +"    ScrollBar { interactive: true; flickableItem: flickableArea }\n"
                                      +"}";
    QByteArray showWhenScrollingScrollbar = "import Qt 4.7\n"
                                            +QT_COMP_IMPORT_STRING_SYMBIAN
                                            +"Item {\n"
                                            +"    id: root\n"
                                            +"    Flickable { id: flickableArea }\n"
                                            +"    ScrollBar { policy: Symbian.ScrollBarWhenScrolling; flickableItem: flickableArea }\n"
                                            +"}";
    QByteArray showWhenNeededScrollbar = "import Qt 4.7\n"
                                         +QT_COMP_IMPORT_STRING_SYMBIAN
                                         +"Item {\n"
                                         +"    id: root\n"
                                         +"    Flickable { id: flickableArea }\n"
                                         +"    ScrollBar { policy: Symbian.ScrollBarWhenNeeded; flickableItem: flickableArea }\n"
                                         +"}";
    QByteArray horizontalScrollbar = "import Qt 4.7\n"
                                     +QT_COMP_IMPORT_STRING_SYMBIAN
                                     +"Item {\n"
                                     +"    id: root\n"
                                     +"    Flickable { id: flickableArea }\n"
                                     +"    ScrollBar { orientation: Qt.Horizontal; flickableItem: flickableArea }\n"
                                     +"}";
    QByteArray verticalScrollbar = "import Qt 4.7\n"
                                   +QT_COMP_IMPORT_STRING_SYMBIAN
                                   +"Item {\n"
                                   +"    id: root\n"
                                   +"    Flickable { id: flickableArea }\n"
                                   +"    ScrollBar { orientation: Qt.Horizontal; flickableItem: flickableArea }\n"
                                   +"}";
    QByteArray onPositionChangedScrollbar = "import Qt 4.7\n"
                                            +QT_COMP_IMPORT_STRING_SYMBIAN
                                            +"Item {\n"
                                            +"    id: root\n"
                                            +"    Flickable { id: flickableArea }\n"
                                            +"    ScrollBar { onPositionChanged: {} flickableItem: flickableArea; }\n"
                                            +"}";
    QByteArray onPageSizeChangedScrollbar = "import Qt 4.7\n"
                                            +QT_COMP_IMPORT_STRING_SYMBIAN
                                            +"Item {\n"
                                            +"    id: root\n"
                                            +"    Flickable { id: flickableArea }\n"
                                            +"    ScrollBar { onPageSizeChanged: {} flickableItem: flickableArea }\n"
                                            +"}";
    QByteArray twoScrollbars = "import Qt 4.7\n"
                               +QT_COMP_IMPORT_STRING_SYMBIAN
                               +"Item {\n"
                               +"    id: root\n"
                               +"    Flickable { id: flickableArea }\n"
                               +"    ScrollBar { flickableItem: flickableArea }\n"
                               +"    ScrollBar { orientation: Qt.Horizontal; flickableItem: flickableArea }\n"
                               +"}";
    QTest::newRow("ScrollBar with ListView") << oneDefaultScrollbarWithListView << true;
    QTest::newRow("ScrollBar with GridView") << oneDefaultScrollbarWithGridView << true;
    QTest::newRow("ScrollBar with Flickable") << oneDefaultScrollbarWithFlickable << true;
    QTest::newRow("ScrollBar interactive property set to true") << nonInteractiveScrollbar << true;
    QTest::newRow("ScrollBar interactive property set to false") << interactiveScrollbar << true;
    QTest::newRow("ScrollBar policy set to Symbian.ScrollBarWhenScrolling") << showWhenScrollingScrollbar << true;
    QTest::newRow("ScrollBar policy set to Symbian.ScrollBarWhenNeeded") << showWhenNeededScrollbar << true;
    QTest::newRow("ScrollBar orientation set to Qt.Horizontal") << horizontalScrollbar << true;
    QTest::newRow("ScrollBar orientation set to Qt.Vertical") << verticalScrollbar << true;
    QTest::newRow("ScrollBar with (position property) onPositionChanged") << onPositionChangedScrollbar << true;
    QTest::newRow("ScrollBar with (pageSize property) onPageSizeChanged") << onPageSizeChangedScrollbar << true;
    QTest::newRow("Two Scrollbars, one default and one Horizontal") << twoScrollbars << true;
}

void tst_scrollbar::testValidScrollBar()
{
    testValid();
}

void tst_scrollbar::testPropertiesScrollBar()
{
    QByteArray qml = "import Qt 4.7\n"
                     +QT_COMP_IMPORT_STRING_SYMBIAN
                     +"Item {\n"
                     +"    id: root\n"
                     +"    Flickable { id: flickableArea }\n"
                     +"    ScrollBar { flickableItem: flickableArea }\n"
                     +"}";
    QString errors;
    QObject *obj = tst_quickcomponentstest::createComponentFromString(qml, &errors)->children().value(1);
    QVERIFY2(obj, qPrintable(errors));

    QVERIFY(obj->property("interactive").isValid());
    QVERIFY(obj->property("flickableItem").isValid());
    QVERIFY(obj->property("orientation").isValid());
    QVERIFY(obj->property("policy").isValid());
    QVERIFY(obj->property("position").isValid());
    QVERIFY(obj->property("pageSize").isValid());
    QVERIFY(obj->property("implicitWidth").isValid());
    QVERIFY(obj->property("implicitHeight").isValid());

    const QMetaObject *metaInfo = obj->metaObject();

    int propertyCount = 0;
    int metaPropertyCount = metaInfo->propertyCount();
    for (int i = 0 ; i < metaPropertyCount ; i++) {
#ifdef QT_COMP_SCROLLBAR_UNIT_TEST_TRACES
        qDebug() << "PROPERTY UNDER CHECK IS" << metaInfo->property(i).name();
#endif //QT_COMP_SCROLLBAR_UNIT_TEST_TRACES
        QMetaProperty property = metaInfo->property(i);
        checkProperties(property, obj, &propertyCount);
    }
    QCOMPARE(propertyCount, 8);
    delete obj;
}

void tst_scrollbar::testValidScrollDecorator_data()
{
    QTest::addColumn<QByteArray>("qml");
    QTest::addColumn<bool>("isValid");
    QByteArray oneDefaultScrollDecoratorWithListView = "import Qt 4.7\n"
                                                       +QT_COMP_IMPORT_STRING_SYMBIAN
                                                       +"Item {\n"
                                                       +"    id: root\n"
                                                       +"    ListView { id: flickableArea }\n"
                                                       +"    ScrollDecorator { flickableItem: flickableArea }\n"
                                                       +"}";
    QByteArray oneDefaultScrollDecoratorWithGridView = "import Qt 4.7\n"
                                                       +QT_COMP_IMPORT_STRING_SYMBIAN
                                                       +"Item {\n"
                                                       +"    id: root\n"
                                                       +"    GridView { id: flickableArea }\n"
                                                       +"    ScrollDecorator { flickableItem: flickableArea }\n"
                                                       +"}";
    QByteArray oneDefaultScrollDecoratorWithFlickable = "import Qt 4.7\n"
                                                        +QT_COMP_IMPORT_STRING_SYMBIAN
                                                        +"Item {\n"
                                                        +"    id: root\n"
                                                        +"    Flickable { id: flickableArea }\n"
                                                        +"    ScrollDecorator { flickableItem: flickableArea }\n"
                                                        +"}";
    QByteArray nonInteractiveScrollDecorator = "import Qt 4.7\n"
                                               +QT_COMP_IMPORT_STRING_SYMBIAN
                                               +"Item {\n"
                                               +"    id: root\n"
                                               +"    Flickable { id: flickableArea }\n"
                                               +"    ScrollDecorator { interactive: false; flickableItem: flickableArea }\n"
                                               +"}";
    QByteArray interactiveScrollDecorator = "import Qt 4.7\n"
                                            +QT_COMP_IMPORT_STRING_SYMBIAN
                                            +"Item {\n"
                                            +"    id: root\n"
                                            +"    Flickable { id: flickableArea }\n"
                                            +"    ScrollDecorator { interactive: true; flickableItem: flickableArea }\n"
                                            +"}";
    QByteArray showWhenScrollingScrollDecorator = "import Qt 4.7\n"
                                                  +QT_COMP_IMPORT_STRING_SYMBIAN
                                                  +"Item {\n"
                                                  +"    id: root\n"
                                                  +"    Flickable { id: flickableArea }\n"
                                                  +"    ScrollDecorator { policy: Symbian.ScrollBarWhenScrolling; flickableItem: flickableArea }\n"
                                                  +"}";
    QByteArray showWhenNeededScrollDecorator = "import Qt 4.7\n"
                                               +QT_COMP_IMPORT_STRING_SYMBIAN
                                               +"Item {\n"
                                               +"    id: root\n"
                                               +"    Flickable { id: flickableArea }\n"
                                               +"    ScrollDecorator { policy: Symbian.ScrollBarWhenNeeded; flickableItem: flickableArea }\n"
                                               +"}";
    QByteArray horizontalScrollDecorator = "import Qt 4.7\n"
                                           +QT_COMP_IMPORT_STRING_SYMBIAN
                                           +"Item {\n"
                                           +"    id: root\n"
                                           +"    Flickable { id: flickableArea }\n"
                                           +"    ScrollDecorator { orientation: Qt.Horizontal; flickableItem: flickableArea }\n"
                                           +"}";
    QByteArray verticalScrollDecorator = "import Qt 4.7\n"
                                         +QT_COMP_IMPORT_STRING_SYMBIAN
                                         +"Item {\n"
                                         +"    id: root\n"
                                         +"    Flickable { id: flickableArea }\n"
                                         +"    ScrollDecorator { orientation: Qt.Horizontal; flickableItem: flickableArea }\n"
                                         +"}";
    QByteArray onPositionChangedScrollDecorator = "import Qt 4.7\n"
                                                  +QT_COMP_IMPORT_STRING_SYMBIAN
                                                  +"Item {\n"
                                                  +"    id: root\n"
                                                  +"    Flickable { id: flickableArea }\n"
                                                  +"    ScrollDecorator { onPositionChanged: {} flickableItem: flickableArea; }\n"
                                                  +"}";
    QByteArray onPageSizeChangedScrollDecorator = "import Qt 4.7\n"
                                                  +QT_COMP_IMPORT_STRING_SYMBIAN
                                                  +"Item {\n"
                                                  +"    id: root\n"
                                                  +"    Flickable { id: flickableArea }\n"
                                                  +"    ScrollDecorator { onPageSizeChanged: {} flickableItem: flickableArea }\n"
                                                  +"}";
    QByteArray twoScrollDecorators = "import Qt 4.7\n"
                                     +QT_COMP_IMPORT_STRING_SYMBIAN
                                     +"Item {\n"
                                     +"    id: root\n"
                                     +"    Flickable { id: flickableArea }\n"
                                     +"    ScrollDecorator { flickableItem: flickableArea }\n"
                                     +"    ScrollDecorator { orientation: Qt.Horizontal; flickableItem: flickableArea }\n"
                                     +"}";
    QTest::newRow("ScrollDecorator with ListView") << oneDefaultScrollDecoratorWithListView << true;
    QTest::newRow("ScrollDecorator with GridView") << oneDefaultScrollDecoratorWithGridView << true;
    QTest::newRow("ScrollDecorator with Flickable") << oneDefaultScrollDecoratorWithFlickable << true;
    QTest::newRow("ScrollDecorator interactive property set to true") << nonInteractiveScrollDecorator << false;
    QTest::newRow("ScrollDecorator interactive property set to false") << interactiveScrollDecorator << false;
    QTest::newRow("ScrollDecorator policy set to Symbian.ScrollBarWhenScrolling") << showWhenScrollingScrollDecorator << false;
    QTest::newRow("ScrollDecorator policy set to Symbian.ScrollBarWhenNeeded") << showWhenNeededScrollDecorator << false;
    QTest::newRow("ScrollDecorator orientation set to Qt.Horizontal") << horizontalScrollDecorator << false;
    QTest::newRow("ScrollDecorator orientation set to Qt.Vertical") << verticalScrollDecorator << false;
    QTest::newRow("ScrollDecorator with (position property) onPositionChanged") << onPositionChangedScrollDecorator << false;
    QTest::newRow("ScrollDecorator with (pageSize property) onPageSizeChanged") << onPageSizeChangedScrollDecorator << false;
    QTest::newRow("Two ScrollDecorators, one default and one Horizontal") << twoScrollDecorators << false;
}

void tst_scrollbar::testValidScrollDecorator()
{
    testValid();
}

void tst_scrollbar::testScrollDecoratorWithInvalidFlickable()
{
    QByteArray qml = "import Qt 4.7\n"
                     +QT_COMP_IMPORT_STRING_SYMBIAN
                     +"Item {\n"
                     +"    id: root\n"
                     +"    Rectangle { id: rect }\n"
                     +"    ScrollDecorator { flickableItem: rect }\n"
                     +"}";
    QTest::ignoreMessage(QtWarningMsg, "<Unknown File>:6: Unable to assign QObject* to QDeclarativeFlickable*");
    QObject *obj = tst_quickcomponentstest::createComponentFromString(qml, 0)->children().value(1);//QDeclarativeComponent.create should invoke expected QWARN
    delete obj;
}
void tst_scrollbar::testScrollDecoratorLoadingWithNoParams()
{
    QByteArray qml = "import Qt 4.7\n"
                     +QT_COMP_IMPORT_STRING_SYMBIAN
                     +"ScrollDecorator {\n"
                     +"}";
    QtMsgHandler orig = qInstallMsgHandler(failIfWarnings);
    QString errors;
    QObject *obj = tst_quickcomponentstest::createComponentFromString(qml, &errors)->children().value(1);
    QVERIFY2(obj, qPrintable(errors));
    qInstallMsgHandler(orig);
    delete obj;
}

void tst_scrollbar::testPropertiesScrollDecorator()
{
    QByteArray qml = "import Qt 4.7\n"
                     +QT_COMP_IMPORT_STRING_SYMBIAN
                     +"Item {\n"
                     +"    id: root\n"
                     +"    Flickable { id: flickableArea }\n"
                     +"    ScrollDecorator { flickableItem: flickableArea }\n"
                     +"}";
    QString errors;
    QObject *obj = tst_quickcomponentstest::createComponentFromString(qml, &errors)->children().value(1);
    QVERIFY2(obj, qPrintable(errors));

    //ScrollDecorator.qml part of Common API and is a wrapper using ScrollBar.qml
    QVERIFY(!obj->property("interactive").isValid());
    QVERIFY(obj->property("flickableItem").isValid());
    QVERIFY(!obj->property("orientation").isValid());
    QVERIFY(!obj->property("policy").isValid());
    QVERIFY(!obj->property("position").isValid());
    QVERIFY(!obj->property("pageSize").isValid());
    QVERIFY(!obj->property("implicitWidth").isValid());
    QVERIFY(!obj->property("implicitHeight").isValid());

    const QMetaObject *metaInfo = obj->metaObject();

    int propertyCount = 0;
    int metaPropertyCount = metaInfo->propertyCount();
    for (int i = 0 ; i < metaPropertyCount ; i++) {
#ifdef QT_COMP_SCROLLBAR_UNIT_TEST_TRACES
        qDebug() << "PROPERTY UNDER CHECK IS" << metaInfo->property(i).name();
#endif //QT_COMP_SCROLLBAR_UNIT_TEST_TRACES
        QMetaProperty property = metaInfo->property(i);
        checkProperties(property, obj, &propertyCount);
    }
    QCOMPARE(propertyCount, 1);
    delete obj;
}

QTEST_MAIN(tst_scrollbar)
#include "tst_scrollbar.moc"
