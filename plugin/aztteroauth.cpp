#include "aztteroauth.h"
#include <QNetworkAccessManager>
#include <QDebug>
#include "../QTweetLib/src/oauthtwitter.h"

// constructor
AztterOAuth::AztterOAuth(QObject *parent) : QObject(parent)
{
	m_OAuthTwitter = new OAuthTwitter(this);
	m_OAuthTwitter->setNetworkAccessManager(new QNetworkAccessManager(this));

	connect(m_oauthTwitter, SIGNAL(authorizePinAuthenticate()), this, SLOT(oauthPinAuthenticate()));
	connect(m_oauthTwitter, SIGNAL(authorizePinFinished()), this, SLOT(accessGranted()));

	qDebug() << "AztterOAuth authorization started";
	oauthUrl = m_OAuthTwitter->authorizePin();
	emit oauthUrlChanged();
}

QUrl AztterOAuth::oauthUrl()
{
	return oauthUrl();
}

void AztterOAuth::oauthPinAuthenticate()
{
	emit pleaseEnterPin();
}

void AztterOAuth::setOAuthPin(QString &str)
{
	oauthPin = str;
}

void AztterOAuth::onPinEntered()
{
	if(!oauthPin.isEmpty())
		m_OAuthTwitter->requestAccessToken(&oauthPin);
}

void AztterOAuth::accessGranted()
{
	qDebug() << "AztterOAuth::accessGranted()";
	emit authorized();
}
