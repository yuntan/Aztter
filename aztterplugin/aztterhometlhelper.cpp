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
	for(int i = 0; i < 300; i++)
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

qint64 AztterHomeTLHelper::deletedId() const
{
	return m_deletedId;
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
	m_tweet[AztterTweetEnum::TweetId] = static_cast<qint64>(tweetObj["id"].toDouble());
	m_tweet[AztterTweetEnum::TweetText] = tweetObj["text"].toString();
	m_tweet[AztterTweetEnum::TweetCreatedAt] = tweetObj["created_at"].toString();
	m_tweet[AztterTweetEnum::TweetSource] = tweetObj["source"].toString();

	QString id = tweetObj["in_reply_to_status_id"].toString();
	id == "null" ? m_tweet[AztterTweetEnum::TweetInReplyToStatusId] = id
			: m_tweet[AztterTweetEnum::TweetInReplyToStatusId] = static_cast<qint64>(id.toDouble());

	QJsonObject userObj = tweetObj["user"].toObject();
	m_tweet[AztterTweetEnum::UserId] = static_cast<qint64>(userObj["id"].toDouble());
	m_tweet[AztterTweetEnum::UserName] = userObj["name"].toString();
	m_tweet[AztterTweetEnum::UserScreenName] = userObj["screen_name"].toString();
	m_tweet[AztterTweetEnum::UserProfileImageUrl] = userObj["profile_image_url"].toString();
	m_tweet[AztterTweetEnum::UserVerified] = userObj["verified"].toBool();

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
