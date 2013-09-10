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
	m_oauthSettings = new QSettings(this);
	m_oauthRequest->setEnableDebugOutput(false);
	m_oauthSettings = new QSettings(QSettings::NativeFormat, QSettings::UserScope, "Aztter", "Aztter", this);

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

	m_oauthSettings->setValue("accounts/test/oauth_token", token);
	m_oauthSettings->setValue("accounts/test/oauth_token_secret", tokenSecret);

	qDebug() << "Account Infomation Saved";

	emit authorized();
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
