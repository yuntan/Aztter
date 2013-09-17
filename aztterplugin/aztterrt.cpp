#include "aztterrt.h"
#include <QDebug>

#define TWITTER_RT_URL "https://api.twitter.com/1.1/statuses/retweet/%1.json"

AztterRT::AztterRT(QObject *parent) : AztterAPIBase(parent)
{
	m_reply = 0;
}

void AztterRT::rt(qint64 tweetId)
{
	init(KQOAuthRequest::POST, QUrl(QString(TWITTER_RT_URL).arg(tweetId)));
	m_oauthManager->executeRequest(m_oauthRequest);
}

void AztterRT::onRequestReady(QByteArray response)
{
	QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
	if(jsonDoc.isObject()){
		QJsonObject jsonObj = jsonDoc.object();
		if(jsonObj.contains("errors")){
			QJsonObject errorObj = jsonObj["errors"].toArray().at(0).toObject();
			qDebug() << "error received";
			qDebug() << "code:" << errorObj["code"].toDouble() <<
						"message:" << errorObj["message"].toString();
			emit finished(0, false);
		} else if(jsonObj.contains("text")){
			qDebug() << "success";
			emit finished(static_cast<qint64>(jsonObj["id"].toDouble()), true);
		}
	}
}
