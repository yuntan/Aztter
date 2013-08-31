#include "aztterstatusupdate.h"
#include <QDebug>

#define TWITTER_STATUSUPDATE_URL "http://api.twitter.com/1.1/statuses/update.json"

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
	init(KQOAuthRequest::POST, QUrl(TWITTER_STATUSUPDATE_URL));
//	init(KQOAuthRequest::GET, QUrl("https://api.twitter.com/1.1/statuses/home_timeline.json"));

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
