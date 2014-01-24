#include <QApplication>
#include <QScreen>
#include <QtQml>
#include <QtQuick/QQuickView>
#include <QtCore/QString>
#ifdef Q_OS_ANDROID
#include <QtAndroidExtras/QAndroidJniObject>
#endif
#include <QDebug>

//twitter4qml
#include <QtTwitterAPI/oauth.h>
#include <QtTwitterAPI/oauthmanager.h>

//UnionModel
#include "src/unionmodel.h"

//AztterPlugin
#include "aztterplugin/aztterplugin.h"
#include "aztterplugin/azttertweetlistmodel.h"
#include "aztterplugin/aztterkeystore.h"
#include "aztterplugin/aztterlocalstorage.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // twitter4qmlにキーを設定
    OAuth oauth;
    oauth.setConsumerKey(AztterKeyStore::consumerKey());
    oauth.setConsumerSecret(AztterKeyStore::consumerSecretKey());
    auto *storage = new AztterLocalStorage();
    oauth.setToken(storage->oauthToken(0));
    oauth.setTokenSecret(storage->oauthTokenSecret(0));
    OAuthManager::instance().setAuthorized(true);
    OAuthManager::instance().setNetworkAccessManager(engine.networkAccessManager());

    auto *aztterPlugin = new AztterPlugin();
    engine.rootContext()->setContextProperty(QLatin1String("aztter"), aztterPlugin);
    auto *tweetListModel = new AztterTweetListModel();
    engine.rootContext()->setContextProperty(QLatin1String("tweetListModel"), tweetListModel);

    // twitter4qmlのUnionModelを登録
    qmlRegisterType<UnionModel>("Aztter", 1, 0, "UnionModel");

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

    // qmlファイルをロード
    engine.load(QUrl("qrc:/qml/main.qml"));

    QObject *topLevel = engine.rootObjects().value(0);
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);
    if ( !window ) {
        qWarning("Error: Your root item has to be a Window.");
        return -1;
    }
    window->show();
    return app.exec();
}
