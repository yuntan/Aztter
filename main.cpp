#include <QApplication>
#include <QtQml>
#include <QtQuick/QQuickView>
#include <QtCore/QString>
#include <QDebug>
#include "aztterplugin/aztterplugin.h"
#include "aztterplugin/azttertweetlistmodel.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QQmlApplicationEngine engine(QUrl("qrc:/qml/main.qml"));

	auto *aztterPlugin = new AztterPlugin();
	engine.rootContext()->setContextProperty(QLatin1String("aztter"), aztterPlugin);
	auto *tweetListModel = new AztterTweetListModel();
	engine.rootContext()->setContextProperty(QLatin1String("tweetListModel"), tweetListModel);

	QObject *topLevel = engine.rootObjects().value(0);
	QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);
	if ( !window ) {
		qWarning("Error: Your root item has to be a Window.");
		return -1;
	}
	window->show();
	return app.exec();
}
