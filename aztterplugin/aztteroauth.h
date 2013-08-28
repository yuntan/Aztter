#ifndef AZTTEROAUTH_H
#define AZTTEROAUTH_H

#include <QObject>
#include <QUrl>
#include <QSettings>

class KQOAuthManager;
class KQOAuthRequest;

class AztterOAuth : public QObject
{
    Q_OBJECT

	Q_PROPERTY(QString oauthUrl READ oauthUrl NOTIFY oauthUrlChanged)

public:
	// constractor
    AztterOAuth(QObject *parent = 0);

	// Q_PROPERTY READ function
	QString oauthUrl();
    
signals:
	// Q_PROPERTY NOTIFY function
	void oauthUrlChanged();

    void authorized();

private slots:
	// connected with signals in KQOAuth
	void onTemporaryTokenReceived(QString temporaryToken, QString temporaryTokenSecret);
	void onAuthorizationPageRequested(QUrl openWebPageUrl);
	void onAuthorizationReceived(QString token, QString verifier);
	void onAccessTokenReceived(QString token, QString tokenSecret);
	void onAuthorizedRequestDone();
	void onRequestReady(QByteArray);

private:
	KQOAuthManager *m_oauthManager;
	KQOAuthRequest *m_oauthRequest;
	QSettings *m_oauthSettings;
	QUrl m_oauthUrl;
};

#endif // AZTTEROAUTH_H
