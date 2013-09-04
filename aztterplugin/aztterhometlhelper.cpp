#include "aztterhometlhelper.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include "azttertweetenum.h"

AztterHomeTLHelper::AztterHomeTLHelper(QObject *parent) :
	QObject(parent)
{
	m_stream = new AztterUserStream(this);

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

QVariantMap AztterHomeTLHelper::tweet() const
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
{ // Do not forget overwrite!!
	m_tweet["TweetId"] = static_cast<qint64>(tweetObj["id"].toDouble());
	m_tweet["TweetText"] = tweetObj["text"].toString();
	m_tweet["TweetCreatedAt"] = tweetObj["created_at"].toString();
	m_tweet["TweetSource"] = tweetObj["source"].toString();

	QString id = tweetObj["in_reply_to_status_id"].toString();
	id == "null" ? m_tweet["TweetInReplyToStatusId"] = QVariant() // insert null
			: m_tweet["TweetInReplyToStatusId"] = static_cast<qint64>(id.toDouble());

	QJsonObject userObj = tweetObj["user"].toObject();
	m_tweet["UserId"] = static_cast<qint64>(userObj["id"].toDouble());
	m_tweet["UserName"] = userObj["name"].toString();
	m_tweet["UserScreenName"] = userObj["screen_name"].toString();
	m_tweet["UserProfileImageUrl"] = userObj["profile_image_url"].toString();
	m_tweet["UserVerified"] = userObj["verified"].toBool();

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
