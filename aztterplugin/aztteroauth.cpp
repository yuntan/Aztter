#include "aztteroauth.h"
#include <QtCore>
#include <QStringList>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QDebug>
#include "kqoauthrequest.h"
#include "kqoauthmanager.h"
#include "aztterkeystore.h"

// constructor
AztterOAuth::AztterOAuth(QObject *parent) : QObject(parent)
{
	m_oauthRequest = new KQOAuthRequest(this);
	m_oauthManager = new KQOAuthManager(this);
	m_oauthRequest->setEnableDebugOutput(false);

	connect(m_oauthManager, SIGNAL(temporaryTokenReceived(QString, QString)),
			this, SLOT(onTemporaryTokenReceived(QString, QString)));

	connect(m_oauthManager, SIGNAL(authorizationPageRequested(QUrl)),
			this, SLOT(onAuthorizationPageRequested(QUrl)));

	connect(m_oauthManager, SIGNAL(authorizationReceived(QString, QString)),
			this, SLOT(onAuthorizationReceived(QString, QString)));

	connect(m_oauthManager, SIGNAL(accessTokenReceived(QString, QString)),
			this, SLOT(onAccessTokenReceived(QString, QString)));

	connect(m_oauthManager, SIGNAL(requestReady(QByteArray)),
			this, SLOT(onRequestReady(QByteArray)));

	qDebug() << "AztterOAuth authorization started";
	m_oauthRequest->initRequest(KQOAuthRequest::TemporaryCredentials, QUrl("https://api.twitter.com/oauth/request_token"));
	m_oauthRequest->setConsumerKey(AztterKeyStore::consumerKey()); // TODO
	m_oauthRequest->setConsumerSecretKey(AztterKeyStore::consumerSecretKey()); //TODO

	m_oauthManager->setHandleUserAuthorization(true);
	m_oauthManager->setHandleAuthorizationPageOpening(false);

	m_oauthManager->executeRequest(m_oauthRequest);
}

void AztterOAuth::onTemporaryTokenReceived(QString token, QString tokenSecret)
{
	qDebug() << "Temporary token received: " << token << tokenSecret;

	QUrl userAuthURL("https://api.twitter.com/oauth/authorize");

	if( m_oauthManager->lastError() == KQOAuthManager::NoError) {
		qDebug() << "Asking for user's permission to access protected resources. Opening URL: " << userAuthURL;
		m_oauthManager->getUserAuthorization(userAuthURL);
	} else {
		qDebug() << "AztterOAuth::onTemporaryTokenReceived error!";
	}
}

void AztterOAuth::onAuthorizationPageRequested(QUrl openWebPageUrl)
{
	qDebug() << "Opening WebPage...";
	m_oauthUrl = openWebPageUrl;
	emit oauthUrlChanged();
}

void AztterOAuth::onAuthorizationReceived(QString token, QString verifier) {
//	qDebug() << "User authorization received: " << token << verifier;
	Q_UNUSED(token)
	Q_UNUSED(verifier)

	m_oauthManager->getUserAccessTokens(QUrl("https://api.twitter.com/oauth/access_token"));
	if( m_oauthManager->lastError() != KQOAuthManager::NoError) {
		qDebug() << "AztterOAuth::onAuthorizationReceived error!";
	}
}

void AztterOAuth::onAccessTokenReceived(QString token, QString tokenSecret) {
//	qDebug() << "Access token received: " << token << tokenSecret;
	Q_UNUSED(token)
	Q_UNUSED(tokenSecret)
	qDebug() << "Access token received!";

	emit authorized();

//    m_oauthSettings.setValue("oauth_token", token);
//    m_oauthSettings.setValue("oauth_token_secret", tokenSecret);

//    qDebug() << "Access tokens now stored. You are ready to send Tweets from user's account!";

//    QCoreApplication::exit();
}

void AztterOAuth::onAuthorizedRequestDone() {
	qDebug() << "Request sent to Twitter!";
//    QCoreApplication::exit();
}

void AztterOAuth::onRequestReady(QByteArray response) {
//	qDebug() << "Response from the service: " << response;
	Q_UNUSED(response)
}

QString AztterOAuth::oauthUrl()
{
	return m_oauthUrl.toString();
}
