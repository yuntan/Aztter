#include <QApplication>
#include <QScreen>
#include <QtQml>
#include <QtQuick/QQuickView>
#include <QtCore/QString>
#ifdef Q_OS_ANDROID
#include <QtAndroidExtras/QAndroidJniObject>
#endif
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

	//implement density-independent pixel
	int dp = 1;
	qreal dotsPerInch = app.screens()[0]->physicalDotsPerInch();
	qDebug() << "physicalDotsPerInch = " << dotsPerInch;
	dp = qRound(dotsPerInch) / 125;
#ifdef Q_OS_ANDROID
	qDebug() << "Android OS detected";
	QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");
	QAndroidJniObject resource = activity.callObjectMethod("getResources","()Landroid/content/res/Resources;");
	QAndroidJniObject metrics = resource.callObjectMethod("getDisplayMetrics","()Landroid/util/DisplayMetrics;");
	dp = metrics.getField<float>("density");
#endif
#ifdef Q_OS_IOS
	qDebug() <<	"iOS detected";
	dp = 3;
#endif
	qDebug() << "1dp = " << dp;
	engine.rootContext()->setContextProperty(QLatin1String("dp"), QVariant::fromValue(dp));

	qDebug() << "OfflineStoragePath: " << engine.offlineStoragePath();

	QObject *topLevel = engine.rootObjects().value(0);
	QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);
	if ( !window ) {
		qWarning("Error: Your root item has to be a Window.");
		return -1;
	}
	window->show();
	return app.exec();
}
