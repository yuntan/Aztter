/*
 * Copyright 2013 Yuuto Tokunaga
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "aztterauthhelper.h"
#include <QtCore>
#include <QStringList>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include "kqoauthrequest.h"
#include "kqoauthmanager.h"
#include "aztterkeystore.h"
#include "aztterlocalstorage.h"

// constructor
AztterAuthHelper::AztterAuthHelper(QObject *parent) : QObject(parent)
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

	qDebug() << "AztterAuthHelper authorization started";
	m_oauthRequest->initRequest(KQOAuthRequest::TemporaryCredentials, QUrl("https://api.twitter.com/oauth/request_token"));
	m_oauthRequest->setConsumerKey(AztterKeyStore::consumerKey());
	m_oauthRequest->setConsumerSecretKey(AztterKeyStore::consumerSecretKey());

	m_oauthManager->setHandleUserAuthorization(true);
	m_oauthManager->setHandleAuthorizationPageOpening(false);

	m_oauthManager->executeRequest(m_oauthRequest);
}

void AztterAuthHelper::onTemporaryTokenReceived(QString token, QString tokenSecret)
{
	qDebug() << "Temporary token received: " << token << tokenSecret;

	QUrl userAuthURL("https://api.twitter.com/oauth/authorize");

	if( m_oauthManager->lastError() == KQOAuthManager::NoError) {
		qDebug() << "Asking for user's permission to access protected resources. Opening URL: " << userAuthURL;
		m_oauthManager->getUserAuthorization(userAuthURL);
	} else {
		qDebug() << "AztterAuthHelper::onTemporaryTokenReceived error!";
	}
}

void AztterAuthHelper::onAuthorizationPageRequested(QUrl openWebPageUrl)
{
	qDebug() << "Opening WebPage...";
	emit authPageRequested(openWebPageUrl.toString());
}

void AztterAuthHelper::onAuthorizationReceived(QString token, QString verifier)
{
//	qDebug() << "User authorization received: " << token << verifier;
	Q_UNUSED(token)
	Q_UNUSED(verifier)

	m_oauthManager->getUserAccessTokens(QUrl("https://api.twitter.com/oauth/access_token"));
	if( m_oauthManager->lastError() != KQOAuthManager::NoError) {
		qDebug() << "AztterAuthHelper::onAuthorizationReceived error!";
	}
}

void AztterAuthHelper::onAccessTokenReceived(QString token, QString tokenSecret)
{
	qDebug() << "Access token received!";
	m_oauthToken = token; m_oauthTokenSecret = tokenSecret;

	// TODO get user screen name
//	disconnect(m_oauthManager, SIGNAL(temporaryTokenReceived(QString, QString)),
//			this, SLOT(onTemporaryTokenReceived(QString, QString)));
//	disconnect(m_oauthManager, SIGNAL(authorizationPageRequested(QUrl)),
//			this, SLOT(onAuthorizationPageRequested(QUrl)));
//	disconnect(m_oauthManager, SIGNAL(authorizationReceived(QString, QString)),
//			this, SLOT(onAuthorizationReceived(QString, QString)));
//	disconnect(m_oauthManager, SIGNAL(accessTokenReceived(QString, QString)),
//			this, SLOT(onAccessTokenReceived(QString, QString)));

//	delete m_oauthManager;
//	delete m_oauthRequest;

//	m_oauthManager = new KQOAuthManager(this);
//	m_oauthRequest = new KQOAuthRequest(this);
//	m_oauthRequest->setEnableDebugOutput(false);

//	connect(m_oauthManager, SIGNAL(requestReady(QByteArray)),
//			this, SLOT(onRequestReady(QByteArray)));
//	connect(m_oauthManager, SIGNAL(authorizedRequestDone()),
//			this, SLOT(onAuthorizedRequestDone()));

//	m_oauthRequest->initRequest(KQOAuthRequest::AuthorizedRequest,
//								 QUrl("https://api.twitter.com/1.1/account/settings.json"));
//	m_oauthRequest->setHttpMethod(KQOAuthRequest::GET);
//	m_oauthRequest->setConsumerKey(AztterKeyStore::consumerKey());
//	m_oauthRequest->setConsumerSecretKey(AztterKeyStore::consumerSecretKey());
//	m_oauthRequest->setToken(m_oauthToken);
//	m_oauthRequest->setTokenSecret(m_oauthTokenSecret);
//	m_oauthManager->executeRequest(m_oauthRequest);

	AztterLocalStorage storage(this);
	storage.addAccount("test", m_oauthToken, m_oauthTokenSecret);

	emit authorized();
}

void AztterAuthHelper::onAuthorizedRequestDone()
{
	qDebug() << "Request sent to Twitter!";
}

void AztterAuthHelper::onRequestReady(QByteArray response)
{
//	qDebug() << "Response from the service: " << response;

	QString screenName;

	QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
	if(jsonDoc.isObject()) {
		QJsonObject jsonObj = jsonDoc.object();
		screenName = jsonObj["screen_name"].toString();
	}

	AztterLocalStorage storage(this);
	storage.addAccount(screenName, m_oauthToken, m_oauthTokenSecret);
	qDebug() << "Account information saved";

	emit authorized();
}
