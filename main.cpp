#include <QtQml>
#include <QtQuick/QQuickView>
#include <QtCore/QString>

#ifndef QT_NO_WIDGETS
#include <QtWidgets/QApplication>
#else
#include <QtGui/QGuiApplication>
#endif

#ifndef QT_NO_WIDGETS
#define Application QApplication
#else
#define Application QGuiApplication
#endif

int main(int argc, char *argv[])
{
    Application app(argc, argv);
    QQmlApplicationEngine engine(QUrl("qml/main.qml"));
    QObject *topLevel = engine.rootObjects().value(0);
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);
    if ( !window ) {
        qWarning("Error: Your root item has to be a Window.");
        return -1;
    }
    window->show();
    return app.exec();
}
