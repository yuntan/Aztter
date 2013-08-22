#include <QtGui/QGuiApplication>
#include <QQuickItem>
#include "qtquick2applicationviewer.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("main.qml"));
    viewer.showExpanded();

    //root object(MainView)
    QObject* root = viewer.rootObject();
    //fine HelloComponent by name(label)
	QObject* label = root->findChild<QObject *>("loadingLabel");
    //set label's text
    label->setProperty("text", "Wow!");

    return app.exec();
}
