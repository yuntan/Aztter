#include "aztterstatusupdate.h"
#include <QDebug>

AztterStatusUpdate::AztterStatusUpdate(QObject *parent) : AztterAPIBase(parent)
{
}

QString AztterStatusUpdate::tweet()
{
	return m_tweet;
}

void AztterStatusUpdate::setTweet(QString &str)
{
	m_tweet = str;
	init(KQOAuthRequest::AuthorizedRequest, QUrl("http://api.twitter.com/1.1/statuses/update.json"));

	KQOAuthParameters params;
	params.insert("status", m_tweet);

	m_oauthRequest->setAdditionalParameters(params);
	m_oauthManager->executeRequest(m_oauthRequest);
}

void AztterStatusUpdate::onRequestReady(QByteArray response) {
	qDebug() << "Response from the service: " << response;
//	Q_UNUSED(response)
}

void AztterStatusUpdate::onAuthorizedRequestDone() {
	qDebug() << "Request sent to Twitter!";
}
