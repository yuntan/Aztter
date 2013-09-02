#include "aztteruserstream.h"
#include <QTimer>
#include <QSslError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

#define TWITTER_USERSTREAM_URL "https://userstream.twitter.com/1.1/user.json"
#define AUTH_HEADER "Authorization"

AztterUserStream::AztterUserStream(QObject *parent) : AztterAPIBase(parent)
{
	m_reply = 0;
	m_backofftimer = new QTimer(this);
	m_timeoutTimer = new QTimer(this);
	m_streamTryingReconnect = false;
	m_backofftimer->setInterval(20000);
	m_backofftimer->setSingleShot(true);
	m_timeoutTimer->setInterval(90000);

	connect(m_backofftimer, SIGNAL(timeout()), this, SLOT(startFetching()));
	connect(m_timeoutTimer, SIGNAL(timeout()), this, SLOT(replyTimeout()));
}


void AztterUserStream::startFetching()
{
	if (m_reply != 0) {
		m_reply->abort();
		m_reply->deleteLater();
		m_reply = 0;
	}

	init(KQOAuthRequest::GET, QUrl(TWITTER_USERSTREAM_URL));
	m_oauthManager->executeRequest(m_oauthRequest);
	m_reply = m_oauthManager->reply(m_oauthRequest);

	connect(m_reply, SIGNAL(readyRead()), this, SLOT(replyReadyRead()));
	connect(m_reply, SIGNAL(readyRead()), m_timeoutTimer, SLOT(start()));
	connect(m_reply, SIGNAL(finished()), this, SLOT(replyFinished()));
	connect(m_reply, SIGNAL(finished()), m_timeoutTimer, SLOT(stop()));
	connect(m_reply, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(sslErrors(QList<QSslError>)));

	qDebug() << "stream fetching started";
}

void AztterUserStream::streamDisconnect()
{
	if (m_reply != 0) {
		m_reply->disconnect();
		m_reply->abort();
		m_reply->deleteLater();
		m_reply = 0;
	}

	qDebug() << "stream disconnected";
}

void AztterUserStream::replyReadyRead()
{
	QByteArray response = m_reply->readAll();

	if (m_streamTryingReconnect) {
		emit reconnected();
		m_streamTryingReconnect = false;
	}

	//set backoff timer to initial interval
	m_backofftimer->setInterval(20000);

	QByteArray responseWithPreviousCache = response.prepend(m_cachedResponse);

	int start = 0;
	int end;

	while ((end = responseWithPreviousCache.indexOf('\r', start)) != -1) {
		if (start != end) {
			QByteArray element = responseWithPreviousCache.mid(start, end - start);

			if (!element.isEmpty()) {
//				qDebug() << "element: " << element;
				emit streamReceived(element);
			}
		}

		int skip = (response.at(end + 1) == QLatin1Char('\n')) ? 2 : 1;
		start = end + skip;
	}

	//undelimited part just cache it
	m_cachedResponse.clear();

	if (start != responseWithPreviousCache.size()) {
		QByteArray element = responseWithPreviousCache.mid(start);
		if (!element.isEmpty())
			m_cachedResponse = element;
	}
}

// called when connection is finished. let's reconnect
void AztterUserStream::replyFinished()
{
	qDebug() << "User stream closed ";

	m_streamTryingReconnect = true;

	if (!m_reply->error()) { //no error, reconnect
		qDebug() << "No error, reconnect";

		m_reply->deleteLater();
		m_reply = 0;

		startFetching();
	} else {    //error
		qDebug() << "Error: " << m_reply->error() << ", " << m_reply->errorString();

		m_reply->deleteLater();
		m_reply = 0;

		//if (m_backofftimer->interval() < 20001) {
		//  m_backofftimer->start();
		//  return;
		//}

		//increase back off interval
		int nextInterval = 2 * m_backofftimer->interval();

		if (nextInterval > 300000) {
			nextInterval = 300000;
			emit failureConnect();
		}

		m_backofftimer->setInterval(nextInterval);
		m_backofftimer->start();

		qDebug() << "Exp backoff interval: " << nextInterval;
	}
}

void AztterUserStream::replyTimeout()
{
	qDebug() << "Timeout connection";

	m_reply->abort();
}

void AztterUserStream::sslErrors(const QList<QSslError> &errors)
{
	Q_UNUSED(errors);

	QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

	if (reply) {
		reply->ignoreSslErrors();
	}
}
