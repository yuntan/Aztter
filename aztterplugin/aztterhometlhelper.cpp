#include "aztterhometlhelper.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include "azttertweetenum.h"

AztterHomeTLHelper::AztterHomeTLHelper(QObject *parent) :
	QObject(parent)
{
	m_stream = new AztterUserStream(this);
	// resize m_tweet to 50
	for(int i = 0; i < 500; i++)
		m_tweet.append(QVariant());

	connect(m_stream, SIGNAL( streamReceived(QByteArray) ), this, SLOT( parseStream(QByteArray) ));
}

void AztterHomeTLHelper::startFetching()
{
	m_stream->startFetching();
}

void AztterHomeTLHelper::streamDisconnect()
{
	m_stream->streamDisconnect();
}

QVariantList AztterHomeTLHelper::tweet() const
{
	return m_tweet;
}

QString AztterHomeTLHelper::name() const
{
	return m_name;
}

QString AztterHomeTLHelper::screenName() const
{
	return m_screenName;
}

QUrl AztterHomeTLHelper::iconSource() const
{
	return m_iconSource;
}

QString AztterHomeTLHelper::text() const
{
	return m_text;
}

void AztterHomeTLHelper::parseStream(const QByteArray &data)
{
	QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

	if(jsonDoc.isObject()) {
		QJsonObject jsonObj = jsonDoc.object();
		if (jsonObj.contains("friends")) {
			qDebug() << "friends list received";
			parseFriendsList(jsonObj);
		} else if (jsonObj.contains("text")) {
			qDebug() << "tweet received";
			parseTweet(jsonObj);
		} else if (jsonObj.contains("delete")) {
			qDebug() << "delete received";
			parseDeleteTweet(jsonObj);
		} else if (jsonObj.contains("direct_message")) {
			qDebug() << "direct message received";
			parseDirectMessage(jsonObj);
		}
	}
}

void AztterHomeTLHelper::parseTweet(const QJsonObject &tweetObj)
{
	m_text = tweetObj["text"].toString();
	m_tweet[AztterTweetEnum::TweetTextRole] = tweetObj["text"].toString();
//	m_tweet[0] = tweetObj["text"].toString();

	QJsonObject userObj = tweetObj["user"].toObject();
	m_name = userObj["name"].toString();
	m_tweet[AztterTweetEnum::UserNameRole] = userObj["name"].toString();
//	m_tweet[1] = userObj["name"].toString();
	m_screenName = userObj["screen_name"].toString();
	m_tweet[AztterTweetEnum::UserScreenNameRole] = userObj["screen_name"].toString();
	m_iconSource = userObj["profile_image_url"].toString();
	m_tweet[AztterTweetEnum::UserProfileImageUrlRole] = userObj["profile_image_url"].toString();

	emit tweetReceived();
}

void AztterHomeTLHelper::parseFriendsList(const QJsonObject &jsonObj)
{
	emit friendsListReceived();
}

void AztterHomeTLHelper::parseDirectMessage(const QJsonObject &jsonObj)
{
	emit directMessageReceived();
}

void AztterHomeTLHelper::parseDeleteTweet(const QJsonObject &jsonObj)
{
	QJsonObject deleteStatusJson = jsonObj["delete"].toObject();
	QJsonObject statusJson = deleteStatusJson["status"].toObject();

	m_deletedId = static_cast<qint64>(statusJson["id"].toDouble());

	emit tweetDeleted();
}
