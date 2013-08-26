#include "aztteroauth.h"
#include <QNetworkAccessManager>
#include <QDebug>

// constructor
AztterOAuth::AztterOAuth(QObject *parent) : QObject(parent)
{
	m_oauthTwitter = new OAuthTwitter(this);
	m_oauthTwitter->setNetworkAccessManager(new QNetworkAccessManager(this));

	connect(m_oauthTwitter, SIGNAL(authorizePinAuthenticate()), this, SLOT(oauthPinAuthenticate()));
	connect(m_oauthTwitter, SIGNAL(authorizePinFinished()), this, SLOT(accessGranted()));

//	qDebug() << "AztterOAuth authorization started";
//	m_oauthUrl = m_oauthTwitter->authorizePin();
//	emit oauthUrlChanged();
}

QUrl AztterOAuth::oauthUrl()
{
	return m_oauthUrl;
}

void AztterOAuth::oauthPinAuthenticate()
{
	emit pleaseEnterPin();
}

QString AztterOAuth::oauthPin()
{
	return m_oauthPin;
}

void AztterOAuth::setOAuthPin(QString &str)
{
	m_oauthPin = str;
}

void AztterOAuth::onPinEntered()
{
	if(!m_oauthPin.isEmpty())
		m_oauthTwitter->requestAccessToken(m_oauthPin);
}

void AztterOAuth::accessGranted()
{
	qDebug() << "AztterOAuth::accessGranted()";
	emit authorized();
}
