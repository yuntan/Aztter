#include <QApplication>
#include <QScreen>
#include <QtQml>
#include <QtQuick/QQuickView>
#include <QtCore/QString>
#include <QFont>
#include <QFontDatabase>
#include <QDebug>

#ifdef Q_OS_ANDROID
#include <QtAndroidExtras/QAndroidJniObject>
#endif

// twitter4qml
#include <QtTwitterAPI/oauth.h>
#include <QtTwitterAPI/oauthmanager.h>

// UnionModel
#include "src/unionmodel.h"

// AztterKeyStore
#include "src/aztterkeystore.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // set keys for twitter4qml
    OAuth oauth;
    oauth.setConsumerKey(AztterKeyStore::consumerKey());
    oauth.setConsumerSecret(AztterKeyStore::consumerSecretKey());
    OAuthManager::instance().setAuthorized(true);
    OAuthManager::instance().setNetworkAccessManager(engine.networkAccessManager());

    // register UnionModel
    qmlRegisterType<UnionModel>("Aztter", 1, 0, "UnionModel");

    // implement density-independent pixel
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

    // load Japanese font
#ifdef Q_OS_ANDROID
    if(QFile::exists("/system/etc/MTLmr3m.ttf")) {
        int fontID = QFontDatabase::addApplicationFont("/system/etc/MTLmr3m.ttf");
        QStringList loadedFontFamilies = QFontDatabase::applicationFontFamilies(fontID);
        if (!loadedFontFamilies.empty()) {
            QString fontName = loadedFontFamilies[0];
            qDebug() << "fontName = " << fontName;
            app.setFont(QFont(fontName));
        } else {
            qWarning("Error: failed to load Japanese font");
        }
    }
#endif

    // load QML
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
